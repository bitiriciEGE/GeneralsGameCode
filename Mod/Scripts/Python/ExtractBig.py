"""Extract files from a Generals / Zero Hour .big archive.

Usage:
    python ExtractBig.py <archive.big> <output dir> [filter]

The optional filter is a case-insensitive prefix such as "Data/INI/".
"""

import os
import struct
import sys


def read_entries(data):
    magic = data[0:4]
    if magic not in (b"BIGF", b"BIG4"):
        raise ValueError(f"not a .big archive (magic {magic!r})")
    file_count = struct.unpack(">I", data[8:12])[0]
    pos = 16
    entries = []
    for _ in range(file_count):
        offset, size = struct.unpack(">II", data[pos:pos + 8])
        pos += 8
        end = data.index(b"\0", pos)
        name = data[pos:end].decode("latin-1").replace("\\", "/")
        pos = end + 1
        entries.append((name, offset, size))
    return entries


def main():
    if len(sys.argv) < 3:
        print(__doc__)
        return 1
    archive, out_dir = sys.argv[1], sys.argv[2]
    prefix = sys.argv[3].replace("\\", "/").lower() if len(sys.argv) > 3 else ""

    with open(archive, "rb") as f:
        data = f.read()

    count = 0
    for name, offset, size in read_entries(data):
        if prefix and not name.lower().startswith(prefix):
            continue
        target = os.path.join(out_dir, *name.split("/"))
        os.makedirs(os.path.dirname(target), exist_ok=True)
        with open(target, "wb") as f:
            f.write(data[offset:offset + size])
        count += 1

    print(f"{count} files extracted from {archive} to {out_dir}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
