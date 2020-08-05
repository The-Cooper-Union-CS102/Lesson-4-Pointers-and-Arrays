#include <stdio.h>

int main() {
    char *names[4];
    names[0] = "Cory";
    names[1] = "Ross";
    names[2] = "Gordon";
    names[3] = "Deborah";
    int n;
    for (n = 0; n < 4; n++) {
        printf("name %d: %s\n", n, names[n]);
    }
}
