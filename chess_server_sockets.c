//
// Created by Bartosz Kruczek on 29/12/2020.
//

#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <AppleEXR.h>

#define PUSTE 12
#define WYGRANA 1000
#define PRZEGRANA -1000
// heurystyki działające.
int heurytyki[13][8][8] = {
        // król
        {
                {PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA},
                {PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA},
                {PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA},
                {PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA},
                {PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA},
                {PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA},
                {PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA},
                {PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA},
        },
        // hetman
        {
                {-176, -178, -178, -179, -179, -178, -178, -176},
                {-178, -180, -180, -180, -180, -180, -180, -178},
                {-178, -180, -181, -181, -181, -181, -180, -178},
                {-179, -180, -181, -181, -181, -181, -180, -179},
                {-180, -180, -181, -181, -181, -181, -180, -179},
                {-178, -181, -181, -181, -181, -181, -180, -178},
                {-178, -180, -181, -180, -180, -180, -180, -178},
                {-176, -178, -178, -179, -179, -178, -178, -176},
        },
        // wieża
        {       {-100, -100, -100, -100, -100, -100, -100, -100},
                {-101, -102, -102, -102, -102, -102, -102, -101},
                {-99,  -100, -100, -100, -100, -100, -100, -99},
                {-99,  -100, -100, -100, -100, -100, -100, -99},
                {-99,  -100, -100, -100, -100, -100, -100, -99},
                {-99,  -100, -100, -100, -100, -100, -100, -99},
                {-99,  -100, -100, -100, -100, -100, -100, -99},
                {-100, -100, 100,  -101, -101, -100, -100, -100},
        },
        // goniec
        {
                {-56,  -58,  -58,  -58,  -58,  -58,  -58,  -56},
                {-58,  -60,  -60,  -60,  -60,  -60,  -60,  -58},
                {-58,  -60,  -61,  -62,  -62,  -61,  -60,  -58},
                {-58,  -61,  -61,  -62,  -62,  -61,  -61,  -58},
                {-58,  -60,  -62,  -62,  -62,  -62,  -60,  -58},
                {-58,  -62,  -62,  -62,  -62,  -62,  -62,  -58},
                {-58,  -61,  -60,  -60,  -60,  -60,  -61,  -58},
                {-56,  -58,  -58,  -58,  -58,  -58,  -58,  -56},
        },
        // skoczek
        {
                {-50,  -52,  -54,  -54,  -54,  -54,  -52,  -50},
                {-52,  -56,  -60,  -60,  -60,  -60,  -56,  -52},
                {-54,  -60,  -62,  -63,  -63,  -62,  -60,  -54},
                {-54,  -61,  -63,  -64,  -64,  -63,  -61,  -54},
                {-54,  -60,  -63,  -64,  -64,  -63,  -60,  -54},
                {-54,  -61,  -62,  -63,  -63,  -62,  -61,  -54},
                {-52,  -56,  -60,  -61,  -61,  -60,  -56,  -52},
                {-50,  -52,  -54,  -54,  -54,  -54,  -52,  -50},
        },
        // pionek
        {
                {-20,  -20,  -20,  -20,  -20,  -20,  -20,  -20},
                {-30,  -30,  -30,  -30,  -30,  -30,  -30,  -30},
                {-22,  -22,  -24,  -26,  -26,  -24,  -22,  -22},
                {-21,  -21,  -22,  -25,  -25,  -22,  -21,  -21},
                {-20,  -20,  -20,  -24,  -24,  -20,  -20,  -20},
                {-21,  -19,  -18,  -20,  -20,  -18,  -19,  -21},
                {-21,  -22,  -22,  -16,  -16,  -22,  -22,  -21},
                {-20,  -20,  -20,  -20,  -20,  -20,  -20,  -20},
        },
        // król komputera
        {
                {WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA},
                {WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA},
                {WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA},
                {WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA},
                {WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA},
                {WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA},
                {WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA},
                {WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA,   WYGRANA}
        },
        // hetman komputera
        {
                {176,  178,  178,  179,  179,  178,  178,  176},
                {178,  180,  180,  180,  180,  180,  180,  178},
                {178,  180,  181,  181,  181,  181,  180,  178},
                {179,  180,  181,  181,  181,  181,  180,  179},
                {180,  180,  181,  181,  181,  181,  180,  179},
                {178,  181,  181,  181,  181,  181,  180,  178},
                {178,  180,  181,  180,  180,  180,  180,  178},
                {176,  178,  178,  179,  179,  178,  178,  176},
        },
        // wieża komputera
        {       {100,  100,  100,  101,  101,  100,  100,  100},
                {99,   100,  100,  100,  100,  100,  100,  99},
                {99,   100,  100,  100,  100,  100,  100,  99},
                {99,   100,  100,  100,  100,  100,  100,  99},
                {99,   100,  100,  100,  100,  100,  100,  99},
                {99,   100,  100,  100,  100,  100,  100,  99},
                {101,  102,  102,  102,  102,  102,  102,  101},
                {100,  100,  100,  100,  100,  100,  100,  100},
        },
        // goniec komputera
        {
                {56,   58,   58,   58,   58,   58,   58,   56},
                {58,   61,   60,   60,   60,   60,   61,   58},
                {58,   62,   62,   62,   62,   62,   62,   58},
                {58,   60,   62,   62,   62,   62,   60,   58},
                {58,   61,   61,   62,   62,   61,   61,   58},
                {58,   60,   61,   62,   62,   61,   60,   58},
                {58,   60,   60,   60,   60,   60,   60,   58},
                {56,   58,   58,   58,   58,   58,   58,   56},
        },
        // skoczek komputera
        {
                {50,   52,   54,   54,   54,   54,   52,   50},
                {52,   56,   60,   60,   60,   60,   56,   52},
                {54,   60,   62,   63,   63,   62,   60,   54},
                {54,   61,   63,   64,   64,   63,   61,   54},
                {54,   60,   63,   64,   64,   63,   60,   54},
                {54,   61,   62,   63,   63,   62,   61,   54},
                {52,   56,   60,   61,   61,   60,   56,   52},
                {50,   52,   54,   54,   54,   54,   52,   50},
        },
        // pionek komputera
        {
                {20,   20,   20,   20,   20,   20,   20,   20},
                {21,   22,   22,   16,   16,   22,   22,   21},
                {21,   19,   18,   20,   20,   18,   19,   21},
                {20,   20,   20,   24,   24,   20,   20,   20},
                {21,   21,   22,   25,   25,   22,   21,   21},
                {22,   22,   24,   26,   26,   24,   22,   22},
                {30,   30,   30,   30,   30,   30,   30,   30},
                {20,   20,   20,   20,   20,   20,   20,   20}
        },
        // puste
        {
                {0,    0,    0,    0,    0,    0,    0,    0},
                {0,    0,    0,    0,    0,    0,    0,    0},
                {0,    0,    0,    0,    0,    0,    0,    0},
                {0,    0,    0,    0,    0,    0,    0,    0},
                {0,    0,    0,    0,    0,    0,    0,    0},
                {0,    0,    0,    0,    0,    0,    0,    0},
                {0,    0,    0,    0,    0,    0,    0,    0},
                {0,    0,    0,    0,    0,    0,    0,    0},
        }

};
//maksymalna liczba kierunków ruchu dla poszcxzegolnych figur
int MAX_KIERUNKI[13] = {8, 8, 4, 4, 8, 3, 8, 8, 4, 4, 8, 3, 0};

