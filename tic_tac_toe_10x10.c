//
// Created by Bartosz Kruczek on 22/11/2020.
//


#include<stdio.h>

#define WYGRANA 10000
#define PRZEGRANA -10000

int DODAJ_X[6] = {0, 0, 1, 5, 20, WYGRANA};
int DODAJ_O[6] = {0, 0, -1, -5, -20, PRZEGRANA};

int DODAJ_XP[6] = {0, 0, 1, 4, 15, WYGRANA};
int DODAJ_OP[6] = {0, 0, -1, -4, -15, PRZEGRANA};

void wypisz(char pl[10][10]) {
    printf("\n");

    for (int i = 0; i < 10; ++i) {
        printf("|");
        for (int j = 0; j < 10; ++j) {
            printf("%c|", pl[i][j]);
        }
        printf("\n");
    }
}

int ocena(char pl[10][10]) {
    int ocena = 0;
    int liczwx = 0, liczwo = 0;
    int liczkx = 0, liczko = 0;

    //przeszukiwanie wierszy i kolumnm dla x-ów.
    //ponizsze polecenia rownowazne sa wyszukiwaniu łącznych podciągów x-ów
    //o długości ≥ 2 i dla każdego tego podciągu należy dodać wartość odpowiadającą długości podciągu.

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            //najpierw wiersze
            if (pl[i][j] == 'x') {
                liczwx++;
            } else {
                if (liczwx == 5)
                    return WYGRANA;
                else
                    ocena += DODAJ_X[liczwx];
                liczwx = 0;
            }
            if (pl[i][j] == 'o') {
                liczwo++;
            } else {
                if (liczwo == 5)
                    return PRZEGRANA;
                else
                    ocena += DODAJ_O[liczwo];
                liczwo = 0;
            }
    //Teraz pzechodzimy do kolumn
    //ciagx, liczwx, ciagy, liczwy
            if (pl[j][i] == 'x') {
                liczkx++;
            } else {
                if (liczkx == 5)
                    return WYGRANA;
                else
                    ocena += DODAJ_X[liczkx];
                liczkx = 0;
            }
            if (pl[j][i] == 'o') {
                liczko++;
            } else {
                if (liczko == 5)
                    return PRZEGRANA;
                else
                    ocena += DODAJ_O[liczko];
                liczko = 0;
            }
        }
        if (liczwx == 5 || liczkx == 5) {
            return WYGRANA;
        } else {
            ocena += DODAJ_X[liczwx] + DODAJ_X[liczkx];

        }
        if (liczko == 5 || liczwo == 5) {
            return PRZEGRANA;
        } else {
            ocena += DODAJ_O[liczwo] + DODAJ_O[liczko];
        }
        liczwx = 0, liczwo = 0;
        liczkx = 0, liczko = 0;

    }
    //ponizej liczę przekatne z góry do dołu w prawo
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (pl[i][j] != ' ' && pl[i][j] == pl[i + 1][j + 1]) {
                if (pl[i][j] == pl[i + 2][j + 2]) {
                    if (pl[i][j] == pl[i + 3][j + 3]) {
                        if (pl[i][j] == pl[i + 4][j + 4]) {
                            if (pl[i][j] == 'x') return WYGRANA;
                            else return PRZEGRANA;
                        }
                        if (pl[i][j] == 'x') ocena += DODAJ_XP[4];
                        else ocena += DODAJ_OP[4];
                    }
                    if (pl[i][j] == 'x') ocena += DODAJ_XP[3];
                    else ocena += DODAJ_OP[3];
                }
                if (pl[i][j] == 'x') ocena += DODAJ_XP[2];
                else ocena += DODAJ_OP[2];
            }
        }
    }
    //przekatne, ale z dolnego wiersza w prawo
    for (int i = 9; i > 3; i--) {
        for (int j = 0; j < 6; j++) {
            if (pl[i][j] != ' ' && pl[i][j] == pl[i - 1][j + 1]) {
                if (pl[i][j] == pl[i - 2][j + 2]) {
                    if (pl[i][j] == pl[i - 3][j + 3]) {
                        if (pl[i][j] == pl[i - 4][j + 4]) {
                            if (pl[i][j] == 'x') return WYGRANA;
                            else return PRZEGRANA;
                        }
                        if (pl[i][j] == 'x') ocena += DODAJ_XP[4];
                        else ocena += DODAJ_OP[4];
                    }
                    if (pl[i][j] == 'x') ocena += DODAJ_XP[3];
                    else ocena += DODAJ_OP[3];
                }
                if (pl[i][j] == 'x') ocena += DODAJ_XP[2];
                else ocena += DODAJ_OP[2];
            }

        }
    }

    //  printf("ocena dla:\n");
    //wypisz(pl);
    //printf("\nto: %d", ocena);
    return ocena;
}

int minimax(int gl, char pl[10][10], int maximizingPlayer, int *io, int *jo) {
    int ocen = ocena(pl);
    int brak_ruchu = 1;
    int eval, maxEval, minEval;
    if (gl == 0 || ocen == WYGRANA || ocen == PRZEGRANA) {
        return ocen;
    }
    if (maximizingPlayer == 1) {
        maxEval = 2 * PRZEGRANA;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (pl[i][j] == ' ') {
                    pl[i][j] = 'x';
                    eval = minimax(gl - 1, pl, 0, io, jo);
                    pl[i][j] = ' ';
                    if (eval >= maxEval) {
                        maxEval = eval;
                        *io = i;
                        *jo = j;
                    }
                    brak_ruchu = 0;

                }

            }
        }
        if (brak_ruchu) return 0; else return maxEval;
    } else {
        minEval = 2 * WYGRANA;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (pl[i][j] == ' ') {
                    pl[i][j] = 'o';
                    eval = minimax(gl - 1, pl, 1, io, jo);
                    pl[i][j] = ' ';
                    if (eval <= minEval) {
                        minEval = eval;
                        *io = i;
                        *jo = j;
                    }
                    brak_ruchu = 0;
                }
            }
        }
        if (brak_ruchu) return 0; else return minEval;
    }
}

int main(void) {
    char pl[10][10] = {"          ", "          ", "          ", "          ", "          ", "          ", "          ",
                       "          ", "          ", "          "};
    int i = 0, j = 0, x, y, puste_pola = 100;
    while (1) {
        minimax(2, pl, 1, &i, &j);
        pl[i][j] = 'x';
        puste_pola--;
        printf("oto ruch komputera: \n");
        wypisz(pl);
        if (ocena(pl) == WYGRANA) {
            printf("Komputer wygrał\n");
            break;
        }
        if (puste_pola == 0) {
            printf("plansza zapełiona. Koniec gry. Zakończono remisem.");
            break;
        }

        printf("podaj ruch: ");
        scanf("%d%d", &x, &y);
        while (1) {
            if (pl[x][y] == ' ') {
                pl[x][y] = 'o';
                break;
            } else {
                printf("Pole jest juz zajete. Wybierz inne:\n");
                printf("podaj ruch: ");
                scanf("%d%d", &x, &y);
            }
        }
        puste_pola--;
        if (ocena(pl) == PRZEGRANA) {
            printf("Brawo, wygrałeś!!\n");
            break;
        }
        if (puste_pola == 0) {
            printf("plansza zapełiona. Koniec gry. Zakończono remisem.");
            break;
        }
    }
}
