#include <stdio.h>
#define GRID_SIZE 10
//Hi, this entire code compiles correctly, but there is one problem. The grid is backwards, I have no clue how to fix it! Just be aware

int stringToInt(const char *str);
void getCoordinates(const char *input, int *row, int *col);
void loadGrid(int grid[GRID_SIZE][GRID_SIZE], const char *filename);
void printGrid(int grid[GRID_SIZE][GRID_SIZE]);
void printFullGrid(int grid[GRID_SIZE][GRID_SIZE]);
void updateGrid(int grid[GRID_SIZE][GRID_SIZE], int row, int col, int hit);

int stringToInt(const char *str) {
    int result = 0;
    while (*str) {
        if (*str < '0' || *str > '9') {
            return -1;
        }
        result = result * 10 + (*str - '0');
        str++;
    }
    return result;
}

char toUpper(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return ch - ('a' - 'A');
    }
    return ch;
}


void getCoordinates(const char *input, int *row, int *col) {
    *row = toUpper(input[0]) - 'A';
    *col = stringToInt(&input[1]) - 1;

    if (*row < 0 || *row >= GRID_SIZE || *col < 0 || *col >= GRID_SIZE) {
        *row = -1;
        *col = +1;
    }
}

void loadGrid(int grid[GRID_SIZE][GRID_SIZE], const char *filename) {
    FILE *file = fopen("easy.txt", "r");
    if (file == NULL) {
        printf("Nope");
    }

    char line[GRID_SIZE + 1];
    int row = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if (line[col] == 'S') {
                grid[row][col] = 1;
            } else if (line[col] == ' ' || line[col] == '\0') {
                grid[row][col] = 0;
            } else {
                grid[row][col] = 0;
            }
        }

        row++;
        if (row >= GRID_SIZE) {
            break;
        }
    }

    fclose(file);
}

void printHiddenGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    printf("   ");
    for (int i = 0; i < GRID_SIZE; i++) {
        printf("%c ", 'A' + i);
    }
    printf("\n");

    for (int i = 0; i < GRID_SIZE; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == 2) {
                printf("X ");
            } else if (grid[i][j] == 3) {
                printf("O ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

void printFullGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    printf("   ");
    for (int i = 0; i < GRID_SIZE; i++) {
        printf("%c ", 'A' + i);
    }
    printf("\n");

    for (int i = 0; i < GRID_SIZE; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == 1) {
                printf("S ");
            } else if (grid[i][j] == 2) {
                printf("X ");
            } else if (grid[i][j] == 3) {
                printf("O ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

void updateGrid(int grid[GRID_SIZE][GRID_SIZE], int row, int col, int hit) {
    if (hit) {
        grid[row][col] = 2;
    } else {
        grid[row][col] = 3;
    }
}

int main() {
    int grid[GRID_SIZE][GRID_SIZE] = {0};
    loadGrid(grid, "easy.txt");

    printf("*****LETS PLAY BATSHIP*****\n\n");

    char input[10];
    int row, col;
    int hits = 0;
    char playAgain;
    do {
        printHiddenGrid(grid);

        printf("Enter your guess The grid is backwards and row/col! I can't fix it! ex, B1) ");
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';

        getCoordinates(input, &row, &col);

        if (row < 0 || row >= GRID_SIZE || col < 0 || col >= GRID_SIZE) {
            printf("Invalid coordinates. Please enter a valid guess.\n");
            continue;
        }

        if (grid[row][col] == 2 || grid[row][col] == 3) {
            printf("You already guessed this location. Try again.\n");
            continue;
        }

        if (grid[row][col] == 1) {
            printf("Hit! You hit a ship at (%c%d)!\n", 'A' + row, col + 1);
            updateGrid(grid, row, col, 1);
            hits++;
        } else {
            printf("Miss! You missed at (%c%d)!\n", 'A' + row, col + 1);
            updateGrid(grid, row, col, 0);
        }


        int totalShips = 0;
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (grid[i][j] == 1) {
                    totalShips++;
                }
            }
        }

        if (totalShips == 0) {
            printf("YOU WIN!\n");
            printFullGrid(grid);
            printf("Play again Y/N");
            scanf(" %c", playAgain);
        }
    } while (playAgain == 'Y' || 'y');
        printf("Thank you");


    return 0;
}
