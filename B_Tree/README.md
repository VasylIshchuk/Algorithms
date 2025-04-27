# Treść zadania

W biurze firmy Rednud Nilffim, znanej firmy zajmującej się sprzedażą papieru i artykułów biurowych, pojawia się potrzeba cyfryzacji informacji o produktach. W szczególności, że cyfryzacja danych jest powszechnym zjawiskiem. Praktycznie wszystkie dane przechowane są na dyskach twardych. Ponadto, utworzenie takiego zbioru informacji i zachowanie go formie bajtów na dysku jest dużym wyzwaniem. Z kolei zlokalizowanie odpowiedniego klucza, hasła powinno być możliwie szybkie.


Michał Szkot, menedżer oddziału, postanawia stworzyć cyfrową encyklopedię, która będzie zawierać szczegółowe informacje o każdym produkcie oferowanym przez firmę. Informacje te mają być łatwo dostępne dla wszystkich pracowników, aby mogli szybko odnaleźć potrzebne dane o papierze, długopisach, zszywaczach itp. Hasła (nazwy produktów) powinny być ułożone w pewnym logicznych porządku, dzięki czemu możliwe będzie szybkie odnalezienie właściwej informacji.

## WEJŚCIE

W pierwszej linii wejścia znajduje się liczba naturalna n, a następnie w kolejnych n liniach jedna z dwóch następujących operacji:
    
    1) hasło: objaśnienie
    2) hasło
Operacja (1) zapisuje na dysku nowe hasło, wraz z jego objaśnieniem. Polecenie (2) jest zapytaniem o wybrane hasło.

    0 <= n <= 32000

## WYJŚCIE

Dla każdego zapytania należy wypisać objaśnienie wyszukiwanego hasła lub słowo BRAK, jeśli takiego hasła brakuje w cyfrowej encyklopedii firmy Rednud Nilffim.

### PRZYKŁADOWE DANE WEJŚCIOWE

    6
    Papier A4: Najwyzszej jakosci papier do drukarek.
    Marker permanentny: Niezmywalny marker do tablic.
    Marker permanentny
    Zszywacz
    Zszywacz biurowy: Wytrzymaly zszywacz do dokumentow.
    Zszywacz biurowy

### PRZYKŁADOWE DANE WYJŚCIOWE

    Niezmywalny marker do tablic.
    BRAK
    Wytrzymaly zszywacz do dokumentow.

## UWAGA

Rozwiązanie powinno wykorzystywać samodzielną implementację B-drzew, gdzie parametr T charakterystyczny dla B-drzewa zawiera się w przedziale [10, 20].