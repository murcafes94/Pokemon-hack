#!/usr/bin/env python3
"""Guard Legacy-specific introductory dialogue during localization work."""
import hashlib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
EXPECTED = {
    'data/scripts/legacy_kanto_cerulean.inc': 'f850867c07d74ebb55f0f0cd7fa0238aa6e6cc796d53af931b5437bb871802ab',
    'data/scripts/legacy_kanto_east.inc': 'da568e067b05725c4db5be666a53e1968bd8766bdf77efbd4e17125395142c31',
    'data/scripts/legacy_kanto_north.inc': '3d226349d380ce02823f9987b8b827078444fb0740ccfd66938dfaf1a04dc228',
    'data/scripts/legacy_kanto_expedition.inc': 'aae3c2f6ef304a6c3ea281cef23823ea7ab9a94017255c2e367a083a79801574',
    'data/text/birch_speech.inc': '2ddc6ad110042ea43299c3f66d94aa2fd87bed6fc58a9553ce3e81cfc4f0fb28',
    'data/scripts/legacy_prologue.inc': '43f7400634b2e46f68eb08f1a7dc5b3d314ab7b0be946b46c8975d3ec1b08ebf',
    'data/scripts/legacy_field_research.inc': 'aacb18598e160677e9fc7297bd4aed5b3137865ba186de156829f5649591ac53',
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
