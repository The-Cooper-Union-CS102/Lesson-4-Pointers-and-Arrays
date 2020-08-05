#include <stdio.h>
#include <string.h>

#define BUFSIZE 10

int main() {
    char line[BUFSIZE];
    FILE *filePointer = fopen("snippets/notexist.txt", "r");
    if (filePointer == NULL) {
        printf("ERROR: file could not be found.\n");
        return -1;
    }
    while (fgets(line, BUFSIZE, filePointer) > 0) {
        int len = strlen(line);
        printf("%s", line);
        if (line[len-1] != '\n') {
            printf("ERROR: line too long. Aborting.\n");
            return -1;
        }
    }
}
