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

int main() {
    SetConsoleOutputCP(866);
    setlocale(LC_ALL, "Russian");
    
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Oshibka otkrytiya fayla input.txt!\n");
        system("pause");
        return 1;
    }
    
    int day, month, year;
    fscanf(file, "%d %d %d", &day, &month, &year);
    fclose(file);
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int currDay = tm.tm_mday;
    int currMonth = tm.tm_mon + 1;
    int currYear = tm.tm_year + 1900;
    
    int days = daysBetweenDates(currDay, currMonth, currYear, day, month, year);
    printf("Dney do daty: %d\n", days);
    
    system("pause");
    return 0;
}
