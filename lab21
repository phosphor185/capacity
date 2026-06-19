#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

int main() {
    SetConsoleOutputCP(866);
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    
    int rows, cols;
    printf("Vvedite kolichestvo strok matritsy: ");
    scanf("%d", &rows);
    printf("Vvedite kolichestvo stolbtsov matritsy: ");
    scanf("%d", &cols);
    
    int **matrix1 = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix1[i] = (int*)malloc(cols * sizeof(int));
    }
    
    int **matrix2 = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix2[i] = (int*)malloc(cols * sizeof(int));
    }
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix1[i][j] = rand() % 100;
            matrix2[i][j] = rand() % 100;
        }
    }
    
    printf("\n=== Matritsa 1 ===\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix1[i][j]);
        }
        printf("\n");
    }
    
    printf("\n=== Matritsa 2 ===\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix2[i][j]);
        }
        printf("\n");
    }
    
    FILE *file = fopen("input.txt", "w");
    if (file == NULL) {
        printf("Oshibka sozdaniya fayla input.txt!\n");
    } else {
        fprintf(file, "%d %d\n", rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                fprintf(file, "%d ", matrix1[i][j]);
            }
            fprintf(file, "\n");
        }
        fprintf(file, "%d %d\n", rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                fprintf(file, "%d ", matrix2[i][j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
        printf("\nMatritsy zapisany v fayl input.txt\n");
    }
    
    for (int i = 0; i < rows; i++) {
        free(matrix1[i]);
        free(matrix2[i]);
    }
    free(matrix1);
    free(matrix2);
    
    printf("Massivy ochishcheny.\n");
    
    system("pause");
    return 0;
}
