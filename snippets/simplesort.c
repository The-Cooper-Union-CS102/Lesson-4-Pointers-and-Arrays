#include <stdio.h>

void sort(int *a, int size) {
    int n, m;
    int temp;
    for (n = 0; n < size; n++) {
        for (m = n+1; m < size; m++) {
            if (a[n] > a[m]) {
                temp = a[n];
                a[n] = a[m];
                a[m] = temp;
            }
        }
    }
}

int main()
{
    int a[] = {3,4,5,63,1,2,3,7,7,6};
    sort(a, 10);
    for (int i = 0; i < 10; i++) {
    printf("%d\n", a[i]);
    }
    return 0;
}
