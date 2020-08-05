#include <stdio.h>

int stringCompare(char *a, char *b) {
    while (*a == *b) {
        if (*a == '\0') {
            return 0;
        }
        a++;
        b++;
    }
    return *a - *b;
}

void sort(void *a[], int size, int (*compare) (void *, void *)) {
    int n, m;
    void *temp;
    for (n = 0; n < size; n++) {
        for (m = n; m >= 1; m--) {
            if (compare(a[m], a[m-1]) < 0) {
                temp = a[m-1];
                a[m-1] = a[m];
                a[m] = temp;
            }
        }
    }
}

int main() {
    char *names[] = {"Cory", "Zoe", "Ross", "Gordon", "Deborah"};
    sort((void *) names, 5, (int (*)(void *, void *))(stringCompare));
    int n;
    for (n = 0; n < 5; n++) {
        printf("name %d: %s\n", n, names[n]);
    }
}
