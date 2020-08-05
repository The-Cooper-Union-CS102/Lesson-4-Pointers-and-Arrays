#include <stdio.h>

int main(int argc, char *argv[]) {
    int n;
    for (n = 0; n < argc; n++) {
        printf("%s", argv[n]);
        if (n < (argc - 1)) {
            printf("\n");
        }
    }
    printf("\n");
}
