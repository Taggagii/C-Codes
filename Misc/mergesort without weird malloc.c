#include <stdio.h>
#include <stdlib.h>



// merge(dest, src1, len1, sec2, len2) modifies dest to contain the elements from both src1 and src2 in sorted order
void merge(int a[], int mid, int len) {
    int pos1 = 0;
    int pos2 = mid;
    int new[] = malloc(len * sizeof(int));
    for (int i = 0; i < len; ++i) {
        if (pos1 == mid || (pos2 < len && a[pos2] < a[pos1])) {
            new[i] = a[pos2];
            ++pos2;
        } else {
            new[i] = a[pos1];
            ++pos1;
        }
    }
    for (int i = 0; i < len; ++i) {
        a[i] = new[i];
    }
    free(new);
}



void merge_sort(int a[], int len) {
    if (len <= 1) return;
    int llen = len / 2;
    int rlen = len - llen;

    merge_sort(a, llen);
    merge_sort(a + llen, rlen);
    
    merge(a, llen, len);

}



int main(void) {
    // int a[] = {2, 3, 7, 1, 6, 9};
    // int length = sizeof(a) / sizeof(int);
    // merge(a, 3, 6);
    // for (int i = 0; i < length; ++i) {
    //     printf("%d\n", a[i]);
    // }

    int a[100];
    int b[100];
    int length = sizeof(a) / sizeof(int);
    for (int i = 0; i < length; ++i) {
        a[i] = rand() % 100; // in [0, 100)
        b[i] = a[i];
    }

    merge_sort(a, length);
    

}
