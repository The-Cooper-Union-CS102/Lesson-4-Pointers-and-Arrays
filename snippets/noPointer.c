#include <stdio.h>

void addOne(int a) {
    a += 1;
}

int main() {
    int a = 1;
    addOne(a);
    printf("%d\n", a);
}
