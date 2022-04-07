#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b; 
    *b = temp;
}

void quicksort(int a[], int len) {
    if (len <= 1) return;

    int pivot = *a;
    int pos = len - 1;

    for (int i = len - 1; i > 0; --i) {
        if (*(a + i) > pivot) {
            swap(a + pos, a + i);
            --pos;
        }
    }

    swap(a, a + pos);
    quicksort(a, pos);
    quicksort(a + (pos + 1), len - (pos + 1));
}






int main(void) {
    int a[] = {1, 4, 65, 3,2, 4, 2, 4, 4, 2, -1,1, 23, 52342};
    printf("Testing things\n");
    quicksort(a, sizeof(a) / 4);
    printf("testing\n");
    for (int i = 0; i < sizeof(a) / 4; ++i) {
        printf("%d, ", a[i]);
    }
}