#include <stdio.h>

int main() {
    // Declare array `a`
    int a[15];
    int *b = a; // This is legal because `a` is really a pointer
    int n;
    // Set the n'th element of `b` to n
    for (n = 0; n < 15; n++) {
        b[n] = n;
    }
    // Print all elements of `a`
    for (n = 0; n < 15; n++) {
        printf("%d\n", a[n]);
    }
}
