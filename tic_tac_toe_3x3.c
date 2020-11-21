
//
// Created by Bartosz Kruczek on 10/11/2020.
//
#include<stdio.h>

#define WIN 10000
#define LOSE -10000

void print_board(char pl[3][3]) {
    printf("\n");

    for (int i = 0; i < 3; ++i) {
        printf("|");
        for (int j = 0; j < 3; ++j) {
            printf("%c|", pl[i][j]);

        }


        printf("\n");
    }

}


int ocena(char pl[3][3]) {
    int licz1x = 0, licz1o = 0;
    int licz2x = 0, licz2o = 0;


    if (pl[0][0] == 'x' && pl[1][1] == 'x' && pl[2][2] == 'x') {
        return WIN;
    }
    if (pl[0][2] == 'x' && pl[1][1] == 'x' && pl[2][0] == 'x') {
        return WIN;
    }
    if (pl[0][0] == 'o' && pl[1][1] == 'o' && pl[2][2] == 'o') {
        return LOSE;
    }
    if (pl[0][2] == 'o' && pl[1][1] == 'o' && pl[2][0] == 'o') {
        return LOSE;
    }

    for (int i = 0; i < 3; ++i) {
        licz1x = 0;
        licz2x = 0;
        licz1o = 0;
        licz2o = 0;
        for (int j = 0; j < 3; ++j) {

            if (pl[i][j] == 'x') {
                licz1x++;
            }
            if (pl[j][i] == 'x') {
                licz2x++;
            }
            if (pl[i][j] == 'o') {
                licz1o++;
            }
            if (pl[j][i] == 'o') {
                licz2o++;
            }
        }
        if (licz1x == 3 || licz2x == 3) {
            return WIN;
        }
        if (licz1o == 3 || licz2o == 3) {
            return LOSE;
        }
    }

    return 0;
}


int minimax(int gl, char pl[3][3], int maximizingPlayer, int *io, int *jo) {
    int ocen = ocena(pl);
    int brak_ruchu = 1;
    int eval, maxEval, minEval;
    if (gl == 0 || ocen == WIN || ocen == LOSE) {
        return ocen;
    }
    if (maximizingPlayer == 1) {
        maxEval = 2 * LOSE;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
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
        minEval = 2 * WIN;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
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
    char pl[3][3] = {"   ", "   ", "   "};
    int i = 0, j = 0, x, y, puste_pola = 9;
    while (1) {
        minimax(22, pl, 1, &i, &j);
        pl[i][j] = 'x';
        puste_pola--;
        printf("oto ruch komputera: \n");
        print_board(pl);
        if (puste_pola == 0) {
            printf("plansza zapełiona. Koniec gry. Zakończono remisem.");
            break;
        }
        if (ocena(pl) == WIN) {
            printf("Komputer wygrał\n");
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
        if (ocena(pl) == LOSE) {
            printf("Brawo, wygrałeś!!\n");
            break;
        }
        if (puste_pola == 0) {
            printf("plansza zapełiona. Koniec gry. Zakończono remisem.");
            break;
        }
    }
}

