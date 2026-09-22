#!/usr/bin/env python3
import hashlib, io, sys, tarfile, urllib.request
from pathlib import Path

URL = "https://registry.npmjs.org/dejavu-fonts-ttf/-/dejavu-fonts-ttf-2.37.3.tgz"
MEMBER = "package/ttf/DejaVuSans.ttf"
SHA256 = "7da195a74c55bef988d0d48f9508bd5d849425c1770dba5d7bfc6ce9ed848954"

def sha256(b): return hashlib.sha256(b).hexdigest()

dest = Path(sys.argv[1]) / "assets" / "fonts" / "DejaVuSans.ttf"
if dest.is_file() and sha256(dest.read_bytes()) == SHA256:
    sys.exit(0)

with urllib.request.urlopen(URL, timeout=30) as r:
    tgz = r.read()
with tarfile.open(fileobj=io.BytesIO(tgz)) as t:
    data = t.extractfile(MEMBER).read()
if sha256(data) != SHA256:
    sys.exit(f"hash mismatch: got {sha256(data)}")

dest.parent.mkdir(parents=True, exist_ok=True)
dest.write_bytes(data)
print(f"font -> {dest}")
