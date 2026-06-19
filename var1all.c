#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year))
        return 29;
    return days[month - 1];
}

int daysFromDate(int day, int month, int year) {
    int days = day;
    for (int m = 1; m < month; m++) {
        days += daysInMonth(m, year);
    }
    return days;
}

int daysBetweenDates(int d1, int m1, int y1, int d2, int m2, int y2) {
    long int n1 = daysFromDate(d1, m1, y1);
    for (int y = 1; y < y1; y++) {
        n1 += isLeapYear(y) ? 366 : 365;
    }
    
    long int n2 = daysFromDate(d2, m2, y2);
    for (int y = 1; y < y2; y++) {
        n2 += isLeapYear(y) ? 366 : 365;
    }
    
    return (n2 - n1);
}

int** allocateMatrix(int m) {
    int **matrix = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        matrix[i] = (int*)malloc(m * sizeof(int));
    }
    return matrix;
}

void freeMatrix(int **matrix, int m) {
    for (int i = 0; i < m; i++) {
        free(matrix[i]);
    }
    free(matrix);
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
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
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

void findMinAndOdd(int **matrix, int m) {
    int minVal = matrix[0][0];
    int minRow = 0, minCol = 0;
    int oddCount = 0;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j];
                minRow = i;
                minCol = j;
            }
            if (matrix[i][j] % 2 != 0) {
                oddCount++;
            }
        }
    }
    
    printf("\n--- ZADANIE 3: Analiz matritsy ---\n");
    printf("Minimal'nyy element: %d\n", minVal);
    printf("Pozitsiya minimuma: stroka %d, stolbets %d (indeksy: [%d][%d])\n", 
           minRow + 1, minCol + 1, minRow, minCol);
    printf("Kolichestvo nechotnykh chisel: %d\n", oddCount);
}

int hasSameNumbersInRowOrCol(int **matrix, int m, int *foundRow, int *foundCol, int *isRow) {
    for (int i = 0; i < m; i++) {
        int same = 1;
        for (int j = 1; j < m; j++) {
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
    
    for (int j = 0; j < m; j++) {
        int same = 1;
        for (int i = 1; i < m; i++) {
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

void checkSameNumbers(int **matrix, int m, int matrixNum) {
    int foundRow, foundCol, isRow;
    
    printf("\n--- ZADANIE 4: Proverka matritsy %d ---\n", matrixNum);
    
    if (hasSameNumbersInRowOrCol(matrix, m, &foundRow, &foundCol, &isRow)) {
        if (isRow) {
            printf("Stroka #%d soderzhit odinakovyye chisla: ", foundRow + 1);
            for (int j = 0; j < m; j++) {
                printf("%d ", matrix[foundRow][j]);
            }
            printf("\n");
        } else {
            printf("Stolbets #%d soderzhit odinakovyye chisla: ", foundCol + 1);
            for (int i = 0; i < m; i++) {
                printf("%d ", matrix[i][foundCol]);
            }
            printf("\n");
        }
    } else {
        printf("Net strok ili stolbtsov s odinakovymi chislami\n");
    }
}

int main() {
    SetConsoleOutputCP(866);
    setlocale(LC_ALL, "Russian");
    
    clock_t start = clock();
    
    printf("=== VARIANT 1 - ITOGOVAYA RABOTA ===\n\n");
    
    // ZADANIE 1
    printf("=== ZADANIE 1: Raschet dney do daty ===\n\n");
    
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Oshibka: fayl input.txt ne nayden!\n");
        printf("Sozdayte fayl s datoy v formate: den' mesyats god\n");
        printf("Primer: 25 12 2026\n\n");
    } else {
        int day, month, year;
        fscanf(file, "%d %d %d", &day, &month, &year);
        fclose(file);
        
        printf("Data iz fayla: %d.%d.%d\n", day, month, year);
        
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        int currDay = tm.tm_mday;
        int currMonth = tm.tm_mon + 1;
        int currYear = tm.tm_year + 1900;
        
        printf("Tekushchaya data: %d.%d.%d\n", currDay, currMonth, currYear);
        
        int days = daysBetweenDates(currDay, currMonth, currYear, day, month, year);
        
        if (days > 0) {
            printf("Dney do ukazannoy daty: %d\n", days);
        } else if (days < 0) {
            printf("Data uzhe proshla. Proshlo dney: %d\n", -days);
        } else {
            printf("Eto segodnyashnyaya data!\n");
        }
        printf("\n");
    }
    
    // ZADANIE 2
    printf("=== ZADANIE 2: Sozdaniye matrits ===\n\n");
    
    int m;
    printf("Vvedite razmer kvadratnoy matritsy m: ");
    scanf("%d", &m);
    
    int **matrix1 = allocateMatrix(m);
    int **matrix2 = allocateMatrix(m);
    
    int sum1, sum2;
    int counter = 0;
    
    printf("\nGeneratsiya dvukh matrits s odinakovoy summoy...\n\n");
    
    do {
        fillRandomMatrix(matrix1, m);
        sum1 = sumMatrix(matrix1, m);
        
        fillRandomMatrix(matrix2, m);
        sum2 = sumMatrix(matrix2, m);
        
        counter++;
        
        if (counter % 10000 == 0) {
            printf("Popytka %d... (summa1=%d, summa2=%d)\n", counter, sum1, sum2);
        }
        
    } while (sum1 != sum2);
    
    printf("\nNaydeno posle %d popytok!\n", counter);
    printf("Obshchaya summa elementov obeikh matrits: %d\n\n", sum1);
    
    printf("=== MATRITSA 1 ===\n");
    printMatrix(matrix1, m);
    printf("Summa: %d\n\n", sum1);
    
    printf("=== MATRITSA 2 ===\n");
    printMatrix(matrix2, m);
    printf("Summa: %d\n\n", sum2);
    
    // ZADANIE 3
    findMinAndOdd(matrix1, m);
    
    // ZADANIE 4
    checkSameNumbers(matrix1, m, 1);
    checkSameNumbers(matrix2, m, 2);
    
    // Zapis' v fayl
    file = fopen("output.txt", "w");
    if (file != NULL) {
        fprintf(file, "VARIANT 1 - REZUL'TATY\n");
        fprintf(file, "======================\n\n");
        
        fprintf(file, "Kolichestvo popytok dlya podbora: %d\n", counter);
        fprintf(file, "Summa elementov obeikh matrits: %d\n\n", sum1);
        
        fprintf(file, "MATRITSA 1 (summa = %d):\n", sum1);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                fprintf(file, "%d ", matrix1[i][j]);
            }
            fprintf(file, "\n");
        }
        
        fprintf(file, "\nMATRITSA 2 (summa = %d):\n", sum2);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                fprintf(file, "%d ", matrix2[i][j]);
            }
            fprintf(file, "\n");
        }
        
        fclose(file);
        printf("\nRezul'taty zapisany v fayl output.txt\n");
    }
    
    freeMatrix(matrix1, m);
    freeMatrix(matrix2, m);
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n=== VREMYA VYPOLNENIYA ===\n");
    printf("Obshcheye vremya raboty programmy: %.6f sekund\n", time_spent);
    printf("Obshcheye vremya raboty programmy: %.2f millisekund\n", time_spent * 1000);
    
    system("pause");
    return 0;
}
