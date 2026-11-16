#!/usr/bin/env bash
set -euo pipefail
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
cd "$work"
python3 - <<'PY'
from pathlib import Path
from struct import pack
import zlib

def chunk(kind, data):
    return pack(">I", len(data)) + kind + data + pack(">I", zlib.crc32(kind + data))

Path("pixel.png").write_bytes(
    b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", pack(">IIBBBBB", 1, 1, 8, 0, 0, 0, 0))
    + chunk(b"IDAT", zlib.compress(b"\x00\x80")) + chunk(b"IEND", b"")
)
PY
pngfix pixel.png
