/* Autor: Rafal Uzarowicz, 300282
 * Zawartosc: Program tworzacy slownik referencji slow w tekscie podanym na standardowym wejsciu.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_WORD 30

//Counter: Wezel listy przechowujacej kolejne wystapienia danego slowa.
struct Counter{
    int line; //Zmienna przechowujaca numer linijki w ktorej wystapilo slowo.
    struct Counter* next_number; //Wskaznik na kolejny wezel listy.
};
typedef struct Counter Counter;

//WordsList: Wezel listy przechowujacej informacje o danym slowie.
struct WordsList{
    char word[ MAX_WORD + 1 ]; //Tablica zawierajaca w sobie dane slowo
    int first_line; //Pierwsze wystapienie danego slowa.
    int number; //Ilosc wystapien danego slowa
    Counter* first_counter; //Wskanik na pierwszy element listy Counter tego slowa.
    struct WordsList* next; //Wskaznik na kolejny element listy.
};
typedef struct WordsList WordsList;

/* isThereWord: Funkcja, ktora przyjmuje slowo oraz wskaznik na pierwszy element listy,
 * a nastepnie sprawdza czy to slowo wystepuje w liscie slow.
 * Jesli wystepuje to funkcja zwraca wskaznik na to slowo, jesli nie to zwraca NULL. */
WordsList* isThereWord( char word[], WordsList* head );

/* isThereCounter: Funkcja, ktora przyjmuje numer linii oraz wskaznik na poczatek listy Counter danego slowa,
 * a nastepnie sprawdza czy podane linijka juz wystepije w liscie Counter. Jesli linijka wystepuje to funkcja
 * zwraca wskaznik na wezel zawierajacy te linijke, a jesli nie wystepuje to zwraca NULL. */
Counter* isThereCounter( int line, Counter* first );

/* addCounter: Funkcja przyjmje numer linijki, wskaznik na pierwszy element listy Counter danego slowa
 * oraz wskaznik na dane slowo, a nastepnie dodaje odpowiedni wezel do listy Counter. Funkcja zwraca
 * wskaznik na nowy wezel listy Counter jesli byla ona wczesniej pusta lub wskaznik na pierwszy wezel listy
 * Counter jesli byla ona niepusta. */
Counter* addCounter( int line, Counter* first, WordsList* word );

/* isLetter: Funkcja przujmuje liczbe typu int, a nastepnie sprawdza czy ta liczba w swojej reprezentacji
 * char jest albo litera a-z albo A-Z albo cyfr¹ 0-9. Jesli tak jest to zwraca 1, a jesli nie to 0. */
int isLetter( int c );

/* findMaxNumber: Funkcja przyjuje wkaznik na poczatek listy WordsList, a nastepnie przeszukujac liste
 * element po elemencie znajduje najwieksza liczbe wystepowan slow w calym slowniku, a nastepnie zwraca
 * te liczbe. */
int findMaxNumber( WordsList* head );

/* abcOrder: Funkcja przyjmuje dwa slowa, a nastepnie zwraca 1 jesli pierwsze slowo jest wyzej w
 * kolejnosci alfabetycznej lub 0 jesli pierwsze slowo jest nizej w kolejnosci alfabetycznej. */
int abcOrder( char first[], char second[] );

/* clearTab: Funkcja przyjmuje dowolna tablice, a nastepnie zeruje wszystkie wartosci w podanej tablicy. */
void clearTab( char tab[] );

/* addWord: Funkcja przyjmuje slowo zapisane w tablicy char, numer linii oraz wskaznik na poczatek listy,
 * a nastepnie dodaje to slowo do slownika w odpowiednim miejscu tak ,aby slowa
 * zachowalyy porzadek alfabetyczny. */
void addWord( char word[], int line, WordsList** head );

/* printList: Funkcja przyjmuje wskaznik na wskaznik na pierwszy element slownika, a nastepnie wypisuje wszystkie slowa slownika
 * w odpowiedniej kolejnosci tak, aby slowa procz porzadku alfabetycznego byly ustawione wedlug czestosci
 * wystepowania w linijkach tekstu. */
void printList( WordsList* head );

/* listFree: Funkcja przyjmuje wkaznik na element slownika, a nastepnie zwalnia pamiec calego slownika
 * poczawszy od podanego wskaznika. */
