#include <stdio.h>

int find_triple(int *aPtr, int *bPtr, int *cPtr, int max) {
    int a, b, c;
    *aPtr = 0;
    *bPtr = 0;
    *cPtr = 0;
    for (a = 1; a <= max; a++) {
        for (b = 1; b <= max; b++) {
            for (c = 1; c <= max; c++) {
                if (a*a + b*b == c*c) {
                    *aPtr = a;
                    *bPtr = b;
                    *cPtr = c;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    int a, b, c;
    int triple_exists = find_triple(&a, &b, &c, 13);
    printf("Triple exists? %d\n", triple_exists);
    printf("Triple: (%d %d %d)\n", a, b, c);
}
