#include <stdio.h>

int main() {
    int x, y, result;
    char op;
    scanf("%d %d %c", &x, &y, &op);
    if (op == '+') {
        result = x + y;
    } else if (op == '-') {
        result = x - y;
    } else if (op == '*') {
        result = x * y;
    } else if (op == '/') {
        result = x / y;
    }
    printf("%d\n", result);
}
