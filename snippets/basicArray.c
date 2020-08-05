#include <stdio.h>

int main() {
    // Declare array `a`
    int a[15];
    int n;
    // Set the n'th element of `a` to n
    for (n = 0; n < 15; n++) {
        a[n] = n;
    }
    // Print all elements of `a`
    for (n = 0; n < 15; n++) {
        printf("%d\n", a[n]);
    }
}
