#include <stdio.h>
#include <string.h>

#define BUFSIZE 10

int main() {
    double x, sum;
    sum = 0;
    char line[BUFSIZE];
    while (gets(line) > 0) {
        if (line[0] == '\0') {
            break;
        } else if (sscanf(line, "%lf", &x) == 1) {
            sum += x;
        }
    }
    printf("Sum: %f\n", sum);
}
