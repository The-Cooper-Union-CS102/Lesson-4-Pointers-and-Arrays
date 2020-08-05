#include <stdio.h>

void swap(int *px, int *py) {
    int temp;
    temp = *px;
    *px = 0;
    *py = temp;
}

int main() {
    int a = 8;
    int b = 3;
    int *aPtr = &a;
    int *bPtr = &b;
    swap(aPtr, bPtr);
}
