#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

int** allocateMatrix(int rows, int cols) {
    int **matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    return matrix;
}

void freeMatrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void fillRandomMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

void printMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int hasSameNumbersInRowOrCol(int **matrix, int rows, int cols, int *foundRow, int *foundCol, int *isRow) {
    for (int i = 0; i < rows; i++) {
        int same = 1;
        for (int j = 1; j < cols; j++) {
            if (matrix[i][j] != matrix[i][0]) {
                same = 0;
                break;
            }
        }
        if (same) {
            *foundRow = i;
            *foundCol = 0;
            *isRow = 1;
            return 1;
        }
    }
    
    for (int j = 0; j < cols; j++) {
        int same = 1;
        for (int i = 1; i < rows; i++) {
            if (matrix[i][j] != matrix[0][j]) {
                same = 0;
                break;
            }
        }
        if (same) {
            *foundRow = 0;
            *foundCol = j;
            *isRow = 0;
            return 1;
        }
    }
    
    return 0;
}

int main() {
    SetConsoleOutputCP(866);
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    
    int rows, cols;
    printf("Vvedite kolichestvo strok: ");
    scanf("%d", &rows);
    printf("Vvedite kolichestvo stolbtsov: ");
    scanf("%d", &cols);
    
    int **matrix = allocateMatrix(rows, cols);
    int counter = 0;
    int foundRow, foundCol, isRow;
    int found = 0;
    
    printf("\nGeneratsiya matrits...\n\n");
    
    do {
        fillRandomMatrix(matrix, rows, cols);
        counter++;
        
        printf("--- Popytka #%d ---\n", counter);
        printMatrix(matrix, rows, cols);
        
        found = hasSameNumbersInRowOrCol(matrix, rows, cols, &foundRow, &foundCol, &isRow);
        
        if (found) {
            if (isRow) {
                printf(">>> Naydena stroka #%d s odinakovymi chislami: %d <<<\n", 
                       foundRow + 1, matrix[foundRow][0]);
            } else {
                printf(">>> Nayden stolbets #%d s odinakovymi chislami: %d <<<\n", 
                       foundCol + 1, matrix[0][foundCol]);
            }
        } else {
            printf("Odinakovyykh strok/stolbtsov ne naydeno, prodolzhayem...\n");
        }
        printf("\n");
        
    } while (!found);
    
    printf("========================================\n");
    printf("Matritsa naydena posle %d popytok!\n\n", counter);
    
    printf("=== ITOGOVAYA MATRITSA ===\n");
    printMatrix(matrix, rows, cols);
    
    if (isRow) {
        printf("\nStroka #%d soderzhit odinakovyye chisla: ", foundRow + 1);
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[foundRow][j]);
        }
        printf("\n");
    } else {
        printf("\nStolbets #%d soderzhit odinakovyye chisla: ", foundCol + 1);
        for (int i = 0; i < rows; i++) {
            printf("%d ", matrix[i][foundCol]);
        }
        printf("\n");
    }
    
    freeMatrix(matrix, rows);
    
    system("pause");
    return 0;
}
