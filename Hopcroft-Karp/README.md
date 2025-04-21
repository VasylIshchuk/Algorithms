# Treść zadania

Elżbieta Harmonia jest zapalonym graczem warcabów. Jednakże jej zaawansowane umiejętności przewidywania, logicznego myślenia oraz perfekcja w prowadzeniu rozgrywki spowodowały znudzenie tą grą planszową. Nasza bohaterka rozważa nowe zasady i różne urozmaicenia rozgrywki.


Rozważa dowolnie dużą kwadratową szachownicę o wymiarach N x N, gdzie N jest liczbą naturalną. Pola na szachownicy numerowane są od 0 do N - 1. Dodatkowo bierki na planszy można rozmieścić tylko na początku rozgrywki i nie można ich przesuwać. Kontynuując pionki należy ustawić na wszystkich polach planszy, co znaczy, że białe pionki zajmują wszystkie białe pola, zaś czarne wszystkie czarne pola. Ponadto pionki przyjmują jedną z czterech funkcji, które wpływają na to jakie pionki może zbić bierka i przez jakie pionki będzie bita. Wyróżniamy następujący typy bierek:

    0 - pionek jest zamrożony, nie może zbić ani zostać zbity,
    1 - pionek bije jeden z pionków znajdujących się na polach: pole oddalone o 3 jednostki w linii prostej przed sobą lub pole oddalone o 2 jednostki w lini prostej przed sobą i o jedną jednostkę w prawo, bądź lewo,
    2 - pionek bije jeden z pionków znajdujących się na polach: pole oddalone o 1 jednostkę w linii prostej przed sobą lub pole oddalone o 1 jednostkę w prawo, bądź lewo,
    3 - pionek bije jeden z pionków znajdujących się na polach: pole oddalone o 1 jednostkę w linii prostej przed sobą lub pole oddalone o 2 jednostki w lini prostej przed sobą i o jedną jednostkę w prawo, bądź lewo.
Należy dodać, że Elżbieta w celu uproszczenia rozgrywki, wprowadziła dodatkową zasadę. Mianowicie, jeżeli jedna bierka (A) może być zbita przez inną bierkę (B), to ta bierka (A) także może zbić taką bierkę (B). Kierunek bicia pionów białych to zachód (w lewo), zaś czarnych to wschód (w prawo), a w lewym górnym rogu (północny-zachód) znajduje się pole czarne.

Celem rozgrywki jest takie rozstawienie pionów o odpowiednich funkcjach, aby na szachownicy zostało jak najmniej wszystkich pionów. Wygrywa ta osoba, której po analizie rozstawienia, zostanie ich więcej. Analiza rozgrywki przebiega tak, że szuka się możliwie największego powiązania pomiędzy polami obu zawodników tak, aby zostało zbite, jak najwięcej par bierek. Z takich par bierek zdejmujemy z szachownicy tylko bierki naszego przeciwnika. Podczas analizy sprawdzamy jedynie powiązania, które generują nasze bierki pamiętając, że nasze bierki i bierki przeciwnika o funkcji 0 są wykluczone z rozgrywki. Powyższa analiza wydaje się bardzo skomplikowana, stąd Elżbieta prosi Cię o pomoc i zaimplementowanie silnika, który pomoże w rozważeniu rozgrywki. Prosi Cię o zaimplementowanie algorytmu, który przedstawi maksymalną liczbę pionów, które nie zostaną zbite. Jako, że ulubionym kolorem naszej bohaterki jest kolor czarny, napisz program, który przeanalizuje rozstawienie czarnych pionów i zwróci liczbę bierek, która pozostanie na szachownicy.


### WEJŚCIE

Algorytm na wejściu otrzymuje liczbę naturalną N, która mówi o wielkości szachownicy. Następnie powinna wczytać N x N liczb naturalnych, które określają funkcje bierek na odpowiednich pozycjach.

    0 <= N <= 32000

### WYJŚCIE

Na wyjściu algorytm powinien wypisać maksymalną liczbę bierek, które pozostaną na planszy.

## Przykład

### PRZYKŁADOWE DANE WEJŚCIOWE

    5
    1 1 1 1 1
    1 1 1 1 1
    0 0 1 0 1
    1 1 1 1 1
    1 1 1 1 1

### PRZYKŁADOWE DANE WYJŚCIOWE

    19