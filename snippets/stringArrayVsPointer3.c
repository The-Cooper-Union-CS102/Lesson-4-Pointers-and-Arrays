#include <stdio.h>

int main() {
    char arrayString[] = "now is the time";
    char *pointerString = "now is the time";
    // Fine
    ++pointerString;
    printf("%s\n", pointerString);
    // Wrong
    ++arrayString;
    printf("%s\n", arrayString);
}
