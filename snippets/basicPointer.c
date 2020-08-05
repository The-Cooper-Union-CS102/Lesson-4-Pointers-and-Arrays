#include <stdio.h>

int main() {
    int value = 1; // Read as value equals one
    int *pointer = &value; // Read as pointer equals to address of value
    printf("value: %d\n", value);
    printf("address: %p\n", pointer);
}
