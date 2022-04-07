#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

void print_fibs_list(int n) {
    assert(n > 0);

    int *fibs = malloc(n * sizeof(int));
    fibs[0] = 0;
    fibs[1] = 1;
    for (int i = 2; i < n; ++i) {
        fibs[i] = fibs[i - 1] + fibs[i - 2];
    }
    for (int i = 0; ;) {
        printf("%d", fibs[i]);
        if (++i == n) break;
        printf(", ");
    }
    printf("\n");
    free(fibs);

}

void print_fibs_interative(int n) {
    
    int a = 0;
    int b = 1;
    if (n == 1) {
        printf("%d", a);
    }
    if (n == 2) {
        printf("%d, %d", a, b);
    } else {
        printf("%d, %d, ", a, b);
        for (int i = 2; ;) {
            int sum = a + b;
            a = b;
            b = sum;
            printf("%d", b);
            if (++i == n) break;
            printf(", ");
        }
    }
    printf("\n");
} 

static int fib(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    return fib(n - 1) + fib(n - 2);
}

void print_fibs_recursive(int n) {
    for (int i = 0; ;) {
        printf("%d", fib(i));
        if (++i == n) break;
        printf(", ");
    }
    printf("\n");
}



int main(void) {
    print_fibs_recursive(10);
}