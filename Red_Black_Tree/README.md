# Treść zadania

﻿
Wydarzenia opisywane w tym zadaniu rozgrywają się w latach 20. XX wieku, tuż po zakończeniu I wojny światowej. Opisują historię Tomasza Forda, który jest przewodniczącym organizacji przestępczej “Mizerni ślepcy”. Budząca powszechny strach organizacja zawdzięcza swoją nazwę noszonym przez jej członków czarnych okularów tzw. leonków. Jako, że około 1920 roku okulary przeciwsłoneczne dopiero zyskiwały popularność, nie trudno było zapamiętać i rozróżnić aktywistów tej grupy. Gang składa się przede wszystkim z członków rodziny naszego bohatera, która prowadzi zakład bukmacherski. Jednakże nasz bohater ma ambicje poszerzać swoje wpływy, a co za tym idzie narobił sobie wrogów.

﻿
Ford spędza ostatnio bardzo dużo czasu na analizowaniu listy potencjalnie zagrażających mu osób. Są wśród nich politycy, ukryci agenci specjalni, członkowie innych gangów, bezkompromisowy inspektor policji Czesław Obozowy vel Dzwon, a nawet pani z pobliskiego warzywniaka. Nasz bohaterka lubi porządek, szczególnie w swoich interesach. Właśnie dlatego jego lista jest uszeregowana od osób najniebezpieczniejszych do tych mniej niebezpiecznych. Co ważne, miejsca na liście dynamicznie się zmieniają, np. jeżeli pani Krysia z warzywniaka podejrzanie długo wydaje resztę, to po chwili Tomek musi przepisywać listę przenosząc ją o kilka miejsc w górę. Oczywiście czasami wykonuje również inne operacje, takie jak zamiana osób miejscami czy dopisanie nowej. Nasz bohater obawia się jednak, że jego notes może wpaść w niepowołane ręce. Właśnie dlatego nadała wszystkim osobom unikalne pseudonimy. Jak można się domyślić prowadzenie takiego notatnika jest bardzo trudne i pracochłonne.

﻿
Mimo wszystko nasz bohater wyprzedzał intelektualnie swoją epokę i wpadł na pewien genialny pomysł. Zaprojektował bardzo skomplikowaną strukturę, na której łatwo można było nanosić zmiany i odtworzył tą strukturę na tablicy w swojej nieznanej nikomu kryjówce. Przypinał do tablicy pseudonimy zagrażających mu osób czarnymi lub czerwonymi od rdzy gwoźdźmi. Na bazie pewnych określonych zasad wykonywał operacje (takie jak zamiana osób miejscami) na tablicy odpowiednio przepinając gwoździe. Należy zaznaczyć, że w latach 20-tych nie było mowy o pierwszych komputerach, a tym bardziej nieznane były tak zaawansowane struktury danych jako samoorganizujące się binarne drzewa poszukiwań. ﻿

﻿
Twoim zadaniem jest odtworzenie tej zaawansowanej struktury i przedstawienie listy najniebezpieczniejszych konkurentów naszego bohatera po tym, gdy wykonał na tej liście pewne określone operacje. ﻿

## Wejście:

W pierwszej linii wejścia program otrzymuje liczbę n oznaczającą początkową liczbę osób na liście. Następnie w n liniach program otrzymuje ciągi znaków s będących pseudonimami osób. Zakładamy, że pierwsza osoba na liście najbardziej zagraża Tomaszowi. W kolejnym kroku program otrzymuje liczbę m będącą ilością operacji do wykonania. Na koniec w m liniach program otrzymuje opisy operacji. Pierwszy znak zawsze oznacza akcję do wykonania, a po nim pojawiają się stosowne dane zgodnie z poniższym opisem:

    a s – dodanie osoby o pseudonimie s na koniec listy, gdzie s jest ciągiem znaków
    m s x – przesunięcie osoby o pseudonimie s na liście o x miejsc, gdzie s jest ciągiem znaków, a x liczbą całkowitą (jeżeli x jest dodatnie to przesuwamy osobę w górę listy, w przeciwnym wypadku w dół)
    r s1 s2 – zamiana miejscami osoby o pseudonimie s1 z osobą o pseudonimie s2, gdzie s1 i s2 są ciągiem znaków

## Wyjście:

Na wyjściu program powinien wypisać listę pseudonimów poczynając od osoby najniebezpieczniejszej.
    
    1 < n ≤ 50000
    
    1 < m ≤ 10000

### Przykładowe wejście:

    5
    Okruszek
    Tester
    Interfejs
    Agent
    Scyzoryk
    4
    r Okruszek Interfejs
    a Kontakt
    m Kontakt 2
    m Interfejs -1

### Przykładowe wyjście:

    Tester
    Interfejs
    Okruszek
    Kontakt
    Agent
    Scyzoryk