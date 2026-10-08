#!/usr/bin/env python3
"""Check source availability without running builds or altering existing files."""
import argparse
from pathlib import Path


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[2])
    args = parser.parse_args()
    root = args.root
    required = (
        "Makefile", "charmap.txt", "src/main.c", "src/strings.c",
        "include/global.h", "asm/macros.inc", "data/maps/LittlerootTown/scripts.inc",
    )
    missing = [name for name in required if not (root / name).is_file()]
    counts = {suffix: sum(1 for _ in root.glob(f"**/*{suffix}"))
              for suffix in (".c", ".png")}
    print(f"Source inventory: {counts['.c']} C files; {counts['.png']} PNG assets")
    for name in missing:
        print(f"MISSING: {name}")
    if missing or not all(counts.values()):
        print("BLOCKED: restore the original Legacy sources; do not replace them with upstream.")
        return 1
    print("Source prerequisites present. This does not certify a successful ROM build.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
