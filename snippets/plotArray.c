#include <stdio.h>
#include <math.h>


void plotArray(int *a, int length, int height) {
    int m, n;
    for (n = 0; n < height; n++) {
        for (m = 0; m < length; m++) {
            if (a[length-m] == n) {
                printf("x");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}


int main() {
    // Declare array `a`
    int a[40];
    int n;
    // Set the n'th element of `a` to n
    for (n = 0; n < 40; n++) {
        a[n] = n*n/16;
    }
    plotArray(a, 40, 40);
}
