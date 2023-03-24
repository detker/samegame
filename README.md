# samegame
my C implementation of samegame

## specification (in polish lang):
Prostokątna plansza do jednoosobowej gry SameGame dzieli się na pola, uporządkowane w wiersze i kolumny.

Każde pole albo jest puste, albo jest na nim klocek określonego rodzaju.

Gracz usuwa z planszy grupy sąsiadujących klocków tego samego rodzaju.

Usunięcie grupy klocków jest możliwe tylko, jeśli są w niej co najmniej dwa klocki.

Po usunięciu grupy plansza jest porządkowana:
<ul>
<li>Klocki opadają na puste pola w wierszach poniżej.</li>
<li>Kolumny, w których są jakieś klocki, są przesuwane w lewo, na miejsce kolumn pustych.</li>
</ul>

Gra jest parametryzowana trzema dodatnimi liczbami całkowitymi:
<ul>
<li>WIERSZE to liczba wierszy planszy;</li>
<li>KOLUMNY to liczba kolumn planszy;</li>
<li>RODZAJE to liczba rodzajów klocków.</li>
</ul>

-------------------------------------------------------------------

Wartości parametrów gry WIERSZE, KOLUMNY i RODZAJE są określone za pomocą stałych symbolicznych, które można zdefiniować opcją -D kompilatora.

W kodzie programu są podane wartości domyślne tych stałych:
<ul>
<li>WIERSZE ma wartość 10;</li>
<li>KOLUMNY ma wartość 15;</li>
<li>RODZAJE ma wartość 4.</li>
</ul>

Program jest wywoływany z dwoma argumentami - współrzędnymi pola wybranego przez gracza. Pierwszy argument to numer wiersza, liczony od 0. Drugi argument to numer kolumny, liczony od 0. Pole z wiersza 0 i kolumny 0 jest w lewym górnym rogu planszy.

Dane programu, czytane z wejścia, to aktualny stan planszy.

Wynik programu, pisany na wyjście, to stan planszy po wykonaniu polecenia gracza.

Stan planszy określa, dla każdego pola, czy jest na nim klocek, a jeśli tak, to jaki jest rodzaj tego klocka.

Zbiór G klocków na planszy nazywamy grupą, jeśli spełnione są trzy warunki:
<ol>
<li>wszystkie klocki w zbiorze G są tego samego rodzaju;</li>
<li>od każdego klocka w zbiorze G można przejść do każdego z pozostałych klocków w tym zbiorze, wykonując tylko kroki do bezpośrednich sąsiadów w wierszu lub w kolumnie i poruszając się przy tym wyłącznie po polach, na których są klocki ze zbioru G;</li>
<li>zbioru G nie można rozszerzyć, nie łamiąc zasad 1 i 2.</li>
</ol>

Można zauważyć, że każdy klocek jednoznacznie określa grupę, do której należy.

Program:
<ol>
<li>czyta stan planszy;</li>
<li>sprawdza, czy na polu o współrzędnych określonych argumentami programu, jest klocek należący do grupy mającej co najmniej dwa elementy i jeśli tak, usuwa z planszy wszystkie klocki tej grupy;</li>
<li>porządkuje planszę;</li>
<li>pisze wynik.</li>
</ol>

Porządkując planszę, program:
<ul>
<li>dopóki jest choć jeden klocek, bezpośrednio poniżej którego, w tej samej kolumnie, jest pole puste, przesuwa ten klocek o jedną pozycję w dół;</li>
<li>dopóki jest choć jedna niepusta kolumna, bezpośrednio na lewo od której jest kolumna pusta, przesuwa wszystkie klocki tej niepustej kolumny o jedną pozycję w lewo.</li>
</ul>

Jeżeli pole o współrzędnych określonych argumentami programu jest puste lub jest na nim klocek, którego grupa jest jednoelementowa, to wynik programu jest taki sam jak dane.

-------------------------------------------------------------------------------------------

Liczba wierszy danych programu jest określona stałą WIERSZE. Każdy wiersz jest zakończony reprezentacją końca wiersza '\n'.

Liczba znaków w każdym wierszu jest określona stałą KOLUMNY.

Znak danych określa zawartość pola planszy:
<ul>
<li>znak '.' wskazuje, że pole jest puste;</li>
<li>cyfra dziesiętna, od '0' do '0' + RODZAJE - 1, reprezentuje rodzaj klocka.</li>
</ul>

Plansza opisana danymi jest uporządkowana. Nie ma na niej klocka, poniżej którego jest pole puste. Nie ma też niepustej kolumny, na lewo od której jest kolumna pusta.

Compilation and launching:
-------------------------

To **compile**, type command: **gcc @opcje -DWIERSZE=val1 -DKOLUMNY=val2 -DRODZAJE=val3 main.c -o 01**

**opcje** is a gcc configuration file, included in repo.
<br>
**WIERSZE, KOLUMNY, RODZAJE** - positive integers; RODZAJE <= 10

To **launch**, type command: **./01 arg1 arg2**

*specification provided by: MIM UW*
