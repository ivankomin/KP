#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c;//=0
    int continueProgram;
    printf("This program calculates the perimeter and area of a triangle as well as the height, median and bisector for each side.\n");
    
    do {
        int validInput;
        // Цикл для валідації вводу сторони a
        do {
            printf("Enter side a: ");
            validInput = scanf("%lf", &a);

            // Перевірка, чи ввід дійсний і в межах допустимого діапазону
            if (validInput != 1 || a <= 0.01 || a >= 1000) {
                printf("Enter a valid number between 0.01 and 1000!\n");
                // Очищення буфера вводу
                while (getchar() != '\n');
            } 
            else {
                // Вийти з циклу, якщо ввід дійсний
                break;
            }//add flush here, remove break
        } while (validInput != 1 || a <= 0.01 || a >= 1000);

        // Цикл для валідації вводу сторони b
        do {
            printf("Enter side b: ");
            validInput = scanf("%lf", &b);

            // Перевірка, чи ввід дійсний і в межах допустимого діапазону
            if (validInput != 1 || b <= 0.01 || b >= 1000) {
                printf("Enter a valid number between 0.01 and 1000!\n");
                // Очищення буфера вводу
                while (getchar() != '\n');
            } 
            else {
                // Вийти з циклу, якщо ввід дійсний
                break;
            }
        } while (validInput != 1 || b <= 0.01 || b >= 1000);

        // Цикл для валідації вводу сторони c
        do {
            printf("Enter side c: ");
            validInput = scanf("%lf", &c);

            // Перевірка, чи ввід дійсний і в межах допустимого діапазону
            if (validInput != 1 || c <= 0.01 || c >= 1000) {
                printf("Enter a valid number between 0.01 and 1000!\n");
                // Очищення буфера вводу
                while (getchar() != '\n');
            } 
            else {
                // Вийти з циклу, якщо ввід дійсний
                break;
            }
        } while (validInput != 1 || c <= 0.01 || c >= 1000);

        // Перевірка, чи сторони утворюють дійсний трикутник
        if ((a + b <= c) || (a + c <= b) || (b + c <= a)) {
            printf("The entered sides do not form a triangle!\n");
            // Перезапуск зовнішнього циклу для повторного введення
            continue;
        }

        unsigned decNum = 0;
        // Зчитування кількості десяткових знаків для виводу
        
        do{
            printf("Enter a number of decimal places (0-12): ");
            validInput = scanf("%u", &decNum);
            if (validInput != 1 || decNum > 12) {
                printf("Enter valid number!\n");
                while (getchar() != '\n');
            }
            else {
                break;
            }
        } while (decNum > 12 || validInput != 1);

        // Обчислення периметра і площі трикутника
        double P = a + b + c;
        double p = (a + b + c) / 2.0;
        double s = sqrt(p * (p - a) * (p - b) * (p - c));
        
        // Обчислення висот трикутника
        double hForA = (2.0 * s) / a;
        double hForB = (2.0 * s) / b;
        double hForC = (2.0 * s) / c;
        
        // Обчислення медіан трикутника
        double mForA = (sqrt(2.0*pow(b,2) + pow(c,2) - pow(a,2))) / 2.0;
        double mForB = (sqrt(2.0*pow(a,2) + pow(c,2) - pow(b,2))) / 2.0;
        double mForC = (sqrt(2.0*pow(a,2) + pow(b,2) - pow(c,2))) / 2.0;

        // Обчислення бісектрис трикутника
        double bisForA = (2.0 / (b + c)) * sqrt(b * c * p * (p - a));
        double bisForB = (2.0 / (a + c)) * sqrt(a * c * p * (p - b));
        double bisForC = (2.0 / (a + b)) * sqrt(a * b * p * (p - c));

        // Виведення результатів
        printf("\nPerimeter: %.*lf\n", decNum, P);
        printf("Area: %.*lf\n", decNum, s);

        printf("\nHeight for side a: %.*lf\n", decNum, hForA);
        printf("Height for side b: %.*lf\n", decNum, hForB);
        printf("Height for side c: %.*lf\n", decNum, hForC);

        printf("\nMedian for side a: %.*lf\n", decNum, mForA);
        printf("Median for side b: %.*lf\n", decNum, mForB);
        printf("Median for side c: %.*lf\n", decNum, mForC);

        printf("\nBisector for side a: %.*lf\n", decNum, bisForA);
        printf("Bisector for side b: %.*lf\n", decNum, bisForB);
        printf("Bisector for side c: %.*lf\n", decNum, bisForC);
        printf("\n");

        // Запит на продовження або вихід з програми
        printf("To continue this program, enter 1 and press Enter.\n");
        printf("To exit the program, enter 0 and press Enter.\n");

        // Очистка буфера вводу
        while (getchar() != '\n');

        if (scanf("%d", &continueProgram) != 1 || (continueProgram != 0 && continueProgram != 1)) {
            printf("Invalid input. Exiting the program.\n");
            return 0;
        }

        // Очистка буфера вводу після зчитування вибору
        while (getchar() != '\n');
        
    } while (continueProgram == 1);

    return 0;
}
