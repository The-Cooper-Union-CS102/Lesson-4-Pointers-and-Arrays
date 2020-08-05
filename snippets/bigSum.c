#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int n;
    int sum = 0;
    for (n = 1; n < argc; n++) {
        sum += atoi(argv[n]);
    }
    printf("Sum: %d\n", sum);
}
