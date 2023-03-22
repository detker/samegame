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
