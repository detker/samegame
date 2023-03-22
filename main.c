/**
 * "SameGame"
 * https://en.wikipedia.org/wiki/SameGame
 * 
 * autor: Wojciech Krolikowski <wk450245@students.mimuw.edu.pl>
 * wersja: 1.1
 * data: 2022-12-14
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// Liczba wierszy planszy.
#ifndef WIERSZE
    #define WIERSZE 10
#endif
// Liczba kolumn planszy.
#ifndef KOLUMNY
    #define KOLUMNY 15
#endif
// Liczba rodzai klockow.
#ifndef RODZAJE
    #define RODZAJE 4
#endif

// Funkcja zamieniajaca elementy miejscami.
void zamien(char *x, char *y)
{
    char bufor = *x;
    *x = *y;
    *y = bufor;
}

// Funkcja odwracajaca tablice na okreslonym przedziale oraz w okreslonym kierunku
// (wiersze/kolumny).
void odwroc(char a[][KOLUMNY], int k, int n, int g, bool opadanie)
{
    // Wyznaczenie poczatku i konca przedzialu.
    int i = k;
    int j = n-1+k;
    
    // Jezeli funkcja, ktora wywolala te funkcje dotyczy przesuwania kolumny.
    if(opadanie)
    {
        while(i < j)
        {
            zamien(&a[i][g], &a[j][g]);
            i++;
            j--;
        }
    }
    // Jezeli funkcja, ktora wywolala te funkcje dotyczy przesuwania wiersza.
    else
    {
        while(i < j)
        {
            zamien(&a[g][i], &a[g][j]);
            i++;
            j--;
        }
    }
}

// Funkcja przesuwajaca tablice na okreslonym przedziale o k pozycji w kolumnie.
void przesun1(char plansza[][KOLUMNY], int x, int y, int k, int ktoraKolumna)
{
    bool opadanie = true;

    odwroc(plansza+y, 0, x-y+1, ktoraKolumna, opadanie);
    odwroc(plansza+y, 0, k, ktoraKolumna, opadanie);
    odwroc(plansza+y+k, 0, x-y+1-k, ktoraKolumna, opadanie);
}

// Funkcja przesuwajaca tablice na okreslonym przedziale o k pozycji we wierszu.
void przesun2(char plansza[][KOLUMNY], int ktoraKolumna, 
                int ktoryWiersz, int zeroweKolumny)
{
    int n = KOLUMNY-ktoraKolumna-zeroweKolumny;
    int k = n-1;
    bool opadanie = false;

    odwroc(plansza, ktoraKolumna, n, ktoryWiersz, opadanie);
    odwroc(plansza, ktoraKolumna, k, ktoryWiersz, opadanie);
    odwroc(plansza, ktoraKolumna+k, n-k, ktoryWiersz, opadanie);
}

// Funkcja okreslajaca po otrzymanych wspolrzednych na jaki rodzaj klocka wskazuja.
char znajdzRodzajKlocka(char plansza[][KOLUMNY], int x, int y)
{
    return plansza[y][x];
}

// Funkcja sprawdzajaca, ile zerowych kolumn znajduje się na wejsciu.
int ileZerowychKolumnPrzed(char plansza[][KOLUMNY])
{
    // Zmienna "s" zlicza zerowe kolumny.
    int s = 0;
    for(int i = KOLUMNY-1; i >= 0; i--) 
    {
        // Aby stwierdzic, czy na wejsciu znajduje sie zerowa kolumna, wystarczy sprawdzic
        // element na samym dole kolumny, tj. element kolumny w ostatnim wierszu;
        // (zgodnie ze specyfikacja: "Plansza opisana danymi jest uporzadkowana. 
        // Nie ma na niej klocka, ponizej ktorego jest pole puste.")
        if(plansza[WIERSZE-1][i] != '.') return s;
        s++;
    }
    return s;
}

// Funkcja sprawdzajaca, czy po usunieciu grupy, dana kolumna jest pusta.
bool czyKolumnaPusta(char plansza[][KOLUMNY], int indexKolumny)
{
    if(plansza[WIERSZE-1][indexKolumny] == '.')
    {
        for(int j = WIERSZE-1; j >= 0; j--)
        {
            if(plansza[j][indexKolumny] != '.') return false;
        }
        return true;
    }
    return false;
}

// Funkcja znajdujaca oraz eliminujaca grupe klockow.
void znajdzGrupe(char plansza[][KOLUMNY], int x, int y, char rodzajKlocka, 
                    int *maksKolumna, int *minKolumna)
{
    // Blok kodu uruchamiajacy sie, gdy wspolrzedne klocka nie wykraczaja poza zakres
    // planszy oraz gdy wspolrzedne wskazuja na klocek tego samego rodzaju,
    // co ten okreslony przez funkcje "znajdzRodzajKlocka".
    if((x >= 0) && (x < KOLUMNY) && (y >= 0) && (y < WIERSZE) && 
        (plansza[y][x] == rodzajKlocka))
    {
        // Dwie instrukcje warunkowe wyznaczajace zakres kolumn, w których doszło 
        // do usunięcia klockow -> dane przydatne do uporzadkowania planszy.
        if(*minKolumna > x) *minKolumna = x;
        if(*maksKolumna < x) *maksKolumna = x;
        
        // "Eliminacja" klocka
        plansza[y][x] = '.';
        
        // Ponizsze wywolania rekurencyjne znajduja nastepne klocki grupy,
        // zgodnie z definicja grupy znajdujacej sie w specyfikacji.
        znajdzGrupe(plansza, x, y+1, rodzajKlocka, maksKolumna, minKolumna);
        znajdzGrupe(plansza, x, y-1, rodzajKlocka, maksKolumna, minKolumna);
        znajdzGrupe(plansza, x-1, y, rodzajKlocka, maksKolumna, minKolumna);
        znajdzGrupe(plansza, x+1, y, rodzajKlocka, maksKolumna, minKolumna);
    }
}

// Funkcja odpowiadajaca za opadanie klockow na puste pola w wierszach ponizej.
void opadanie(char plansza[][KOLUMNY], int ktoraKolumna)
{
    // Zmienne "x" i "y" okreslaja indeksy: poczatkowy i koncowy w kolumnie,
    // pomiedzy ktorymi spodziewamy sie porzadkowania.
    int x = WIERSZE-1;
    int y = 0;
    while((y < WIERSZE) && (plansza[y][ktoraKolumna] == '.')) y++;
    while((x >=0 ) && (plansza[x][ktoraKolumna] != '.')) x--;

    // Blok kodu wykonujacy sie do momentu, az w kolumnie, pomiedzy klockami a
    // pustymi polami nie bedzie jednej, jednoznacznej granicy.
    if(y < x)
    {
        // Przesuniecie wszystkich elementow w kolumnie o 1 w dol.
        przesun1(plansza, x, y, 1, ktoraKolumna);
        // Wywolanie rekurencyjne.
        opadanie(plansza, ktoraKolumna);
    }
}

// Funkcja przesuwajaca pusta kolumne na koniec
void przesuniecieKolumny(char plansza[][KOLUMNY], int indexKolumny, 
                            int zeroweKolumnyNaKoncu)
{
    for(int k = 0; k < WIERSZE; k++)
    {
        przesun2(plansza, indexKolumny, k, zeroweKolumnyNaKoncu);
    }
}

void porzadkuj(char plansza[][KOLUMNY], int maksKolumna, int minKolumna, int zeroweKolumnyNaKoncu)
{
    // Zmienna zawierajaca informacje ile aktualnie zerowych kolumn 
    // znajduje sie na koncu planszy.
    for(int i = minKolumna; i <= maksKolumna; i++)
    {
        // Jezeli kolumna (oczywiscie taka, z ktorej wyeliminowano kolcek/klocki)
        // nie jest pusta - uruchom funkcje odpowiadajaca za opadanie klockow na puste
        // pola w wierszach ponizej.
        if(!czyKolumnaPusta(plansza, i)) opadanie(plansza, i);
    }

    int k = minKolumna;
    while((k <= maksKolumna) && (k < (KOLUMNY-zeroweKolumnyNaKoncu)))
    {
        // Jezeli kolumna jest pusta nastapi przesuniecie jej na koniec planszy.
        // Tym samym sprawdzajac ponownie ten sam indeks kolumny, w rzeczywistosci
        // bedziemy sprawdzac nastepna kolumne, ktora rowniez moglaby byc
        // pusta kolumna. Zatem wartosc zmiennej "k" nie ulega zmianie.
        if(czyKolumnaPusta(plansza, k))
        {
            przesuniecieKolumny(plansza, k, zeroweKolumnyNaKoncu);
            // Zwiekszenie ilosci zerowych kolumn na koncu planszy.
            zeroweKolumnyNaKoncu++;
        }
        // Jezeli kolumna nie jest pusta, zmienna k ulega inkrementacji.
        // Zatem trafimy do kolejnej kolumny.
        else k++;
    }
}

// Funkcja wyswietlajaca plansze po usunieciu grupy klockow oraz po uporzadkowaniu.
void wyswietlPlansze(char plansza[][KOLUMNY])
{
    for(int i = 0; i < WIERSZE; i++)
    {
        for(int j = 0; j < KOLUMNY; j++)
        {
            printf("%c", plansza[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    assert(argc>=0);
    // Przypisanie do zmiennych i konwersja argumentow danych
    // podczas wywolania programu z typu char na int.
    int x = atoi(argv[2]);
    int y = atoi(argv[1]);

    // Plansza o wymiarach WIERSZExKOLUMNY.
    char plansza[WIERSZE][KOLUMNY];

    // Deklaracja zmiennych okreslajacych zakres grupy klockow.
    int maksKolumna = 0, minKolumna = KOLUMNY-1;

    // Wczyt danych wejsciowych.
    for(int i = 0; i < WIERSZE; i++) 
    {
        for(int j = 0; j < KOLUMNY; j++) scanf(" %c", &plansza[i][j]);
    }

    // Przypisanie do zmiennej rodzaju klocka.
    char rodzajKlocka = znajdzRodzajKlocka(plansza, x, y);

    // Obliczenie ilosci zerowych kolumn przed eliminacja grupy.
    int zeroweKolumnyNaKoncu = ileZerowychKolumnPrzed(plansza);

    // Blok kodu uruchamiajacy sie jezeli bezpośrednio w pobliżu klocka, 
    // ktorego pozycja jest definiowana przez "x" i "y" znajduje sie,
    // w którymś kierunku, klocek tego samego rodzaju (rowniez nalezacy do grupy)
    // oraz jednoczesnie nie wykracza on poza zakres planszy.
    if((plansza[y][x] != '.') && (((x > 0) && (plansza[y][x-1] == rodzajKlocka)) || 
        ((x < KOLUMNY-1) && (plansza[y][x+1] == rodzajKlocka)) || 
        ((y < WIERSZE-1) && (plansza[y+1][x] == rodzajKlocka)) || 
        ((y > 0) && (plansza[y-1][x] == rodzajKlocka))))
    {
        znajdzGrupe(plansza, x, y, rodzajKlocka, &maksKolumna, &minKolumna);
        porzadkuj(plansza, maksKolumna, minKolumna, zeroweKolumnyNaKoncu);
    }

    wyswietlPlansze(plansza);

    return 0;
}