void listFree( WordsList* Word );

/* nodeFree: Funkcja przyjmuje wskanik na element listy Counter, a nastepnie zwalnia pamiec calego slownika
 * Counter poczawszy od podanego wskaznika. */
void nodeFree( Counter* node );


int main (){
    WordsList* head =NULL;                                              //Zmienna wskazujaca poczatek listy slow.
    char word[ MAX_WORD + 1 ];                                          //Tablica do przechowywania slowa do slownika.
    clearTab( word );                                                   //Czysczenie tablicy do slowa.
    int c = 0;                                                          //Zmienna do przechowywania aktualnie rozpatrywanego znaku z wejscia.
    int line=1;                                                         //Zmienna do przechowywania aktualnie rozpatrywanej linijki.
    while( EOF != ( c = getchar() ) ){
        if( isLetter( c ) ){                                            // Przymowana litera spelnia wymagania potrzebne do wpisania do tablicy slowa.
            for( int j = 0 ; isLetter( c ) && j < MAX_WORD ; ++j ){     //Zbieranie znakow do utworzenia slowa.
                word[ j ] = ( char ) c;
                word[ j + 1 ] = '\0';
                c = getchar();
            }
            WordsList* current = NULL;                                  //current - zmienna pomocnicza pokazujaca na ktorym elemencie listy jestesmy.
            if( NULL != ( current = isThereWord( word, head ) ) ){      //Podane slowo jest juz w slowniku.
                if( NULL == current->first_counter ) {                  //Slowo nie ma listy Counter, wystapilo tylko w jednej linii.
                    if( current->first_line != line ){                  //Slowo nie powtarza sie w danej linijce.
                        current->first_counter = addCounter( line, current->first_counter, current );
                    }
                }else{                                                  //Slowo ma liste Counter, wystapilo w wiecej niz jednej linijce.
                    addCounter( line, current->first_counter, current ); //Dodanie wezla listy Counter.
                }
            }else{                                                      //Podanego slowa nie ma w slowniku.
                addWord( word, line, &head );                           //Dodanie nowego slowa do slownika w odpowiednim miejscu.
            }
        }
        clearTab( word );                                               //Wyczyszczenie tablicy do slowa.
        if( c == '\n' ){
            ++line;                                                     //Przejscie do kolejnej linijki w przypadku wystapienia znaku nowej linii.
        }
    }
    printList(head);                                                    //Wypisanie slownika na ekran.
    listFree(head);                                                     //Zwolnienie zaalokowanej pamieci.
    return 0;
}


WordsList* isThereWord( char word[], WordsList* head ){
    WordsList* current = head;                                          //Zmienna current bedzie wskaznikiem na aktualnie sprawdzany wezel.
    while( current != NULL )                                            //Sprawdzamy dopoki nie dojdziemy do konca listy.
    {
        if( strcmp( current->word, word ) == 0 )                        //Sprawdzamy czy podane slowo wystepuje w sprawdzanym wezle.
            return current;                                             //Jesli slowo wystepuje to zwracamy wskazink na dany wezel.
        current = current->next;                                        //Jesli nie wystepuje przechodzimy do kolejnego wezla.
    }
    return NULL;                                                        //Jesli doszlismy do konca listy zwracamy NULL.
}

Counter* isThereCounter( int line, Counter* first ){
    Counter* current = first;                                           //Zmienna current bedzie wskaznikiem na aktualnie sprawdzany wezel.
    while( current != NULL )                                            //Sprawdzamy dopoki nie dojdziemy do konca listy.
    {
        if( line == current->line )                                     //Sprawdzamy czy slowo wystapilo w danej linijce.
            return current;                                             //Jesli wystapilo zwracamy wskaznik na wezel listy Counter.
        current = current->next_number;                                 //Jesli nie wystapilo przechodzimy do kolenego wezla.
    }
    return NULL;                                                        //Jesli nie wystapilo to zwracamy NULL.
}

