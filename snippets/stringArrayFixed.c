#include <stdio.h>

int main() {
    char *names[3] = {"Cory", "Ross", "Gordon"};
    int n;
    for (n = 0; n < 3; n++) {
        printf("name %d: %s\n", n, names[n]);
    }
}
