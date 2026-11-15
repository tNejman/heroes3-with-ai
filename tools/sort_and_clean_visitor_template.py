from pathlib import Path
import re
from typing import Final, Iterator, List, Tuple

def findPatternAndLocationInLines(file_lines: List[str], rule: str) -> List[Tuple[Iterator[re.Match[str]], int]]: 
    matches = []
    regex = re.compile(rule)
    for line_num, line in enumerate(file_lines, start = 1):
        if sum(1 for _ in regex.finditer(line)) > 0:
            matches.append((regex.finditer(line), line_num))
    return matches


def getVisitorTemplateArgs(file_lines: List[str]) -> Tuple[List[str], int]:
    rule: Final[str] = r"Visitor<.*>"
    matches = findPatternAndLocationInLines(file_lines, rule)
    assert(len(matches) == 1)
    iter, loc = matches[0]
    match = next(iter).group()      # "Visitor<T1, T2, T3...>;"
    _, _, Ts = match.partition('<') # "Visitor", "<", "T1, T2, T2...>;"
    Ts, _, _ = Ts.partition('>')    # "T1, T2, T3...", ">", ";"
    types = Ts.split(", ")
    return (types, loc)

def getClassDeclarations(file_lines: List[str]) -> List[Tuple[str, int]]:
    classes_and_lines = []
    
    rule: Final[str] = r"class .*;"
    matches = findPatternAndLocationInLines(file_lines, rule)
    for match_iter in matches:
        iter, loc = match_iter
        match = next(iter).group()           # "class T;"
        _, _, Ts = match.partition("class ") # "", "class ", "T;"
        Ts, _, _ = Ts.partition(";")         # "T", ";", ""
        classes_and_lines.append((Ts, loc));
       
    return classes_and_lines

def removeClassDeclarations(file_lines: List[str]) -> List[str]:
    lines_cleaned = []
    
    for line in file_lines:
        if not line.startswith("class"):
            lines_cleaned.append(line)
    
    return lines_cleaned

def sortAndMakeUniqueTemplateArgs(template_args: List[str]) -> List[str]:
    unique_args: set[str] = set()
    
    for template_arg in template_args:
        unique_args.add(template_arg)
    
    sorted_unique_args = list(unique_args)
    sorted_unique_args.sort()
    
    return sorted_unique_args

def addClassDeclarations(file_lines: List[str], class_names: List[str], pos: int) -> List[str]:
    file_lines_with_class_decls = []
    
    for line_num, line in enumerate(file_lines, start=1):
        if line_num != pos:
            file_lines_with_class_decls.append(line)
            continue
                
        for class_name in class_names:
            file_lines_with_class_decls.append(f"class {class_name};\n")
            
        file_lines_with_class_decls.append(line)

    return file_lines_with_class_decls

def main() -> int:
    # @SECTION clean up Visitor.h
    path = Path("engine/model/include/engine/model/IGraphics/Visitor.h")
    lines = open(path).readlines()
    template_args, template_pos = getVisitorTemplateArgs(lines)
    class_decl = getClassDeclarations(lines)
    first_decl_loc: int = class_decl[0][1]
    
    lines_no_class_decl = removeClassDeclarations(lines)
    sorted_and_unique_template_args = sortAndMakeUniqueTemplateArgs(template_args)
    lines_with_sroted_and_unique_class_decls = addClassDeclarations(lines_no_class_decl, sorted_and_unique_template_args, first_decl_loc)
    
    with open(path, "w") as file:
        for line in lines_with_sroted_and_unique_class_decls:
            file.write(line)
        
    return 0

if __name__ == "__main__":
    main()