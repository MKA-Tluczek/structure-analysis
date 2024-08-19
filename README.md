# Structure analysis

## Sekcja pierwsza - operacje na strukturach danych
Katalog "1 - structure" zawiera aplikację operującą na strukturach danych.

Aplikacja pozwala na tworzenie poniższych struktur danych zawierających liczby całkowite:
* tablicy
* listy dwukierunkowej
* kopca binarnego typu max
* drzewa czerwono-czarnego

W każdej ze struktur można dokonać operacji dodawania, wyszukiwania i usuwania wybranych elementów.

W przypadku tablicy i listy dwukierunkowej, możliwe jest dodawanie elementów w dowolnym miejscu struktury.

## Sekcja druga - algorytmy grafowe
Katalog "2 - graph" zawiera aplikcję operującą na grafach.

Aplikacja umożliwia wyznaczanie najkrótszej ścieżki w grafie oraz minimalnego drzewa rozpinającego.

Najkrótszą ścieżkę w grafie można wyznaczyć algorytmem:
* Dijkstry
* Bellmana-Forda

Minimalne drzewo rozpinające można wyznaczyć algorytmem:
* Prima
* Kruskala

Informacje o grafie są przechowywane na dwa sposoby, i możliwe jest uruchomienie każdego z algorytmów na obu strukturach danych:
* Macierz sąsiedztwa
* Lista sąsiedztwa

Graf jest interpretowany jako nieskierowany w przypadku problemu MDR, a skierowany w przypadku problemu najkrótszej ścieżki.

## Wczytywanie z pliku
Aby wczytać dane z pliku, należy umieścić plik o nazwie `input.txt` w tym samym katalogu co aplikacja.

W przypadku aplikacji 1, `input.txt` powinien zawierać liczby całkowite, każda w osobnej linii. Liczby te zostaną dodane do struktury w tej samej kolejności.

W przypadku aplikacji 2, `input.txt` powinien w pierwszej linii zawierać liczbę krawędzi i wierzchołków, natomiast każda kolejna linia pliku zawiera kolejne informacje o jednej krawędzi:
* Wierzchołek początkowy krawędzi (liczony od zera)
* Wierzchołek końcowy krawędzi
* Waga/koszt krawędzi

## Eksperyment
Obie aplikacje pozwalają na wykonanie analizy czasu działania każdej z operacji dla każdego z algorytmów i struktur danych.

Eksperyment polega na wygenerowaniu zadanej liczby struktur/grafów o losowej zawartości, a następnie przeprowadzeniu na każdej z nich podanej liczby losowych operacji/uruchomień algorytmów, wraz z mierzeniem czasu ich działania.
