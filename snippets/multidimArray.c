/*
Prints rule 110:
111 110 101 100 011 010 001 000
 0   1   1   0   1   1   1   0
*/

#include <stdio.h>
#define M 80
#define N 80

int main() {
    int rule[] = {0, 1, 1, 1, 0, 1, 1, 0};
    int a[M][N] = {0};
    a[0][N-1] = 1;
    int m, n;
    int index;
    for (m = 1; m < M; m++) {
        for (n = 1; n < N-1; n++) {
            index = a[m-1][n-1]*4 + a[m-1][n]*2 + a[m-1][n+1];
            a[m][n] = rule[index];
        }
    }
    for (m = 0; m < M; m++) {
        for (n = 0; n < N-1; n++) {
            printf(a[m][n] ? "x" : " ");
        }
        printf("\n");
    }
}