//maksymalna liczba pól ruchu dla poszcxzegolnych figur
int MAX_ODLEGLOSCI[13] = {2, 8, 8, 8, 2, 2, 2, 8, 8, 8, 2, 2, 0};

//pomoc w wypisywaniu planszy
char ZNAKI[13] = {'K', //    0 - król
                  'H', //     1 - hetman
                  'W', //     2 - wieża
                  'G', //     3 - goniec
                  'S', //     4 - skoczek
                  'P', //     5 - pionek
                  'k', //     6 - król_k
                  'h', //     7 - hetman_k
                  'w', //     8 - wieża_k
                  'g', //     9 - goniec_k
                  's', //     10 - skoczek_k
                  'p', //     11 - pionek_k
                  ' '};//    12 - pole puste





int WY[12][8] = {
        {0,  1, 1,  1, 0,  -1, -1, -1},
        {0,  1, 1,  1, 0,  -1, -1, -1},
        {0,  1, 0,  -1},
        {1,  1, -1, -1},
        {1,  2, 2,  1, -1, -2, -2, -1},
        {-1, 0, 1},
        {0,  1, 1,  1, 0,  -1, -1, -1},
        {0,  1, 1,  1, 0,  -1, -1, -1},
        {0,  1, 0,  -1},
        {1,  1, -1, -1},
        {1,  2, 2,  1, -1, -2, -2, -1},
        {-1, 0, 1}
};

