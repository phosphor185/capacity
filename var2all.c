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

void createRandomMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
}

void writeMatrixToFile(FILE *file, int **matrix, int rows, int cols) {
    fprintf(file, "%d %d\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
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

void findMinElement(int **matrix, int rows, int cols, int *minVal, int *minRow, int *minCol) {
    *minVal = matrix[0][0];
    *minRow = 0;
    *minCol = 0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] < *minVal) {
                *minVal = matrix[i][j];
                *minRow = i;
                *minCol = j;
            }
        }
    }
}

int countOddNumbers(int **matrix, int rows, int cols) {
    int count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] % 2 != 0) {
                count++;
            }
        }
    }
    return count;
}

int hasSameNumbersInRowOrCol(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        int same = 1;
        for (int j = 1; j < cols; j++) {
            if (matrix[i][j] != matrix[i][0]) {
                same = 0;
                break;
            }
        }
        if (same) return 1;
    }
    
    for (int j = 0; j < cols; j++) {
        int same = 1;
        for (int i = 1; i < rows; i++) {
            if (matrix[i][j] != matrix[0][j]) {
                same = 0;
                break;
            }
        }
        if (same) return 1;
    }
    
    return 0;
}

void printMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    SetConsoleOutputCP(866);
    setlocale(LC_ALL, "Russian");
    
    clock_t start = clock();
    srand(time(NULL));
    
    printf("=== VARIANT 2 - KOMBINIROVANNYY ===\n\n");
    
    int rows, cols;
    printf("Vvedite kolichestvo strok: ");
    scanf("%d", &rows);
    printf("Vvedite kolichestvo stolbtsov: ");
    scanf("%d", &cols);
    
    // ZADANIE 1: Sozdaniye input.txt
    printf("\n=== ZADANIE 1: Sozdaniye input.txt ===\n");
    
    int **matrix1 = allocateMatrix(rows, cols);
    int **matrix2 = allocateMatrix(rows, cols);
    
    createRandomMatrix(matrix1, rows, cols);
    createRandomMatrix(matrix2, rows, cols);
    
    FILE *inputFile = fopen("input.txt", "w");
    writeMatrixToFile(inputFile, matrix1, rows, cols);
    writeMatrixToFile(inputFile, matrix2, rows, cols);
    fclose(inputFile);
    
    printf("Matritsy zapisany v input.txt\n");
    
    freeMatrix(matrix1, rows);
    freeMatrix(matrix2, rows);
    
    // ZADANIE 2: Chteniye i operatsii
    printf("\n=== ZADANIE 2: Chteniye i operatsii ===\n");
    
    inputFile = fopen("input.txt", "r");
    int r1, c1, r2, c2;
    
    int **mat1 = readMatrixFromFile(inputFile, &r1, &c1);
    int **mat2 = readMatrixFromFile(inputFile, &r2, &c2);
    fclose(inputFile);
    
    printf("Matritsa 1:\n");
    printMatrix(mat1, r1, c1);
    
    printf("\nMatritsa 2:\n");
    printMatrix(mat2, r2, c2);
    
    int **multResult = NULL;
    if (c1 == r2) {
        multResult = multiplyMatrices(mat1, mat2, r1, c1, r2, c2);
        printf("\nRezultat umnozheniya:\n");
        printMatrix(multResult, r1, c2);
    } else {
        printf("\nUmnnozheniye nevozmozhno!\n");
    }
    
    int **addResult = NULL;
    if (r1 == r2 && c1 == c2) {
        addResult = addMatrices(mat1, mat2, r1, c1);
        printf("\nRezultat slozheniya:\n");
        printMatrix(addResult, r1, c1);
        
        FILE *outputFile = fopen("output.txt", "w");
        fprintf(outputFile, "Rezultat slozheniya:\n");
        for (int i = 0; i < r1; i++) {
            for (int j = 0; j < c1; j++) {
                fprintf(outputFile, "%d ", addResult[i][j]);
            }
            fprintf(outputFile, "\n");
        }
        if (multResult) {
            fprintf(outputFile, "\nRezultat umnozheniya:\n");
            for (int i = 0; i < r1; i++) {
                for (int j = 0; j < c2; j++) {
                    fprintf(outputFile, "%d ", multResult[i][j]);
                }
                fprintf(outputFile, "\n");
            }
        }
        fclose(outputFile);
        printf("\nZapisano v output.txt\n");
        
        freeMatrix(addResult, r1);
    }
    
    // ZADANIE 3: Minimum i nechotnyye
    printf("\n=== ZADANIE 3: Minimum i nechotnyye ===\n");
    
    int minVal, minRow, minCol;
    findMinElement(mat1, r1, c1, &minVal, &minRow, &minCol);
    printf("Minimal'nyy element v matritse 1: %d\n", minVal);
    printf("Pozitsiya: stroka %d, stolbets %d\n", minRow + 1, minCol + 1);
    
    int oddCount = countOddNumbers(mat1, r1, c1);
    printf("Kolichestvo nechotnykh chisel: %d\n", oddCount);
    
    // ZADANIE 4: Odinakovyye chisla
    printf("\n=== ZADANIE 4: Odinakovyye chisla ===\n");
    
    if (hasSameNumbersInRowOrCol(mat1, r1, c1)) {
        printf("Matritsa 1 soderzhit stroku/stolbets s odinakovymi chislami\n");
    } else {
        printf("Matritsa 1 NE soderzhit strok/stolbtsov s odinakovymi chislami\n");
    }
    
    if (hasSameNumbersInRowOrCol(mat2, r2, c2)) {
        printf("Matritsa 2 soderzhit stroku/stolbets s odinakovymi chislami\n");
    } else {
        printf("Matritsa 2 NE soderzhit strok/stolbtsov s odinakovymi chislami\n");
    }
    
    // ZADANIE 5: Zamer vremeni
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n=== ZADANIE 5: Vremya vypolneniya ===\n");
    printf("Obshcheye vremya raboty programmy: %.6f sekund\n", time_spent);
    printf("Obshcheye vremya raboty programmy: %.2f millisekund\n", time_spent * 1000);
    
    freeMatrix(mat1, r1);
    freeMatrix(mat2, r2);
    if (multResult) freeMatrix(multResult, r1);
    
    system("pause");
    return 0;
}
