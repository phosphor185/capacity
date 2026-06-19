#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

int main() {
    SetConsoleOutputCP(866);
    setlocale(LC_ALL, "Russian");
    
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Oshibka otkrytiya fayla input.txt!\n");
        printf("Snachala zapustite zadaniye 1.\n");
        system("pause");
        return 1;
    }
    
    int rows, cols;
    fscanf(file, "%d %d", &rows, &cols);
    
    int **matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
    fclose(file);
    
    printf("=== Matritsa 1 (%dx%d) ===\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    int minVal = matrix[0][0];
    int minRow = 0, minCol = 0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j];
                minRow = i;
                minCol = j;
            }
        }
    }
    
    printf("\nMinimal'nyy element: %d\n", minVal);
    printf("Nomer stroki: %d\n", minRow + 1);
    printf("Nomer stolbtsa: %d\n", minCol + 1);
    printf("Pozitsiya (indeksy s 0): [%d][%d]\n", minRow, minCol);
    
    int oddCount = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] % 2 != 0) {
                oddCount++;
            }
        }
    }
    
    printf("\nKolichestvo nechotnykh chisel v matritse: %d\n", oddCount);
    
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    system("pause");
    return 0;
}