int WX[12][8] = {
        {-1, -1, 0, 1, 1, 1, 0,  -1},
        {-1, -1, 0, 1, 1, 1, 0,  -1},
        {-1, 0,  1, 0},
        {-1, 1,  1, -1},
        {-2, -1, 1, 2, 2, 1, -1, -2},
        {-1, -1, -1},
        {-1, -1, 0, 1, 1, 1, 0,  -1},
        {-1, -1, 0, 1, 1, 1, 0,  -1},
        {-1, 0,  1, 0},
        {-1, 1,  1, -1},
        {-2, -1, 1, 2, 2, 1, -1, -2},
        {1,  1,  1}
};

//podaje ocene na aktualnym ułożeniu
int ocena(int pl[8][8]) {
    int wynik = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            wynik += heurytyki[pl[i][j]][i][j];
        }
    }

    return wynik;
}

//wypisuje aktualne ułożenie planszy
void wypisz(int plansza[8][8]) {
    printf("\n");
    printf("   ");

    for (int i = 0; i < 8; ++i) {
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 0; i < 8; ++i) {
        printf("%d |", i);
        for (int j = 0; j < 8; ++j) {
            printf("%c|", ZNAKI[plansza[i][j]]);
        }
        printf("\n");
    }
}

int mozliwy_ruch(int plansza[8][8], int x_start, int y_start, int x_nowe, int y_nowe) {
    int dx, dy;
    //czy pola wybrane mieszcza sie w tablicy..:
    if (x_nowe >= 0 && x_nowe <= 7 && y_nowe >= 0 && y_nowe <= 7 && x_start >= 0 && x_start <= 7 && y_start >= 0 &&
        y_start <= 7) {
        //czy nasz pion:
        if (plansza[x_start][y_start] > 5 && plansza[x_start][y_start] < 12) {
            // przekopiowane z funkcji "najlepszy"
            // sprawdza możliwe kierunki
            for (int kierunek = 0; kierunek < MAX_KIERUNKI[plansza[x_start][y_start]]; kierunek++) {
                // sprawdza różne długości ruchu
                for (int odleglosc = 1; odleglosc < MAX_ODLEGLOSCI[plansza[x_start][y_start]]; odleglosc++) {
                    dx = (odleglosc - 1) * WX[plansza[x_start][y_start]][kierunek];
                    dy = (odleglosc - 1) * WY[plansza[x_start][y_start]][kierunek];
                    if (odleglosc >= 2 && plansza[x_start + dx][x_start + dy] != 12) break;
                    dx = odleglosc * WX[plansza[x_start][y_start]][kierunek];
                    dy = odleglosc * WY[plansza[x_start][y_start]][kierunek];
                    if (x_start + dx >= 0 && x_start + dx < 8 && y_start + dy >= 0 && y_start + dy < 8) {
                        if (plansza[x_start + dx][y_start + dy] == 12 || plansza[x_start + dx][y_start + dy] <= 5) {
                            //Sprawdzenie warunku pionka tj. bicie na skos i ruch w przód.
                            if (plansza[x_start][y_start] != 11 ||
                                (plansza[x_start + dx][y_start + dy] == 12 && dy == 0) ||
                                (plansza[x_start + dx][y_start + dy] != 12 && dy != 0)) {
                                if (((x_start + dx) == x_nowe) && ((y_start + dy) == y_nowe)) {
                                    return 1;
                                }
                            }
                        }
                    }

                }

            }
        }

    }
    return 0;
}


