#!/usr/bin/env python3
"""Guard Legacy-specific introductory dialogue during localization work."""
import hashlib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
EXPECTED = {
    'data/text/birch_speech.inc': '2ddc6ad110042ea43299c3f66d94aa2fd87bed6fc58a9553ce3e81cfc4f0fb28',
    'data/scripts/legacy_prologue.inc': '43f7400634b2e46f68eb08f1a7dc5b3d314ab7b0be946b46c8975d3ec1b08ebf',
    'data/scripts/legacy_field_research.inc': '5a1ac699f7eb42968caa1c09dbd423f8ccc32c88bc9bf8fe1c6fa9db88469298',
    'data/scripts/legacy_forest_research.inc': 'bde1dc49307efeb8fa526539475840d31c0d7d342080d57660f7a11b1daa9866',
}


def main():
    for name, expected in EXPECTED.items():
        actual = hashlib.sha256((ROOT / name).read_bytes()).hexdigest()
        if actual != expected:
            raise ValueError(f'Legacy text changed: {name}. Review the intended edit before updating its approved checksum.')
    print('Legacy-specific dialogue preserved')


if __name__ == '__main__':
    main()
