from pathlib import Path
from typing import Final, Iterator, List


def findFilesFromGlob(path: Path, globs: List[str]) -> List[Iterator[Path]]:
  glob_matches: List[Iterator[Path]] = []
  for glob in globs:
    glob_matches.append(path.rglob(glob))
  
  return [found_path for found_path in glob_matches if path.is_file()]

def main() -> int:
  CURRENT_DIR_PATH: Final[Path] = Path.cwd()
  HEADER_GLOB: Final[List[str]] = [".h", ".hpp"]
  EXPECTED_PRAGMA_LINE: Final[str] = "#pragma once"
  
  path_iterators = findFilesFromGlob(CURRENT_DIR_PATH, HEADER_GLOB)
  
  for iter in path_iterators:
    for path in iter:
      with open(path) as file:
        read_line = file.readline(1)
        if read_line != EXPECTED_PRAGMA_LINE:
          print(f"No pragma in header: {path}")
  
  return 0

if __name__ == "__main__":
  main()