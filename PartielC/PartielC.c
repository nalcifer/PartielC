// PartielC : Faire un puissance 4

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW (4)

char** initTab(char filling);
void drawTab(char** tab);
//char* askString(char* message);
int askOneNumber(char* message, int min, int max);
char askSign(char* message);
int getRandomNumber(int max);
int checkPlayability(char** tab, int column);
int checkFreeLine(char** tab, int column);
int checkWin(char** tab, char player_sign);
int checkEquality(char** tab);

void lap(char** tab, char* player, char player_sign);

int main()
{
    int condition = 1;
    int win = 0;
    int equality = 0;
    char** tab = NULL;
    char* p1_name = "Joueur 1";
    char* p2_name = "Joueur 2";
    char p1_sign, p2_sign;
    int p_turn;
    char p_sign;
    do {
        system("CLS");
        tab = initTab('N');
        //p1_name = askString("Entrez le nom du joueur 1 : ");
        //p2_name = askString("Entrez le nom du joueur 2 : ");
        p1_sign = askSign("Joueur 1 - Choisissez un signe 0=[O] 1=[X] : ");
        if (p1_sign == 'O') {
            p2_sign = 'X';
        }
        else {
            p2_sign = 'O';
        }
        drawTab(tab);

        // Manche
        p_turn = getRandomNumber(2);
        while (win == 0 && equality == 0) {
            if (p_turn == 0) {
                p_sign = p1_sign;
                lap(tab, p1_name, p_sign);
                p_turn++;
            }
            else if (p_turn == 1) {
                p_sign = p2_sign;
                lap(tab, p2_name, p_sign);
                p_turn--;
            }
            system("CLS");
            drawTab(tab);
            win = checkWin(tab, p_sign);
            equality = checkEquality(tab);
        }
        

        drawTab(tab);
        // fin de manche
        if (win == 1) {
            if (p_sign == p1_sign) {
                printf("BRAVO ! %s a gagne !", p1_name);
            }
            else if (p_sign == p2_sign) {
                printf("BRAVO ! %s a gagne !", p2_name);
            }
            win = 0;
        }
        else if (equality == 1) {
            printf("Il y a egalite\n");
            equality = 0;
        }
        condition = askOneNumber("Voulez-vous recommencer ? 0=[NON] 1=[OUI] : ", 0, 1);
        free(tab);
    } while (condition);
    
    
}


char** initTab(char filling) {
    int i, j;
    char** table = (char**)malloc(sizeof(char*) * ROW);
    if (table == NULL)
        return 1;
    for (i = 0; i < ROW; ++i)
    {
        table[i] = (char*)malloc(sizeof(char) * ROW);
        if (table[i] == NULL)
            return 1;
        for (j = 0; j < ROW; ++j)
        {
            table[i][j] = filling;
        }
    }
    return table;
}


void drawTab(char** tab) {
    int i, j;
    for (i = 0; i < ROW; i++) {
        printf(" %d ", i + 1);
    }
    for (i = 0; i < ROW; i++) {
        putchar('\n');
        for (j = 0; j < ROW; j++) {
            if (tab[i][j] == 'N') {
                printf("[ ]");
            }
            else {
                printf("[%c]", tab[i][j]);
            }
        }
    }
    putchar('\n');
}


//char* askString(char* message) {
//    char* string;
//    printf("%s", message);
//    scanf_s("%s", &string);
//    while (getchar() != '\n');
//    return string;
//}


int askOneNumber(char* message, int min, int max) {
    int result;
    printf("%s", message);
    scanf_s("%d", &result);
    while (getchar() != '\n');
    while (result < min || result > max) {
        printf("\nReponse non valide.\n%s", message);
        scanf_s("%d", &result);
        while (getchar() != '\n');
    }
    return result;
}


char askSign(char* message) {
    int s;
    char sign;
    s = askOneNumber(message, 0, 1);
    if (s == 0) {
        sign = 'O';
    }
    else {
        sign = 'X';
    }
    return sign;
}


int getRandomNumber(int modul) {
    int n;
    srand(time(NULL));
    n = rand() % modul;
    return n;
}


int checkPlayability(char** tab, int column) {
    if (tab[0][column] == 'N') {
        return 1;
    }
    else {
        return 0;
    }
}

int checkFreeLine(char** tab, int column) {
    int line = 3;
    while (tab[line][column] != 'N') {
        line--;
    }
    return line;
}


void lap(char** tab, char* player, char player_sign) {
    int column, line, playability;
    printf("%s\n", player);
    column = askOneNumber("Choisissez une colonne : ", 1, 4);
    column--;
    playability = checkPlayability(tab, column);
    while (playability != 1) {
        column = askOneNumber("Choisissez une autre colonne : ", 1, 4);
        column--;
        playability = checkPlayability(tab, column);
    }
    line = checkFreeLine(tab, column);
    tab[line][column] = player_sign;
}


int checkWin(char** tab, char player_sign) {
    int i, j;
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < ROW; j++) {
            if (i == 0) {
                if (tab[i][j] == player_sign && tab[i + 1][j] == player_sign && tab[i + 2][j] == player_sign && tab[i + 3][j] == player_sign) {
                    return 1;
                }
            }
            if (j == 0) {
                if (tab[i][j] == player_sign && tab[i][j + 1] == player_sign && tab[i][j + 2] == player_sign && tab[i][j + 3] == player_sign) {
                    return 1;
                }
            }
            if (i == 0 && j == 0) {
                if (tab[i][j] == player_sign && tab[i + 1][j + 1] == player_sign && tab[i + 2][j + 2] == player_sign && tab[i + 3][j + 3] == player_sign) {
                    return 1;
                }
            }
            if (i == 0 && j == 3) {
                if (tab[i][j] == player_sign && tab[i + 1][j - 1] == player_sign && tab[i + 2][j - 2] == player_sign && tab[i + 3][j - 3] == player_sign) {
                    return 1;
                }
            }
        }
    }
    return 0;
}


int checkEquality(char** tab) {
    int i, j;
    int box = 0;
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < ROW; j++) {
            if (tab[i][j] != 'N') {
                box++;
            }
        }
    }
    if (box == 16) {
        return 1;
    }
    else {
        return 0;
    }
}