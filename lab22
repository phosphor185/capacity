#include <stdio.h>
#include <stdlib.h>
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

int** readMatrixFromFile(FILE *file, int *rows, int *cols) {
    fscanf(file, "%d %d", rows, cols);
    int **matrix = allocateMatrix(*rows, *cols);
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
    return matrix;
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

int** addMatrices(int **A, int **B, int rows, int cols) {
    int **result = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

void printMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%6d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void writeMatrixToFile(FILE *file, int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%6d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
}

int main() {
    SetConsoleOutputCP(866);
    setlocale(LC_ALL, "Russian");
    
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Oshibka otkrytiya fayla input.txt!\n");
        printf("Snachala zapustite zadaniye 1.\n");
        system("pause");
        return 1;
    }
    
    int r1, c1, r2, c2;
    
    int **mat1 = readMatrixFromFile(inputFile, &r1, &c1);
    int **mat2 = readMatrixFromFile(inputFile, &r2, &c2);
    fclose(inputFile);
    
    printf("=== Matritsa 1 (%dx%d) ===\n", r1, c1);
    printMatrix(mat1, r1, c1);
    
    printf("\n=== Matritsa 2 (%dx%d) ===\n", r2, c2);
    printMatrix(mat2, r2, c2);
    
    int **addResult = NULL;
    if (r1 == r2 && c1 == c2) {
        addResult = addMatrices(mat1, mat2, r1, c1);
        printf("\n=== Rezul'tat slozheniya ===\n");
        printMatrix(addResult, r1, c1);
    } else {
        printf("\nSlozheniye nevozmozhno: razmery matrits ne sovpadayut!\n");
    }
    
    int **multResult = NULL;
    if (c1 == r2) {
        multResult = multiplyMatrices(mat1, mat2, r1, c1, r2, c2);
        printf("\n=== Rezul'tat umnozheniya (%dx%d) ===\n", r1, c2);
        printMatrix(multResult, r1, c2);
    } else {
        printf("\nUmnnozheniye nevozmozhno!\n");
    }
    
    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile != NULL) {
        fprintf(outputFile, "=== Iskhodnyye matritsy ===\n\n");
        fprintf(outputFile, "Matritsa 1:\n");
        writeMatrixToFile(outputFile, mat1, r1, c1);
        fprintf(outputFile, "\nMatritsa 2:\n");
        writeMatrixToFile(outputFile, mat2, r2, c2);
        
        if (addResult != NULL) {
            fprintf(outputFile, "\n=== Rezul'tat slozheniya ===\n");
            writeMatrixToFile(outputFile, addResult, r1, c1);
        }
        
        if (multResult != NULL) {
            fprintf(outputFile, "\n=== Rezul'tat umnozheniya ===\n");
            writeMatrixToFile(outputFile, multResult, r1, c2);
        }
        
        fclose(outputFile);
        printf("\nRezul'taty zapisany v fayl output.txt\n");
    }
    
    freeMatrix(mat1, r1);
    freeMatrix(mat2, r2);
    if (addResult) freeMatrix(addResult, r1);
    if (multResult) freeMatrix(multResult, r1);
    
    system("pause");
    return 0;
}
