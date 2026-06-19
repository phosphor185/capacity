#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

int** allocateMatrix(int m) {
    int **matrix = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        matrix[i] = (int*)malloc(m * sizeof(int));
    }
    return matrix;
}

void fillRandomMatrix(int **matrix, int m) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

void printMatrix(int **matrix, int m) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    SetConsoleOutputCP(866);
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    
    int m;
    printf("Vvedite razmer matritsy m: ");
    scanf("%d", &m);
    
    int **matrix = allocateMatrix(m);
    fillRandomMatrix(matrix, m);
    
    printf("Matritsa:\n");
    printMatrix(matrix, m);
    
    for (int i = 0; i < m; i++)
        free(matrix[i]);
    free(matrix);
    
    system("pause");
    return 0;
}
