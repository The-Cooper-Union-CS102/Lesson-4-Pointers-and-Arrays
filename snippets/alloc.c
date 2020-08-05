#include <stdio.h>
#include <string.h>

#define ALLOCSIZE 10000 // size of available space

static char allocbuf[ALLOCSIZE]; // storage for alloc
static char *allocp = allocbuf; // next free position

char *alloc(int n) // return pointer to n characters
{
    int spaceUsed = allocp - allocbuf;
    int spaceLeft = ALLOCSIZE - spaceUsed;
    if (spaceLeft >= n) {
        // It fits
        allocp += n;
        return allocp - n; // old p
   } else {
        // Not enough room
        return 0;
   }
}

void afree(char *p) // free storage pointed to by p
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE) {
        // p within bounds of big array allocbuf
        allocp = p;
    }
}

// Store characters in soure s joined by sep into target, t
void join(char *s, char *t, char *sep) {
    // Assign first character
    *t = *s;
    s++;
    t++;
    while (*s != '\0') {
        char *sepStart = sep;
        while (*sep != '\0') {
            *t = *sep;
            t++;
            sep++;
        }
        sep = sepStart;
        *t = *s;
        t++;
        s++;
    }
}

int main() {
    char *s = alloc(100);
    s[0] = '0';
    s[1] = '1';
    s[2] = '2';
    s[3] = '\0';
    char *sep = alloc(3);
    sep[0] = ',';
    sep[1] = ' ';
    sep[2] = '\0';
    char *t = alloc(strlen(s) + (strlen(s)-1)*strlen(sep) + 1);
    join(s, t, sep);
    printf("%s -> %s\n", s, t);
}
