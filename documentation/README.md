# zpr_project_heroes_with_AI

## w naszym projekcie używamy cmake, sfml i googletest

Bibliotekę sfml i googletest pobieramy dynamicznie w trakcie procesu "build".
Z tego powodu potrzebny jest dostęp do internetu w trakcie "build" i testowania.
Co więcej, by biblioteka sfml poprawnie działa potrzebne jest pobranie dodatkowych bibliotek.
Skrypt do pobrania jest wbudowany do start.sh.
By uruchomić program prosimy upewnić się, że nie ma folderu build. W folderze głównym prosimy o uruchomienie skryptu start.sh. Spowoduje to zbudowanie i uruchomienie aplikacji. Poprawnie uruchomiony program powinien wyświetlić nowe okno z jednostkami na mapie.
Do testów potrzebne jest użycie tych dwóch komend.
`cd build`
`ctest`
W pliku tests/battle/testBattle.cc testujemy możliwości atakowania i ograniczenia związane z maksymalnymi wartościami ataku i defensywy. Natomiast w tests/battle/testBattlefield.cc testujemy możliwość przejścia z każdego kawałka pola bitwy na inny kawałek pola bitwy.

Ruch w Overworld: (standard) W,A,S,D
Ruch w Bitwie: kliknięcie myszą w odpowiednie pole 
|-> Aby czekać (oddać ruch), należy kliknąć jednostkę