Counter* addCounter( int line, Counter* first, WordsList* word ){
    Counter* newCounter = malloc( sizeof( Counter ) );                  //Alokujemy pamiec na nowy wezel listy Counter.
    if( NULL == newCounter ){                                           //Zabezpieczenie przed brakiem pamieci.
        puts( "Brak pamieci." );
        exit( EXIT_FAILURE );
    }
    newCounter->line = line;                                            //Ustawiamy odpowiednie wartosci w wezle.
    if( NULL == first ){                                                //Jesli lista Counter danego slowa byla pusta tworzymy odpowiednio pierwszy wezel.
        newCounter->next_number = NULL;
        ++( word->number );                                             //Zwiekszamy liczby wystapien danego slowa.
        return newCounter;                                              //Zwracamy wskaznik na nowy element, ktory jest teraz pierwszy.
    }
    Counter* tmp = first;                                               //Zmienna pomocnicza wskazujaca nam aktualnie sprawdzany wezel.
    if( NULL == isThereCounter( line, first ) ){                        //Sprawdzamy czy linia juz wystapila.
        ++( word->number );                                             //Zwiekszamy liczbe wystapien danego slowa.
        while( NULL != tmp ){                                           //Wykonujemy dopoki nie dojdziemy na koniec listy.
            if( NULL== tmp->next_number ){                              //Sprawdzamy czy sprawdzany element wskazuje na koniec listy.
                tmp->next_number = newCounter;                          //Dodajemy utworzony wezel na koniec listy.
                newCounter->next_number = NULL;                         //Utworzony wezel wskazuje na koniec listy.
                return first;                                           //Zwracamy wskaznik na pierwszy element, ktory sie nie zmienil.
            }
            tmp = tmp->next_number;                                     //Przechodzimy do kolejnego wezla.
        }
    }
}

int abcOrder( char first[], char second[] ){
    for( int i = 0; i <= strlen( first ) ; ++i ){                       //Petla sprawdzajaca po kolei kolejne litery.
        if( first[ i ] < second[ i ] ){
            return 1;                                                   // Slowo first jest wyzej alfabetycznie.
        }else if(first[i]>second[i]){
            return 0;                                                   //Slowo first jest nizej alfabetycznie.
        }
    }
    return 0;                                                           //Slowo first jest nizej alfabetycznie.
}

int isLetter( int c ) {
    if ( ( c >= '0' && c <= '9' ) || ( c >= 'A' && c <= 'Z' ) || ( c >= 'a' && c <= 'z' ) ){
        return 1;                                                       //Znak spelnia wymagania do wpisania do slowa.
    }else{
        return 0;                                                       //Znak nie spelnia wymagan do wpisania do slowa.
    }
}

int findMaxNumber( WordsList* head ){
    WordsList* tmp = head;                                              //Wskaznik na aktualnie sprawdzany wezel.
    int record = 0;                                                     //Najwieksza liczba wystapien w calej liscie.
    while( tmp ){                                                       //Sprawdzamy dopoki nie skonczy sie lista.
        if( record < tmp->number ){                                     //Sprawdzamy czy rekord jest mniejszy liczby w sprawdzanym wezle.
            record=tmp->number;                                         //Jesli rekord jest mniejszy to zamieniamy.
        }
        tmp = tmp->next;                                                //Przechodzimy do kolejnego wezla.
    }
    return record;                                                      //Zwracamy najwieksza liczbe wustapien.
}

