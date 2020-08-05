#include <stdio.h>

int len(char *s) {
    int n = 0;
    while (*s != '\0') {
        n++;
        s++;
    }
    return n;
}

int main() {
    char *s = "12345";
    printf("Length of '%s': %d\n", s, len(s));
}
