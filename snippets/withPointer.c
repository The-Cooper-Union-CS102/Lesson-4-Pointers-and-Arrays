#include <stdio.h>

void addOne(int *a) {
    *a += 1;
}

int main() {
    int a = 1;
    int *pointerToA = &a;
    addOne(pointerToA);
    printf("%d\n", a);
}
