#include <stdio.h>

int main() {
    int c;
    while ((c = getchar()) != EOF) {
        printf("%c", c);
    }
    printf("--Done reading!--\n");
}
