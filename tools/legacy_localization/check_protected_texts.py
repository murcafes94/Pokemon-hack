#!/usr/bin/env python3
"""Guard Legacy-specific introductory dialogue during localization work."""
import hashlib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
EXPECTED = {
    'data/text/birch_speech.inc': '2ddc6ad110042ea43299c3f66d94aa2fd87bed6fc58a9553ce3e81cfc4f0fb28',
    'data/scripts/legacy_prologue.inc': '373b9b0fde513ae650c8956fe25fa5616cb06c2157429019a8684669a5fc23e5',
}


def main():
    for name, expected in EXPECTED.items():
        actual = hashlib.sha256((ROOT / name).read_bytes()).hexdigest()
        if actual != expected:
            raise ValueError(f'Legacy text changed: {name}. Review the intended edit before updating its approved checksum.')
    print('Legacy-specific dialogue preserved')


if __name__ == '__main__':
    main()
