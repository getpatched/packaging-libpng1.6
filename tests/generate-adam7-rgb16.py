#!/usr/bin/env python3
"""Generate a deterministic, valid 32x32 RGB16 Adam7 PNG for libpng regressions."""
import struct
import sys
import zlib
from pathlib import Path


def chunk(kind, data):
    body = kind + data
    return struct.pack(">I", len(data)) + body + struct.pack(">I", zlib.crc32(body) & 0xFFFFFFFF)


def generate(width=32, height=32, interlaced=True):
    passes = ((0, 0, 8, 8), (4, 0, 8, 8), (0, 4, 4, 8), (2, 0, 4, 4),
              (0, 2, 2, 4), (1, 0, 2, 2), (0, 1, 1, 2))
    if not interlaced:
        passes = ((0, 0, 1, 1),)
    raw = bytearray()
    for x_start, y_start, x_step, y_step in passes:
        xs = range(x_start, width, x_step)
        if x_start >= width or y_start >= height:
            continue
        for y in range(y_start, height, y_step):
            raw.append(0)  # PNG filter: None
            for x in xs:
                red = (x * 65535) // (width - 1)
                green = (y * 65535) // (height - 1)
                blue = ((x * 977 + y * 619) & 0xFFFF)
                raw.extend(struct.pack(">HHH", red, green, blue))
    header = struct.pack(">IIBBBBB", width, height, 16, 2, 0, 0, int(interlaced))
    return b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", header) + chunk(b"IDAT", zlib.compress(raw, 9)) + chunk(b"IEND", b"")


def main():
    if len(sys.argv) not in (2, 3) or (len(sys.argv) == 3 and sys.argv[2] != "--flat"):
        raise SystemExit("usage: generate-adam7-rgb16.py OUTPUT.png [--flat]")
    Path(sys.argv[1]).write_bytes(generate(interlaced=len(sys.argv) == 2))


if __name__ == "__main__":
    main()