//drzewo ruchów
int najlepszy(int plansza[8][8], int gl, int *x, int *y, int *k, int *o) {
    int px_pom, py_pom, k_pom, o_pom, dx, dy;
    int wynik, wmin, bita_fig, figura, wmax;

// ocena
    wynik = ocena(plansza);
// ograniczenie rekurencji
    if (gl == 0 || wynik > WYGRANA || wynik < PRZEGRANA) return wynik;
//zaczyna komputer....
    if (gl % 2 == 0) {
        wmax = -1000000;
        //iteruję się przez wszystkie pola na planszy
        for (int px = 0; px < 8; px++) {
            for (int py = 0; py < 8; py++) {
                figura = plansza[px][py];
                //jeżeli na polu stoi pionek komputera
                if (plansza[px][py] >= 6 && plansza[px][py] < 12) {
                    //sprawdzam wszystkie kierunki wychodzące z tego pola,
                    for (int kierunek = 0; kierunek < MAX_KIERUNKI[plansza[px][py]]; kierunek++) {
                        //idąc w max odleglosc, dopoki pola puste, sprawdzajac kazde pole.
                        for (int odleglosc = 1; odleglosc < MAX_ODLEGLOSCI[plansza[px][py]]; odleglosc++) {
                            //sprawdzanie pol po drodze
                            dx = (odleglosc - 1) * WX[plansza[px][py]][kierunek];
                            dy = (odleglosc - 1) * WY[plansza[px][py]][kierunek];
                            if (odleglosc >= 2 && plansza[px + dx][py + dy] != 12) break;
                            dx = odleglosc * WX[plansza[px][py]][kierunek];
                            dy = odleglosc * WY[plansza[px][py]][kierunek];
                            //sprawdzenie warunku, czy nie wychodzimy poza plansze.
                            if (px + dx >= 0 && px + dx < 8 && py + dy >= 0 && py + dy < 8) {
                                bita_fig = plansza[px + dx][py + dy];
                                //12-puste. Jesli puste, lub stoi tam figura przeciwnika
                                if (plansza[px + dx][py + dy] == 12 || plansza[px + dx][py + dy] <= 5) {
                                    //Sprawdzenie warunku pionka tj. bicie na skos i ruch w przód, o ile jest puste.
                                    if (plansza[px][py] != 11 || (plansza[px + dx][py + dy] == 12 && dy == 0) ||
                                        (plansza[px + dx][py + dy] != 12 && dy != 0)) {
                                        //wykonanie ruchu
                                        plansza[px + dx][py + dy] = plansza[px][py];
                                        plansza[px][py] = 12;
                                        //sprawdzenie czy zmieniamy pionka na hetmana.
                                        if (figura == 11 && px + dx == 7) {
                                            plansza[px + dx][py + dy] = 7;
                                        }
                                        //rekurencja
                                        wynik = najlepszy(plansza, gl - 1, &px_pom, &py_pom, &k_pom, &o_pom);
                                        //powrót
                                        plansza[px][py] = figura;
                                        plansza[px + dx][py + dy] = bita_fig;
                                        if (wynik > wmax) {
                                            wmax = wynik;
                                            *x = px;
                                            *y = py;
                                            *k = kierunek;
                                            *o = odleglosc;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (wmax > -1000000) return wmax;
        else return 0;
    } else { //teraz czlowiek...
        wmin = 1000000;
        //iteruję się przez wszystkie pola na planszy
        for (int px = 0; px < 8; px++) {
            for (int py = 0; py < 8; py++) {
                figura = plansza[px][py];
                //czy na polu stoi pionek czlowieka
                if (plansza[px][py] <= 5) {
                    //sprawdzamy wszystkie kierunki dla danej figury
                    for (int kierunek = 0; kierunek < MAX_KIERUNKI[plansza[px][py]]; kierunek++) {
                        //idąc w max odleglosc, dopoki pola puste, sprawdzajac kazde pole.
                        for (int odleglosc = 1; odleglosc < MAX_ODLEGLOSCI[plansza[px][py]]; odleglosc++) {
                            //sprawdzanie pol po drodze
                            dx = (odleglosc - 1) * WX[plansza[px][py]][kierunek];
                            dy = (odleglosc - 1) * WY[plansza[px][py]][kierunek];
                            if (odleglosc >= 2 && plansza[px + dx][py + dy] != 12) break;
                            dx = odleglosc * WX[plansza[px][py]][kierunek];
                            dy = odleglosc * WY[plansza[px][py]][kierunek];
                            //sprawdzenie, czy nie wychodzimy poza plansze
                            if (px + dx >= 0 && px + dx < 8 && py + dy >= 0 && py + dy < 8) {
                                bita_fig = plansza[px + dx][py + dy];
                                //czy pole puste czy jest tam figura przeciwnika
                                if (plansza[px + dx][py + dy] >= 6) {
                                    //Sprawdzenie warunku pionka tj. bicie na skos i ruch w przód.
                                    if (plansza[px][py] != 5 || (plansza[px + dx][py + dy] == 12 && dy == 0) ||
                                        (plansza[px + dx][py + dy] != 12 && dy != 0)) {
                                        //ruch
                                        plansza[px + dx][py + dy] = plansza[px][py];
                                        plansza[px][py] = 12;
                                        //zamiana na hetmana
                                        if (figura == 5 && px + dx == 0) {
                                            plansza[px + dx][py + dy] = 1;
                                        }
                                        //rekurencja
                                        wynik = najlepszy(plansza, gl - 1, &px_pom, &py_pom, &k_pom, &o_pom);
                                        //powrot
                                        plansza[px][py] = figura;
                                        plansza[px + dx][py + dy] = bita_fig;
                                        if (wynik < wmin) {
                                            wmin = wynik;
                                            *x = px;
                                            *y = py;
                                            *k = kierunek;
                                            *o = odleglosc;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (wmin < 1000000) return wmin;
        else return 0;
    }
}


int main() {

    int figura1, dx1, dy1;
    //                    0-------------------------> y
    int plansza[8][8] = {{8,  10, 9,  7,  6,  9,  10, 8},  // |
                         {11, 11, 11, 11, 11, 11, 11, 11}, // |
                         {12, 12, 12, 12, 12, 12, 12, 12}, // |
                         {12, 12, 12, 12, 12, 12, 12, 12}, // |
                         {12, 12, 12, 12, 12, 12, 12, 12}, // |
                         {12, 12, 12, 12, 12, 12, 12, 12}, // |
                         {5,  5,  5,  5,  5,  5,  5,  5},  // V
                         {2,  4,  3,  1,  0,  3,  4,  2}}; // x


    int gl = 4, x, y, kierunek, odleglosc, t;
    int x_start, y_start, x_nowe, y_nowe;

    int status, gniazdo, dlugosc, nr = 0, end = 1, gniazdo2, rozmowa;
    struct sockaddr_in ser, cli;
    char buf[200];
    char mess[200];

    gniazdo = socket(AF_INET, SOCK_STREAM, 0);
    if (gniazdo == -1) {
        printf("blad socketn");
        return 0;
    }

    ser.sin_family = AF_INET;
    ser.sin_port = htons(9000);
    ser.sin_addr.s_addr = inet_addr("127.0.0.1");

    status = bind(gniazdo, (struct sockaddr *) &ser, sizeof(ser));
    if (status == -1) {
        printf("blad bind\n");
        return 0;
    }

    status = listen(gniazdo, 10);
    if (status == -1) {
        printf("blad listen\n");
        return 0;
    }

    while (end) {
        rozmowa = 1;
        dlugosc = sizeof(cli);
        gniazdo2 = accept(gniazdo, (struct sockaddr *) &cli, (socklen_t *) &dlugosc);
        if (gniazdo2 == -1) {
            printf("blad accept");
            return 0;
        }
        while (rozmowa) {
            status = recv(gniazdo2, buf, sizeof(buf) - 1, 0);
            buf[status] = '\0';
            printf("Otrzymałem: %s\n", buf);
            if (buf[0] == 'Q') {
                sprintf(mess, "Zgoda, serwer konczy prace\n");
                end = 0;
                rozmowa = 0;
            } else if (buf[0] == 'N') sprintf(mess, "Jestes klientem nr %d\n", nr++);
            else if (buf[0] == 'P') {
                sprintf(mess, "Kończę rozmowę\n");
                rozmowa = 0;
            } else {

                printf("Otrzymałem ruch: %s\n", buf);
                x_start = buf[0] - 48;
                y_start = buf[1] - 48;
                x_nowe = buf[2] - 48;
                y_nowe = buf[3] - 48;
                t = plansza[x_start][y_start];
                plansza[x_nowe][y_nowe] = t;
                plansza[x_start][y_start] = 12;
                //sprawdzenie, czy nalezy zmienic piona na hetmana.
                if (plansza[x_nowe][y_nowe] == 5 && x_nowe == 0) {
                    plansza[x_nowe][y_nowe] = 1;
                }
                printf("Oto ruch przeciwnika:\n");

                //   if (ocena(plansza) >= WYGRANA) {
                //     printf("przeciwnik wygral");
                //    break;
                //}



                najlepszy(plansza, 4, &x, &y, &kierunek, &odleglosc);
                //komputer wykonuje swój ruch ustalony przez najlpeszy
                figura1 = plansza[x][y];
                dx1 = odleglosc * WX[figura1][kierunek];
                dy1 = odleglosc * WY[figura1][kierunek];
                plansza[x + dx1][y + dy1] = figura1;
                plansza[x][y] = PUSTE;
                //sprawdzenie warunku na zmiane piona na hetmana
                if (figura1 == 11 && y + dy1 == 7) {
                    plansza[x + dx1][y + dy1] = 7;
                }



                mess[0] = 48 + x;
                mess[1] = 48 + y;
                mess[2] = 48 + x + dx1;
                mess[3] = 48 + y + dy1;

                if (mess[0] == 'P') {
                    rozmowa = 0;
                }
                wypisz(plansza);

            }
            status = send(gniazdo2, mess, strlen(mess), 0);
        }
        close(gniazdo2);
    }

    close(gniazdo);
}