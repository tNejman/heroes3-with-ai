Styl kodowania obowiązujący na projektach z ZPR.
Rafał Biedrzycki

1. Kodowanie: ASCII (Plain), tj. brak znaków narodowych.
2. Nadawanie nazw oraz komentarze w jęz. polskim lub angielskim - należy jednak zdecydować się na konkretny język i tego właśnie języka używać w całym programie.
3. Nazwa pliku powinna odpowiadać zawartości.
4. Nazwa pliku powinna powinna rozpoczynać się dużą literą, np. ObliczaniePierwiastkow.cc.
5. Pliki z kodem powinny mieć rozszerzenie .cc.
6. Pliki nagłówkowe powinny mieć rozszerzenie .h.
7. Pliki nagłówkowe zawierające zarówno deklarację jak i definicję (sensowne przy szablonach) powinny mieć rozszerzenie .hpp.
8. Każdy plik źródłowy oraz nagłówkowy powinien rozpoczynać się blokiem komentarza zawierającym dane autora oraz opis zawartości.
9. Każda nietrywialna klasa i metoda powinny być poprzedzone blokiem komentarza.
10. Należy unikać trudnych w zrozumieniu fragmentów kodu, a gdy nie da się ich uniknąć powinny zostać opatrzone komentarzem.
11. Nazwy klas, struktur, wyliczeń i nazwy definicji typów (typedef) powinny zaczynać się dużą literą. Każdy następny wyraz użyty w nazwie powinien zaczynać się dużą literą, np. struct KotekInfo{};.
12. Nazwy funkcji oraz nazwy metod powinny zaczynać się małą literą. Każdy następny wyraz użyty w nazwie powinien zaczynać się dużą literą, np. int obliczPierwiastki(){};.
13. Parametry funkcji/metody oraz zmienne lokalne powinny rozpoczynać się małymi literami. Każdy następny wyraz użyty w nazwie powinien zaczynać się małą literą, kolejne wyrazy powinny być rozdzielone znakiem podkreślenia ’_’, np. char czy_koniec;.
14. Elementy wyliczeń oraz nazwy stałych powinny być pisane wyłącznie dużymi literami. Każdy następny wyraz użyty w nazwie powinien być rozdzielony od pozostałych znakiem podkreślenia ’_’, np. enum Kolor{BIALY, CZARNY}; const int ROZMIAR_MAKSYMALNY=14;.
15. Nazwy pól klasy kończą się znakiem podkreślenia ’_’.
16. Na początku dołączamy nagłówki bibliotek, potem własne nagłówki.
17. W plikach z implementacją włączamy przestrzeń 'std', a w plikach nagłówkowych nie.
18. Proszę o zwrócenie uwagi na to, gdzie występują spacje w poniższym przykładzie. (spacje mogą być również tak, jak robi clang-format)

Przykład:

#include <iostream>
#include <cmath>
#include "Kotek.h"

class MojaKlasa{
public:
    MojaKlasa();
    void funkcjaPierwsza( int parametr_pierwszy );

    enum class Kolor{ BIALY, NIEBIESKI, CIEMNO_ZIELONY };
private:
    Kolor kolor_;
};
Należy wykonywać wcięcia o jeden poziom dla każdego nowego poziomu logicznego. Przykład:

if( wyr )
    instr1;

int obliczPierwiastki(){
    for(  ;  ; ){
       if( wyr ){
          instr1;
          instr2;
          ...
       }
       instr3;
       ...
    }
}