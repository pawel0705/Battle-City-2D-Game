# A-poorly-written-Battle-City-game

Gra inspirowana grą-Battle City. Do jej napisania wykorzystano język C++ oraz multimedialną bibliotekę graficzną SFML 2.5.

# Sterowanie

Poruszanie się: strzałki - lewo, prawo, góra, dół
Strzał: Spacja
Zatwierdzanie wyboru: Enter
Powrót (i zapis jeżeli jest to możliwe): Esc

# Tryb - Play Game

Gracz zostaje przeniesiony do listy wyboru map. Porusza się po niej strzałkami w górę i dół. Zatwierdza wybór klawiszem "Enter". Po wybraniu mapy następuje główna część rozgrywki. Celem gracza jest zniszczenie 10 przeciwników. Jeżeli gracz umrze lub baza zostanie zniszczona (zielony orzeł) następuje koniec gry, który traktowany jest jako porażka. Gracz porusza się czołgiem używając strzałek. Strzał jest oddawany po naciśnięciu klawisza "Spacja".

Podczas gry na mapie pojawiają się bonusy. Po jego zebraniu gracz zostanie nagrodzony w postaci: pozbycia się wszystkich przeciwników na mapie (nie liczy się jako zabójstwo przeciwnika, pomocne podczas odciągania od bazy), ulepszenia czołgu, dodatkowego życia, naprawy ścian otaczających bazę, zamrożenia przeciwników.

Po zniszczeniu 10 przeciwników lub porażce gracz zostaje przeniesiony do podsumowania zdobytych punktów, zniszczonych przeciwników oraz rekordu punktów. Nowy rekord jest automatycznie zapisywany. Po kliknięciu "Enter" gracz zostaje przeniesiony do menu głównego.

# Tryb - Create Map

W tym trybie gracz może stworzyć swoją własną mapę (ale o ograniczonej wielkości). Gracz przesuwa czołgiem (strzałkami) co 64 piksele. Klikając spację wybiera blok, który ma zostać położony. Wybór zostaje zatwierdzony klawiszem "Enter". Jeżeli gracz nie zatwierdzi bloku (kliknie spację, strzałki) blok zostanie usunięty. Po kliknięciu "ESC" gracz zostaje przeniesiony do menu głównego, a jego mapa zostanie automatycznie zapisana. Jej nazwa (która jest ustawiana automatycznie) będzie widoczna na dole listy wyboru map. By usunąć mapę trzeba to zrobić ręcznie w plikach gry.
