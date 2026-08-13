from __future__ import annotations

import io
import os
import sys
import tempfile
import urllib.request
import zipfile
from dataclasses import dataclass
from pathlib import Path
from typing import Iterator

BASE = "https://www.spriters-resource.com/media/assets"
ROOT = Path(sys.argv[1]) / "sprites"
HEADERS = {
    "User-Agent": "Mozilla/5.0",
    "Referer": "https://www.spriters-resource.com/",
}
TIMEOUT = 30
PNG_MAGIC = b"\x89PNG\r\n\x1a\n"
ZIP_MAGIC = b"PK\x03\x04"


@dataclass(frozen=True)
class Faction:
    name: str
    subdir: str
    first_id: int
    units: list[str]


@dataclass(frozen=True)
class Asset:
    url: str
    dest: Path


FACTIONS: list[Faction] = [
    Faction("castle", "39", 42154,
            ["pikeman", "archer", "griffin", "swordsman", "monk", "cavalier", "angel"]),
    Faction("conflux", "42", 44995,
            ["pixie", "air_elemental", "water_elemental", "fire_elemental",
             "earth_elemental", "psychic_elemental", "firebird"]),
]

EXTRAS: dict[str, str] = {
    "38/41246.png": "heroes_adventure.png",
}

ARCHIVES: dict[str, str] = {
    "41/43587.zip": "terrain",
}


def fetch(url: str, magic: bytes) -> bytes:
    request = urllib.request.Request(url, headers=HEADERS)
    with urllib.request.urlopen(request, timeout=TIMEOUT) as response:
        data = response.read()
    if not data.startswith(magic):
        raise ValueError(
            f"unexpected content (got {data[:16]!r}, expected prefix {magic!r})"
        )
    return data


def sprite_assets() -> Iterator[Asset]:
    for faction in FACTIONS:
        for index, unit in enumerate(faction.units):
            url = f"{BASE}/{faction.subdir}/{faction.first_id + index}.png"
            dest = ROOT / "units" / faction.name / f"{unit}.png"
            yield Asset(url, dest)
    for path, dest in EXTRAS.items():
        yield Asset(f"{BASE}/{path}", ROOT / dest)


def download(asset: Asset) -> None:
    if asset.dest.exists():
        return
    asset.dest.parent.mkdir(parents=True, exist_ok=True)
    data = fetch(asset.url, PNG_MAGIC)
    tmp = asset.dest.with_suffix(asset.dest.suffix + ".part")
    try:
        tmp.write_bytes(data)
        os.replace(tmp, asset.dest)
    finally:
        tmp.unlink(missing_ok=True)
    print(f"  {asset.dest.relative_to(ROOT)}")


def safe_members(archive: zipfile.ZipFile, outdir: Path) -> list[str]:
    resolved_root = outdir.resolve()
    for name in archive.namelist():
        target = (outdir / name).resolve()
        if target != resolved_root and resolved_root not in target.parents:
            raise ValueError(f"archive member escapes target dir: {name!r}")
    return archive.namelist()


def unpack(url_path: str, subdir: str) -> None:
    outdir = ROOT / subdir
    if outdir.exists():
        return
    data = fetch(f"{BASE}/{url_path}", ZIP_MAGIC)
    staging = Path(tempfile.mkdtemp(prefix=f"{subdir}.", dir=ROOT))
    try:
        with zipfile.ZipFile(io.BytesIO(data)) as archive:
            names = safe_members(archive, staging)
            archive.extractall(staging)
        os.replace(staging, outdir)
    except BaseException:
        for child in sorted(staging.rglob("*"), reverse=True):
            child.rmdir() if child.is_dir() else child.unlink()
        staging.rmdir()
        raise
    print(f"  {subdir}/ ({len(names)} files)")


def main() -> int:
    failures: list[tuple[str, Exception]] = []

    for asset in sprite_assets():
        try:
            download(asset)
        except Exception as error:
            failures.append((asset.url, error))

    for url_path, subdir in ARCHIVES.items():
        try:
            unpack(url_path, subdir)
        except Exception as error:
            failures.append((f"{BASE}/{url_path}", error))

    for url, error in failures:
        print(f"FAIL {url}: {error}", file=sys.stderr)
    return 1 if failures else 0


if __name__ == "__main__":
    raise SystemExit(main())