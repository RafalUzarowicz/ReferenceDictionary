* Rafał Uzarowicz

* Słownik referencji

* Metoda:
	1.Wczytanie poprawnego slowa z wejscia.
	2.a)Jeśli słowo jeszcze nie wystąpiło zapisanie słowa do słownika w odpowiednim miejscu.
	2.b)Jeśli słowo już wystąpiło ewentualne dopisanie do słowa numeru odpowieniej linijki występowania, bez powtórzeń.
	3.Powtórzenie czynności 1-3, aż użytkownik zakończy dopisywanie słów do słownika.
	4.Wypisanie słownika referencji.

* Ważne informacje:
	- Program przyjmuje wszystkie znaki, ale jako słowa akceptuje tylko ciągi złożone z dużych liter A-Z, małych liter a-z i cyfr 0-9.
	- Program nie zapisuje polskich znaków.
	- Program uznaje słowa do 30 znaków. Jeśli jakieś słowo ma więcej niż 30 znaków program zamienia je na na słowa po maksymalnie 30 znaków.
	- Program wypisuje słowa od najczęściej występującego słowa, gdy występowania równe to alfabetycznie.
	- Program uznaje taką kolejność alfabetyczną: cyfry>duże litery>małe litery.
	- Program należy uruchamiać w konsoli/IDE (z obsługą EOF w strumieniu wejścia) w standardzie C99.
	- Program kończy działanie gdy zostanie wysłany sygnał EOF.
	- Program wypisze odpowiedni komunikat gdy nie udało sie zaalokować potrzebnej pamięci.

* Funkcje:
	- Własne: isThereWord, isThereCounter, addCounter, isLetter, findMaxNumber, abcOrder, clearTab, addWord, printList, listFree, nodeFree
	- Z poszczególnych bibliotek: <stdio.h>: {printf, puts, getchar}, <stdlib.h>: {malloc, free}, <string.h>: {strlen, strcpy, strcmp}

* Drzewko programu:
	-main.

* Testowanie:
	-podawanie kolejnych linijek tekstu - program prawidłowo wypisuje słownik;
	-podawanie kilku linijek tekstu jednocześnie - program prawidłowo wypisuje 		słownik;
	-podanie pustej linijki - program uznaje, że przechodzimy do kolejnej linii;
	-podanie słów wiekszych niż 30 znaków - program dzieli słowa na mniejsze słowa;
	-podanie miliona linijek - progam zadzialał w pełni prawidłowo.

* Wnioski:
	Program w prawidłowy sposób tworzy słownik referencji i prawidłowo zarządza pamięcią. Program w prawdiłowy sposób zwalnia pamięć. Dzieki użyciu list do programu można wpisać z góry nieokreślone ilości słów.
