#include <stdio.h>

int main() {
    int x = 1;
    int *px = &x;
    int **ppx = &px;
    int ***pppx = &ppx;
    printf("x: %d\n", ***pppx);
}
