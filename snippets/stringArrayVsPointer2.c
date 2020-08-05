#include <stdio.h>

int main() {
    char arrayString[] = "now is the time";
    char *pointerString = "now is the time";
    // Fine
    arrayString[0] = 'N';
    printf("%s\n", arrayString);
    // Fine
    pointerString = arrayString;
    pointerString[1] = 'O';
    printf("%s\n", pointerString);
}
