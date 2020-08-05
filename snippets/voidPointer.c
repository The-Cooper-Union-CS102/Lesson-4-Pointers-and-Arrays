#include <stdio.h> 

int main() {
    int x = (67 << 0) + //  C
            (79 << 8) + //  O
            (82 << 16) + // R
            (89 << 24); //  Y
    void *ptr = &x;
    printf("%lu\n", sizeof(int));
    printf("%lu\n", sizeof(char));
    printf("%d\n", *(int *)ptr);
    printf("%c", *((char *)ptr+0));
    printf("%c", *((char *)ptr+1));
    printf("%c", *((char *)ptr+2));
    printf("%c\n", *((char *)ptr+3));
} 
