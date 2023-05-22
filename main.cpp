#include <stdio.h>

using namespace std;

#define firstPlayer 1
#define secondPlayer 2

struct dataP {
    short width;
    short height;
    short row;
    short player;
    short opponent;
    short** tab;
};
struct list {
    dataP game;
    list* next;
};

void addElement(const dataP& newGame, list*& head) {
    list* temp = head;
    list* nowy = new list;
    nowy->game = newGame;
    nowy->next = nullptr;
    if (head == nullptr) {
        head = nowy;
    }
    else {
        while (head->next != nullptr) {
            head = head->next;
        }
        head->next = nowy;
        head = temp;
    }
}
void removeList(list*& head) {
    list* temp;
    while (head->next != nullptr) {
        temp = head->next;
        for (int i = 0; i < head->game.height; i++) {
            delete[] head->game.tab[i];
        }
        delete[] head->game.tab;
        delete head;
        head = temp;
    }
    delete head;
}
bool areEqual(char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return false;
        }
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0') {
        return true;
    }
    else {
        return false;
    }
}
int countChars(dataP programData, int search) {
    int find = 0;
    for (int i = 0; i < programData.height; i++) {
        for (int j = 0; j < programData.width; j++) {
            if (programData.tab[i][j] == search) {
                find++;
            }
        }
    }
    return find;
}
bool win(dataP programData, int activePlayer) {
    int inRow = 0;
    for (int i = 0; i < programData.height; i++) {
        for (int j = 0; j < programData.width; j++) {
            if (programData.tab[i][j] == activePlayer) inRow++;
            else inRow = 0;

            if (inRow >= programData.row) {
                return true;
            }
        }
        inRow = 0;
    }
    for (int i = 0; i < programData.width; i++) {
        for (int j = 0; j < programData.height; j++) {
            if (programData.tab[j][i] == activePlayer) inRow++;
            else inRow = 0;

            if (inRow >= programData.row) {
                return true;
            }
        }
        inRow = 0;
    }
    for (int i = 0; i < programData.width; i++) {
        for (int j = programData.height - 1; j >= 0; j--) {
            for (int k = 0; i + k < programData.width && j + k < programData.height; k++) {
                if (programData.tab[j + k][i + k] == activePlayer) inRow++;
                else inRow = 0;

                if (inRow >= programData.row) {
                    return true;
                }
            }
            inRow = 0;
        }
    }
    for (int i = programData.width - 1; i >= 0; i--) {
        for (int j = programData.height - 1; j >= 0; j--) {
            for (int k = 0; i - k >= 0 && j + k < programData.height; k++) {
                if (programData.tab[j + k][i - k] == activePlayer) inRow++;
                else inRow = 0;

                if (inRow >= programData.row) {
                    return true;
                }
            }
            inRow = 0;
        }
    }
    return false;
}
int countAllMoves(dataP programData) {
    if (win(programData, programData.player) == true || win(programData, programData.opponent) == true) {
        return 0;
    }
    int moves = countChars(programData, 0);
    return moves;
}
int countAllWinMoves(dataP programData, short activePlayer) {
    if (win(programData, programData.player) == true || win(programData, programData.opponent) == true) {
        return 0;
    }
    for (int i = 0; i < programData.height; i++) {
        for (int j = 0; j < programData.width; j++) {
            if (programData.tab[i][j] == 0) {
                programData.tab[i][j] = activePlayer;
                if (win(programData, activePlayer) == true) {
                    programData.tab[i][j] = 0;
                    return 1;
                }
                programData.tab[i][j] = 0;
            }
        }
    }
    return 0;
}
int countAllWinMoves2(dataP programData, short activePlayer) {
    if (win(programData, programData.player) == true || win(programData, programData.opponent) == true) {
        return 0;
    }
    int moves = 0;
    for (int i = 0; i < programData.height; i++) {
        for (int j = 0; j < programData.width; j++) {
            if (programData.tab[i][j] == 0) {
                programData.tab[i][j] = activePlayer;
                if (win(programData, activePlayer) == true) {
                    moves++;
                    programData.tab[i][j] = 0;
                    if (moves == 2) return moves;
                }
                programData.tab[i][j] = 0;
            }
        }
    }
    return moves;
}
void allMoves(dataP programData) {
    int moves = countAllMoves(programData);
    printf("%i\n", moves);
    for (int k = 0; k < moves; k++) {
        int iter = 0;
        for (int i = 0; i < programData.height; i++) {
            for (int j = 0; j < programData.width; j++) {
                if (programData.tab[i][j] == 0) {
                    if (iter == k) {
                        printf("%i ", programData.player);
                    }
                    else {
                        printf("%i ", programData.tab[i][j]);
                    }
                    iter++;
                }
                else {
                    printf("%i ", programData.tab[i][j]);
                }
            }
            printf("\n");
        }
    }
}
void allMovesCutWin(dataP programData) {
    int moves = countAllWinMoves(programData, programData.player);
    if (moves == 0) {
        allMoves(programData);
    }
    else {
        bool finish = false;
        printf("%i\n", moves);
        for (int i = 0; i < programData.height; i++) {
            for (int j = 0; j < programData.width; j++) {
                if (programData.tab[i][j] == 0) {
                    programData.tab[i][j] = programData.player;
                    if (finish == false && win(programData, programData.player) == true) {
                        printf("%i ", programData.player);
                        programData.tab[i][j] = 0;
                        finish = true;
                    }
                    else {
                        programData.tab[i][j] = 0;
                        printf("%i ", programData.tab[i][j]);
                    }
                }
                else {
                    printf("%i ", programData.tab[i][j]);
                }
            }
            printf("\n");
        }
    }
}
void printWin(int activePlayer) {
    if (activePlayer == 1) {
        printf("FIRST_PLAYER_WINS\n");
    }
    else {
        printf("SECOND_PLAYER_WINS\n");
    }
}
bool winExtraCondition(dataP programData, short activePlayer) {
    if (programData.row == 1) {
        printWin(activePlayer);
        return true;
    }
    else if (programData.row == 2 && programData.height >= 2 && programData.width >= 2) {
        if (countChars(programData, activePlayer) >= 1) {
            printWin(activePlayer);
            return true;
        }
        else if (countChars(programData, activePlayer) == countChars(programData, (activePlayer % 2) + 1)) {
            printWin(activePlayer);
            return true;
        }
        else if (countChars(programData, activePlayer) < countChars(programData, (activePlayer % 2) + 1)) {
            printWin((activePlayer % 2) + 1);
            return true;
        }
    }
    else if (countAllWinMoves(programData, activePlayer)) {
        printWin(activePlayer);
        return true;
    }
    return false;
}
int minValue(int a, int b) {
    if (a > b) {
        return b;
    }
    else {
        return a;
    }
}
int maxValue(int a, int b) {
    if (a < b) {
        return b;
    }
    else {
        return a;
    }
}
int minmax(dataP programData, short activePlayer) {

    if (countAllMoves(programData) == 0 && win(programData, programData.player) == false && win(programData, programData.opponent) == false) {
        return 0;
    }
    else if (win(programData, firstPlayer) == true) {
        return 1;
    }
    else if (win(programData, secondPlayer) == true) {
        return -1;
    }
    else if (countAllWinMoves(programData, activePlayer) == 1) {
        if (activePlayer == firstPlayer) return 1;
        else return -1;
    }
    else if (countAllWinMoves2(programData, (activePlayer % 2) + 1) == 2) {
        if (activePlayer == firstPlayer) return -1;
        else return 1;
    }
    list* gameStates = nullptr;
    for (int i = 0; i < programData.height; i++) {
        for (int j = 0; j < programData.width; j++) {
            if (programData.tab[i][j] == 0) {
                programData.tab[i][j] = activePlayer;
                dataP temp;
                temp.tab = new short* [programData.height];
                for (int h = 0; h < programData.height; h++) {
                    temp.tab[h] = new short[programData.width];
                }
                for (int k = 0; k < programData.height; k++) {
                    for (int l = 0; l < programData.width; l++) {
                        temp.tab[k][l] = programData.tab[k][l];
                    }
                }
                temp.height = programData.height;
                temp.width = programData.width;
                temp.opponent = programData.opponent;
                temp.player = programData.player;
                temp.row = programData.row;
                addElement(temp, gameStates);
                programData.tab[i][j] = 0;
            }
        }
    }
    if (activePlayer == firstPlayer) {
        int best = -100;
        list* temp = gameStates;
        while (gameStates != nullptr) {
            best = maxValue(best, minmax(gameStates->game, (activePlayer % 2) + 1));
            if (best == 1) {
                gameStates = temp;
                removeList(gameStates);
                return 1;
            }
            gameStates = gameStates->next;
        }
        gameStates = temp;
        removeList(gameStates);
        return best;
    }
    else {
        int best = 100;
        list* temp = gameStates;
        while (gameStates != nullptr) {
            best = minValue(best, minmax(gameStates->game, (activePlayer % 2) + 1));
            if (best == -1) {
                gameStates = temp;
                removeList(gameStates);
                return -1;
            }
            gameStates = gameStates->next;
        }
        gameStates = temp;
        removeList(gameStates);
        return best;
    }
}
void solveGame(dataP programData) {
    if (countAllMoves(programData) == 0 && win(programData, programData.player) == false && win(programData, programData.opponent) == false) {
        printf("BOTH_PLAYERS_TIE\n");
    }
    else if (win(programData, firstPlayer) == true) {
        printf("FIRST_PLAYER_WINS\n");
    }
    else if (win(programData, secondPlayer) == true) {
        printf("SECOND_PLAYER_WINS\n");
    }
    else {
        if (winExtraCondition(programData, programData.player) == false) {
            int result = minmax(programData, programData.player);
            if (result == 0) {
                printf("BOTH_PLAYERS_TIE\n");
            }
            else if (result > 0) {
                printWin(firstPlayer);
            }
            else {
                printWin(secondPlayer);
            }
        }
    }
}

