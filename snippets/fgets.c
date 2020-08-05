#include <stdio.h>
#include <string.h>

#define BUFSIZE 10

int main() {
    double x, sum;
    sum = 0;
    char line[BUFSIZE];
    while (fgets(line, BUFSIZE, stdin) > 0) {
        if (line[0] == '\n') {
            break;
        } else if (sscanf(line, "%lf", &x) == 1) {
            sum += x;
        }
    }
    printf("Sum: %f\n", sum);
}
