#include <stdio.h>

int main() {
    char *names[4] = {"Cory", "Ross", "Gordon"};
    names[3] = "Deborah";
    int n;
    for (n = 0; n < 4; n++) {
        printf("name %d: %s\n", n, names[n]);
    }
}
