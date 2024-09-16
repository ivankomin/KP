#include <stdio.h>
#include <conio.h>

// Функція для виведення римських цифр
int roman(int i, int j, char c);

int main(){
    unsigned a = 0;
    printf("This program converts numbers to roman numerals\n");
    printf("ENTER NUMBER from 1 to 4999\n");
    // Валідація вводу користувача
    if (scanf("%u", &a) != 1 || a > 4999 || a == 0){
        printf("Invalid input. Enter a number that is between 1 and 4999\n");
        return 0;
    }
    // Конвертування числа в римські цифри, починаючи з найбільшого значення
    a = roman(a, 1000, 'M');
    a = roman(a, 500, 'D');
    a = roman(a, 100, 'C');
    a = roman(a, 50, 'L');
    a = roman(a, 10, 'X');
    a = roman(a, 5, 'V');
    a = roman(a, 1, 'I');
    printf("\nPress any key to exit\n");
    getch(); // Очікування натискання клавіші для завершення програми
    return 0;
}

// Функція для виведення римських цифр відповідно до значення
int roman(int i, int j, char c){
    // Виведення символу римської цифри, поки залишок числа більший або дорівнює значенню
    while (i >= j){
        putchar(c);
        i = i - j;
    }
    return i; // Повертає залишок числа після конвертації
}
