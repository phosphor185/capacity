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
            matrix[i][j] = rand() % 100;
        }
    }
}

int** multiplyMatrices(int **A, int **B, int r1, int c1, int r2, int c2) {
    int **result = allocateMatrix(r1, c2);
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < c1; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

int main() {
    SetConsoleOutputCP(866);
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    
    int size;
    printf("Vvedite razmer kvadratnykh matrits (naprimer, 100): ");
    scanf("%d", &size);
    
    printf("\nSozdaniye dvukh matrits %dx%d...\n", size, size);
    
    int **A = allocateMatrix(size, size);
    int **B = allocateMatrix(size, size);
    
    fillRandomMatrix(A, size, size);
    fillRandomMatrix(B, size, size);
    
    printf("Matritsy zapolneny. Nachinayem umnozheniye...\n\n");
    
    clock_t start = clock();
    
    int **C = multiplyMatrices(A, B, size, size, size, size);
    
    clock_t end = clock();
    
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("=== Rezul'tat umnozheniya (pervyye 5 strok i stolbtsov) ===\n");
    int displaySize = (size < 5) ? size : 5;
    for (int i = 0; i < displaySize; i++) {
        for (int j = 0; j < displaySize; j++) {
            printf("%6d ", C[i][j]);
        }
        if (size > 5) printf(" ...");
        printf("\n");
    }
    if (size > 5) printf("...\n");
    
    printf("\n========================================\n");
    printf("Vremya vypolneniya umnozheniya: %f sekund\n", time_spent);
    printf("Vremya vypolneniya umnozheniya: %f millisekund\n", time_spent * 1000);
    printf("========================================\n");
    
    freeMatrix(A, size);
    freeMatrix(B, size);
    freeMatrix(C, size);
    
    system("pause");
    return 0;
}
