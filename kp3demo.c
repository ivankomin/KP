#include <stdio.h>
#include <conio.h>
#include <math.h>

int main() {

    printf("\nThis application will calculate the K-th root of an X with specified precision (E).\n");
    printf("Press Enter to proceed...\n");
    getch();

    while (1) {

        double k = 0, x = 0, e = 0;

        // input
        do {
            printf("Enter the root degree (k): \n");
            scanf("%lf", &k);
            fflush(stdin);
            if (k == 0) {
                printf("Error: the root degree cannot be equal to 0.\nPlease, try again.\n\n");
            } else break;
        } while (1);
        printf("Enter the radical (x): \n");
        scanf("%lf", &x);
        fflush(stdin);
        do {
            printf("Enter the accuracy (from 1e-15 to 1e-1): \n");
            scanf("%lf", &e);
            fflush(stdin);
            if (e > 0.1) {
                printf("Error: the accuracy is too big.\nPlease, try again.\n\n");
            } else break;
        } while (1);

        if ((int)k % 2 == 0 && x < 0) {
            printf("Error: wrong input, solution is not real.\n");
            getch();
            return -1;
        }

        // calculation
        double y = 1;
        if (x != 0) {
            if (k < 0) {
                k = -k;
                x = 1/x;
            }
            while (1) {
                const double d = 1/k*(x/pow(y,k-1)-y);
                if (fabs(d) < e) {
                    break;
                }
                y+=d;
            }
        } else y = 0;

        // result
        printf("Result : %.*lf\n", (int)-log10(e), y);

        // loop ender
        char answer;
        do {
            printf("\nDo you want to continue? (y/n) : ");
            scanf(" %s", &answer);
            if (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N') {
                printf("Invalid input, please try again.\n");
            } else break;
            fflush(stdin);
        } while (1);

        if (answer == 'n' || answer == 'N') {
            printf("Press Enter to exit...\n");
            getch();
            return 0;
        }
    }
}