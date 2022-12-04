#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int maxInt(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

typedef struct HeapTemp {
    int length; // number of elements
    int size; // actual memory size
    int* values;
} Heap;

void heapSwap(Heap* heap, int indexA, int indexB) {
    if (heap == NULL) {
        return;
    }

    if (indexA >= heap->length || indexB >= heap->length) {
        return;
    }

    int temp = heap->values[indexA];
    heap->values[indexA] = heap->values[indexB];
    heap->values[indexB] = temp;
}

Heap* createHeap() {
    Heap* tempHeap = (Heap*) malloc(sizeof(Heap));
    tempHeap->length = 0;
    tempHeap->size = 1;
    tempHeap->values = (int*) malloc(tempHeap->size * sizeof(int));
    return tempHeap;
}

void printHeap(Heap* heap) {
    if (heap == NULL || heap->size == 0) {
        return;
    }
    for (int i = 0; i < heap->length; ++i) {
        printf("%d", heap->values[i]);
        if (i < heap->length - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

void heapFloat(Heap* heap, int index) {
    int curIndex = index;
    while (curIndex > 0) {
        int parentIndex = (curIndex - 1) / 2;
        if (heap->values[curIndex] < heap->values[parentIndex]) {
            heapSwap(heap, curIndex, parentIndex);
            curIndex = parentIndex;
        } else {
            break;
        }
    }
}

void addHeap(Heap* heap, int value) {
    if (heap == NULL) {
        return;
    }

    if (heap->size == heap->length) {
        heap->size *= 2;
        heap->values = (int*) realloc(heap->values, heap->size * sizeof(int));
    }

    heap->values[heap->length] = value;
    heapFloat(heap, heap->length++);
}

void heapSink(Heap* heap, int index) {
    int curIndex = index;
    while (1) {
        int childIndexOne = 2 * curIndex + 1;
        int childIndexTwo = childIndexOne + 1;
        // go to the min of the two
        int smallerIndex = childIndexTwo;
        if (heap->values[childIndexOne] < heap->values[childIndexTwo]) {
            smallerIndex = childIndexOne;
        }
        if (heap->values[smallerIndex] < heap->values[curIndex]) {
            heapSwap(heap, smallerIndex, curIndex);
            curIndex = smallerIndex;
        } else {
            break;
        }
    }
}

int pollHeap(Heap* heap) {
    if (heap == NULL || heap->length == 0) {
        return -1;
    }
    int valueToReturn = heap->values[0];

    int lastIndex = heap->length - 1;
    
    // swap first and last
    heapSwap(heap, 0, heap->length - 1);
    // remove last element 
    --heap->length;

    heapSink(heap, 0);
    return valueToReturn;
}

int randomInt(int max) {
    return rand() % max;
}


int main() {
    Heap* heap = createHeap();
    srand(time(NULL));
    for (int i = 0; i < 100; ++i) {
        addHeap(heap, rand() % 50);
    }

    while (heap->length) {
        printf("%d\n", pollHeap(heap));
    }
    free(heap);
}
