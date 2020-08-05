#include <stdio.h>

int main() {
    double x;
    double sum = 0;
    while ((scanf("%lf", &x) == 1)) {
        printf("added: %lf\n", x);
        sum += x;
    }
    printf("Sum: %f\n", sum);
}