int main() {
    char option[50];
    dataP programData;
    while (true) {
        scanf("%s", option);
        if (feof(stdin) != 0) break;
        short a, b, c, d;

        scanf("%hd", &a);
        scanf("%hd", &b);
        scanf("%hd", &c);
        scanf("%hd", &d);
        programData.player = d;
        programData.width = b;
        programData.height = a;
        programData.row = c;
        if (programData.player == firstPlayer) programData.opponent = secondPlayer;
        else programData.opponent = firstPlayer;
        programData.tab = new short* [programData.height];
        for (int i = 0; i < programData.height; i++) {
            programData.tab[i] = new short[programData.width];
        }
        for (int i = 0; i < programData.height; i++) {
            for (int j = 0; j < programData.width; j++) {
                scanf("%hd", &a);
                programData.tab[i][j] = a;
            }
        }
        if (areEqual(option, "GEN_ALL_POS_MOV") == true) {
            allMoves(programData);
        }
        else if (areEqual(option, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == true) {
            allMovesCutWin(programData);
        }
        else if (areEqual(option, "SOLVE_GAME_STATE") == true) {
            solveGame(programData);
        }
        for (int i = 0; i < programData.height; i++) {
            delete[] programData.tab[i];
        }
        delete[] programData.tab;
    }
}
