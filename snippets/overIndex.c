#include <stdio.h>

int main() {
    // Declare array `a`
    int a[15];
    int n;
    // Set the n'th element of `b` to n
    // Not that 30 is greater than
    for (n = 0; n < 30; n++) {
        *(a+n) = n;
    }
    // Print all elements of `a`
    for (n = 0; n < 30; n++) {
        printf("%d\n", *(a+n));
    }
}
