#include <stdio.h>

int main() {
    char arrayString[] = "now is the time";
    char *pointerString = "now is the time";
    // Fine
    arrayString[0] = 'N';
    printf("%s\n", arrayString);
    // Wrong
    pointerString[0] = 'N';
    printf("%s\n", pointerString);
}
