#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

int main() {
    SetConsoleOutputCP(866);
    setlocale(LC_ALL, "Russian");
    
    clock_t start = clock();
    
    printf("Vypolneniye programmy...\n");
    
    long long sum = 0;
    for (int i = 0; i < 100000000; i++) {
        sum += i;
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("Vremya vypolneniya: %f sekund\n", time_spent);
    printf("Vremya vypolneniya: %f millisekund\n", time_spent * 1000);
    
    system("pause");
    return 0;
}
