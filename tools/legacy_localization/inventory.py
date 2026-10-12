#!/usr/bin/env python3

from pathlib import Path
from collections import Counter
import csv
import re

ROOT = Path(__file__).resolve().parents[2]
SEARCH_DIRS = [ROOT / "src", ROOT / "data"]
EXTENSIONS = {".c", ".h", ".inc"}

# _("...")
# COMPOUND_STRING("...")
CALL_RE = re.compile(
    r'(?P<kind>COMPOUND_STRING|_)\s*\(\s*"(?P<text>(?:\\.|[^"\\])*)"\s*\)',
    re.DOTALL,
)

# .string "..."
ASM_RE = re.compile(
    r'\.string\s+"(?P<text>(?:\\.|[^"\\])*)"',
    re.DOTALL,
)

# Etiqueta ASM inmediatamente anterior a uno o más .string
LABEL_RE = re.compile(r'^\s*([A-Za-z_][A-Za-z0-9_]*)::?\s*$', re.MULTILINE)


def line_number(content, pos):
    return content.count("\n", 0, pos) + 1


def visible_text(text):
    return (
        text.replace(r"\n", " ")
            .replace(r"\p", " ")
            .replace(r"\l", " ")
            .replace(r"\f", " ")
            .replace(r"\\", "\\")
            .strip()
    )


records = []

for base in SEARCH_DIRS:
    if not base.exists():
        continue

    for path in base.rglob("*"):
        if not path.is_file() or path.suffix not in EXTENSIONS:
            continue

        relative = path.relative_to(ROOT)

        try:
            content = path.read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue

        # C / headers
        for match in CALL_RE.finditer(content):
            raw = match.group("text")

            if raw:
                records.append({
                    "file": str(relative),
                    "line": line_number(content, match.start()),
                    "kind": (
                        "compound"
                        if match.group("kind") == "COMPOUND_STRING"
                        else "underscore"
                    ),
                    "symbol": "",
                    "text": raw,
                    "visible": visible_text(raw),
                })

        # ASM/inc .string blocks
        if path.suffix == ".inc":
            labels = list(LABEL_RE.finditer(content))

            for i, label in enumerate(labels):
                start = label.end()
                end = labels[i + 1].start() if i + 1 < len(labels) else len(content)
                block = content[start:end]

                pieces = [
                    m.group("text")
                    for m in ASM_RE.finditer(block)
                ]

                if pieces:
                    raw = "".join(pieces)

                    records.append({
                        "file": str(relative),
                        "line": line_number(content, label.start()),
                        "kind": "asm_string_block",
                        "symbol": label.group(1),
                        "text": raw,
                        "visible": visible_text(raw),
                    })


output = Path(__file__).parent / "text_inventory.csv"

with output.open("w", newline="", encoding="utf-8") as f:
    writer = csv.DictWriter(
        f,
        fieldnames=[
            "file",
            "line",
            "kind",
            "symbol",
            "text",
            "visible",
        ],
    )
    writer.writeheader()
    writer.writerows(records)

files = Counter(r["file"] for r in records)
kinds = Counter(r["kind"] for r in records)

print("Pokémon Legacy — Inventario de localización")
print("=" * 48)
print(f"Cadenas/bloques encontrados: {len(records):,}")
print(f"Archivos con texto:          {len(files):,}")

print("\nPor formato:")
for kind, amount in kinds.most_common():
    print(f"  {kind:<22} {amount:>7,}")

print("\nArchivos con más entradas:")
for filename, amount in files.most_common(20):
    print(f"  {amount:>6,}  {filename}")

print(f"\nCSV: {output.relative_to(ROOT)}")
