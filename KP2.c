#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c;
    int continueProgram;
    printf("This program calculates the perimeter and area of a triangle as well as the height, median and bisector of each side.\n");
    
    do {
        // Зчитування сторін трикутника
        printf("Enter side a: ");
        if (scanf("%lf", &a) != 1 || a <= 0.01 || a >= 1000) {
            printf("Enter valid number between 0.01 and 1000!\n");
            return 0;
        }
        printf("Enter side b: ");
        if (scanf("%lf", &b) != 1 || b <= 0.01 || b >= 1000) {
            printf("Enter valid number between 0.01 and 1000!\n");
            return 0;
        }
        printf("Enter side c: ");
        if (scanf("%lf", &c) != 1 || c <= 0.01 || c >= 1000) {
            printf("Enter valid number between 0.01 and 1000!\n");
            return 0;
        }

        // Перевірка на те, чи є задані сторони трикутником
        if ((a + b <= c) || (a + c <= b) || (b + c <= a)) {
            printf("The entered sides do not form a triangle!\n");
            return 0;
        }

        unsigned decNum = 0;
        // Зчитування кількості десяткових знаків для виводу
        printf("Enter a number of decimal places (0-12): ");
        if ((scanf("%u", &decNum) != 1) || (decNum > 12)) {
            printf("Enter valid number!\n");
            return 0;
        }

        // Обчислення периметра і площі трикутника
        double P = a + b + c;
        double p = (a + b + c) / 2;
        double s = sqrt(p * (p - a) * (p - b) * (p - c));
        
        // Обчислення висот трикутника
        double hForA = (2 * s) / a;
        double hForB = (2 * s) / b;
        double hForC = (2 * s) / c;
        
        // Обчислення медіан трикутника
        double mForA = (sqrt(2*pow(b,2) + pow(c,2) - pow(a,2))) / 2.0;
        double mForB = (sqrt(2*pow(a,2) + pow(c,2) - pow(b,2))) / 2.0;
        double mForC = (sqrt(2*pow(a,2) + pow(b,2) - pow(c,2))) / 2.0;

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
