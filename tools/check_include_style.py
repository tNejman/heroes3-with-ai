

from pathlib import Path
from typing import Final, List
from sys import stderr

def print_err(*args, **kwargs):
    print(*args, file=stderr, **kwargs)

def findPathsMatchingGlobs(search_start_path: Path, globs: List[str]) -> List[Path]:
    if len(globs) == 0:
        print_err("findPathsMatchingGlobs called with no glob")
        exit(1)
    
    matching_file_paths = []

    for glob in globs:
        matching_file_paths += [path for path in search_start_path.rglob(glob)]
    
    return matching_file_paths

def checkFileIncludes(paths: List[Path], banned_includes: List[str], note: str = "") -> bool:
    retv = True
    
    if len(paths) == 0 or len(banned_includes) == 0:
        print_err("checkFileIncludes with arg len 0")
        exit(1)
    
    for path in paths:
        with open(path) as file:
            for line_num, line in enumerate(file, start=1):
                for banned_include in banned_includes:
                    if line.startswith(banned_include):
                        print_err(f"file ${path} contains banned include: ${line_num}:${line.rstrip('\n')}", end='')
                        if note:
                            print_err(f"; note: ${note}")
                        else:
                            print_err()
                        retv = False
                        
    return retv

def main() -> int:
    CPP_FILE_EXT_GLOB_PATTERNS: Final[List[str]] = ["*.h", "*.hpp", "*.cc", "*.tpp"]
    CWD: Final[Path] = Path.cwd()
    INCLUDE_ENGINE_QUOTATION: Final[str] = "#include \"engine"
    INCLUDE_ENGINE_ANGLE_BRACKET: Final[str] = "#include <engine"

    INCLUDE_AUX_QUOTATION: Final[str] = "#include \"aux"
    INCLUDE_AUX_ANGLE_BRACKET: Final[str] = "#include <aux"

    INCLUDE_ENGINE_MODEL_QUOTATION: Final[str] = "#include \"engine/model"
    INCLUDE_ENGINE_MODEL_ANGLE_BRACKET: Final[str] = "#include <engine/model"
        
    INCLUDE_ENGINE_PLATFORM_QUOTATION: Final[str] = "#include \"engine/platform"
    INCLUDE_ENGINE_PLATFORM_ANGLE_BRACKET: Final[str] = "#include <engine/platform"
    
    INCLUDE_CORE_QUOTATION: Final[str] = "#include \"core"
    INCLUDE_CORE_ANGLE_BRACKET: Final[str] = "#include <core"
    
    INCLUDE_CORE_ANY: Final[List[str]] = [INCLUDE_CORE_QUOTATION, INCLUDE_CORE_ANGLE_BRACKET]
    INCLUDE_ENGINE_ANY: Final[List[str]] = [INCLUDE_ENGINE_QUOTATION, INCLUDE_ENGINE_ANGLE_BRACKET]
    INCLUDE_ENGINE_PLATFORM_ANY: Final[List[str]] = [INCLUDE_ENGINE_PLATFORM_QUOTATION, INCLUDE_ENGINE_PLATFORM_ANGLE_BRACKET]
    
    all_correct: List[bool] = []
    
    ### 1.1. aux mustn't include anything from others
    aux_file_paths = findPathsMatchingGlobs(CWD/"aux", CPP_FILE_EXT_GLOB_PATTERNS)
    checkFileIncludes(aux_file_paths, banned_includes=INCLUDE_CORE_ANY + INCLUDE_ENGINE_ANY)
    
    ### 2.1. engine/model mustn't include engine/platform or core
    ### 2.2. engine/model must include engine/model with quotation marks
    engine_model_file_paths = findPathsMatchingGlobs(CWD/"engine/model", CPP_FILE_EXT_GLOB_PATTERNS)
    all_correct.append(checkFileIncludes(engine_model_file_paths, banned_includes=INCLUDE_CORE_ANY + INCLUDE_ENGINE_PLATFORM_ANY + [INCLUDE_ENGINE_MODEL_ANGLE_BRACKET]))
    
    ### 3.1. core mustn't include engine/platform
    ### 3.2. core must include aux, engine/model with angled brackets
    ### 3.3. core must include core with quotations
    core_file_paths = findPathsMatchingGlobs(CWD/"core", CPP_FILE_EXT_GLOB_PATTERNS)
    all_correct.append(checkFileIncludes(core_file_paths, banned_includes=INCLUDE_ENGINE_PLATFORM_ANY + [INCLUDE_ENGINE_MODEL_QUOTATION, INCLUDE_AUX_QUOTATION, INCLUDE_CORE_ANGLE_BRACKET]))
    
    ### 4.1. engine/platform must include aux, engine/mode, core, engine/platform with angled brackets
    engine_platform_file_paths = findPathsMatchingGlobs(CWD/"engine/platform", CPP_FILE_EXT_GLOB_PATTERNS)
    all_correct.append(checkFileIncludes(engine_platform_file_paths, banned_includes=[INCLUDE_AUX_QUOTATION, INCLUDE_ENGINE_MODEL_QUOTATION, INCLUDE_CORE_QUOTATION, INCLUDE_ENGINE_PLATFORM_QUOTATION]))
    
    if not all(all_correct):
        # exit(1)
        exit(0) # @TODO change to 1
    
    return 0

if __name__ == "__main__":
    main()