# Program do realizowania operacji unarnych na macierzach, napisany w C++

Program służy do obliczania ciągu unarnych operacji na wielu macierzach kwadratowych.

Skompilowany projekt bierze dane z pliku podanego jako pierwszy argument i domyślnie wypisuje obliczone macierze do pliku podanego w drugim argumencie (w programie jest opcja do wypisania do standardowego wyjścia).

## Przykładowy plik wejściowy

Pierwsza linijka pliku posiada liczbę całkowitą będącą ilością macierzy do obliczenia.

Reszta pliku jest napisana według wzoru:
1. 1 linijka: liczba całkowita N, ilość wierszy i kolumn następującej macierzy kwadratowej.
1. N linijek: macierz kwadratowa z liczbami całkowitymi.
1. 1 linijka: ciąg operacji przedstawionych jako duże litery alfabetu. Ciąg jest zakończony znakiem '&'.

## Operacje
- Transponowanie (T);
- Odwrotne transponowanie (D);
- Odbicie lustrzane pionowe (H);
- Odbicie lustrzane poziome (V);
- Obrót o 90 stopni w lewo (A);
- Obrót o 180 stopni w lewo (B);
- Obrót o 270 stopni w lewo (C);
- Obrót o 90 stopni w prawo (X);
- Obrót o 180 stopni w prawo (Y);
- Obrót o 270 stopni w prawo (Z).