void addWord( char word[], int line, WordsList** head ){
    WordsList* newWord = malloc( sizeof( WordsList ) );                 //Alokujemy pamiec dla nowego wezla.
    if( NULL == newWord ){                                              //Zabezpieczenie przed brakiem pamieci.
        puts( "Brak pamieci." );
        exit( EXIT_FAILURE );
    }
    strcpy( newWord->word, word );                                      //Ustawiamy odpowiednie wartosci w nowym wezle na domyslne.
    newWord->first_line = line;
    newWord->number = 1;
    newWord->first_counter = NULL;
    newWord->next = NULL;

    if( NULL != *head ){                                                //Lista slow nie jest pusta.
        WordsList* prev_word = *head;                                   //Poprzednie slowo ustawiamy na wskaznik na poczatek listy.
        WordsList* next_word = (*head)->next;                           //Nastepne slowo ustawiamy na pierwszy elemeny listy.
        if( abcOrder( newWord->word, prev_word->word ) ){               //Nowy wezel jest wyzej niz pierwszy wezel na liscie.
            newWord->next = prev_word;                                  //Nowy wezel wskazuje na pierwszy wezel.
            *head = newWord;                                            //Wskaznik na poczcatek listy wskazuje na nowy wezel.
        }else {                                                         //Nowy wezel jest nizej niz pierwszy wezel na liscie.
            while ( NULL != next_word && next_word->number != 1 ) {     //Przechodzimy do slow ktore wystapily raz.
                prev_word = next_word;                                  //Ustawiamy poprzedni wezel na nastepny.
                next_word = next_word->next;                            //Nastepny element staje sie kolejnym wzgledem siebie.
            }
            if ( NULL == next_word ) {                                  //Nie ma nastepnego elementu listy.
                    prev_word->next = newWord;                          //Poprzedni element wskazuje na nowe slowo.
                    newWord->next = NULL;                               //Nowy element listy staje sie ostatnim.
            } else {                                                    //Istnieja kolejne elementy listy.
                while ( NULL != next_word && !abcOrder( newWord->word, next_word->word ) ){
                    //Szukamy miejsca w liscie dla nowego wezla.
                    prev_word = next_word;                              //Poprzedni element staje sie nastepnym.
                    next_word = next_word->next;                        //Nastepny element staje sie kolejnym wzgledem siebie.
                }
                prev_word->next = newWord;                              //Poprzedni wezel wskazuje na nowy wezel.
                newWord->next = next_word;                              //Nowy wezel wskazuje na kolejny wezel albo koniec listy.
            }
        }
    }else{                                                              //Lista slow jest pusta.
        newWord->next = NULL;                                           //Nowe slowo wskazuje na koniec listy.
        *head = newWord;                                                //Wskaznik na poczatek listy wskazuje na nowe slowo.
    }
}

void clearTab( char tab[] ){
    for( int i=0 ; i < strlen(tab) ; ++i ){
        tab[ i ] = 0;
    }
}

void printList( WordsList* head ){
    WordsList* tmpWord = head;                                          //Zmienna wskazujaca na aktualnie wypisywane slowo.
    Counter* tmpCounter = NULL;                                         //Zmienna wskazujaca na aktualnie wypisywane wystapienia.
    int max = findMaxNumber( head );                                    //Liczba najwiekszej ilosci wystepowan.
    for( int i = max ; i>0 ; --i ){                                     //Wypisujemy od najczesciej wystepujacych.
        tmpWord = head;                                                 //Przechodzimy na poczatek listy.
        while( tmpWord ){                                               //Wypisujemy dopoki nie trafimy na koniec listy.
            if( i == tmpWord->number ){                                 //Wypisujemy jesli slowo wystapilo odpowiednia ilosc razy.
                printf( "%s %d", tmpWord->word, tmpWord->first_line );
                tmpCounter = tmpWord->first_counter;                    //Ustawiamy poczatek wypisywanej listy Counter.
                while ( tmpCounter ) {                                  //Wypisujemy dopoki nie trafimy na koniec listy Counter.
                    printf( ",%d", tmpCounter->line );
                    tmpCounter = tmpCounter->next_number;               //Przechodzimy do kolejnego wezla listy Counter.
                }
                printf( "\n" );                                         //Przechodzimy do nowej wypisywanej linii.
            }
            tmpWord = tmpWord->next;                                    //Przechodzimy do kolejnego slowa.
        }
    }
}

void listFree( WordsList* Word ){
    WordsList* prev = NULL;                                             //Zmienna pomocnicza ktora bedzie wskazywac na aktualnie czyszczony wezel.
    while( Word ){                                                      //Wykonujemy dopoki nie trafimy na koniec listy.
        prev = Word;                                                    //Ustawiamy wezel do wyczyszczenia.
        nodeFree( Word->first_counter );                                //Czyscimy liste ktora jest wskazywana w naszej liscie.
        Word = Word->next;                                              //Przechodzimy do kolejnego wezla.
        free( prev );                                                   //Czyscimy aktualny wezel.
    }
}

void nodeFree( Counter* node ){
    Counter* prev = NULL;                                               //Zmienna pomocnicza ktora bedzie wskazywac na aktualnie czyszczony wezel.
    while( node ){                                                      //Wykonujemy dopoki nie trafimy na koniec listy.
        prev = node;                                                    //Ustawiamy wezel do wyczyszczenia.
        node = node->next_number;                                       //Przechodzimy do kolejnego wezla.
        free( prev );                                                   //Czyscimy aktualnie sprawdzany wezek.
    }
}
