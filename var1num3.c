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

int sumMatrix(int **matrix, int m) {
    int sum = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            sum += matrix[i][j];
        }
    }
    return sum;
}

void printMatrix(int **matrix, int m) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void writeMatrixToFile(FILE *file, int **matrix, int m, int sum) {
    fprintf(file, "Summa: %d\n", sum);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");
}

int main() {
    SetConsoleOutputCP(866);
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    
    int m;
    printf("Vvedite razmer matritsy: ");
    scanf("%d", &m);
    
    int **mat1 = allocateMatrix(m);
    int **mat2 = allocateMatrix(m);
    int sum1, sum2;
    int counter = 0;
    
    printf("Generatsiya matrits...\n\n");
    
    do {
        fillRandomMatrix(mat1, m);
        sum1 = sumMatrix(mat1, m);
        
        fillRandomMatrix(mat2, m);
        sum2 = sumMatrix(mat2, m);
        
        counter++;
        
        printf("--- Popytka #%d ---\n", counter);
        
        printf("Matritsa 1 (summa = %d):\n", sum1);
        printMatrix(mat1, m);
        
        printf("Matritsa 2 (summa = %d):\n", sum2);
        printMatrix(mat2, m);
        
        if (sum1 == sum2) {
            printf(">>> SUMMY SOVPALI! <<<\n");
        } else {
            printf("Summy ne sovpadayut...\n");
        }
        printf("\n");
        
    } while (sum1 != sum2);
    
    printf("Naydeno posle %d popytok!\n", counter);
    printf("Obshchaya summa: %d\n\n", sum1);
    
    printf("=== MATRITSA 1 ===\n");
    printMatrix(mat1, m);
    
    printf("=== MATRITSA 2 ===\n");
    printMatrix(mat2, m);
    
    FILE *file = fopen("output.txt", "w");
    if (file != NULL) {
        fprintf(file, "Naydeny posle %d popytok\n", counter);
        fprintf(file, "Matritsy s odinakovoy summoy %d:\n\n", sum1);
        fprintf(file, "Matritsa 1:\n");
        writeMatrixToFile(file, mat1, m, sum1);
        fprintf(file, "Matritsa 2:\n");
        writeMatrixToFile(file, mat2, m, sum2);
        fclose(file);
        printf("Zapisano v output.txt\n");
    }
    
    for (int i = 0; i < m; i++) {
        free(mat1[i]);
        free(mat2[i]);
    }
    free(mat1);
    free(mat2);
    
    system("pause");
    return 0;
}
