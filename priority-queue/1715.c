#include <stdio.h>
#include <stdlib.h>

typedef struct MinHeap {
    int* arr;
    int capacity;
    int size;
} MinHeap;

void SwapElements(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

MinHeap* CreateMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (heap == NULL) {
        exit(1);
    }
    heap->arr = (int*)calloc(capacity + 1, sizeof(int)); 
    if (heap->arr == NULL) {
        free(heap);
        exit(1);
    }
    heap->capacity = capacity; 
    heap->size = 0;           
    return heap;
}

void MinHeapifyDown(MinHeap* heap, int idx) {
    int smallest = idx;
    int left_child_idx = 2 * idx;
    int right_child_idx = 2 * idx + 1;

    if (left_child_idx <= heap->size && heap->arr[left_child_idx] < heap->arr[smallest]) {
        smallest = left_child_idx;
    }

    if (right_child_idx <= heap->size && heap->arr[right_child_idx] < heap->arr[smallest]) {
        smallest = right_child_idx;
    }

    if (smallest != idx) {
        SwapElements(&heap->arr[idx], &heap->arr[smallest]);
        MinHeapifyDown(heap, smallest);
    }
}

void MinHeapifyUp(MinHeap* heap, int idx) {
    while (idx > 1 && heap->arr[idx] < heap->arr[idx / 2]) {
        SwapElements(&heap->arr[idx], &heap->arr[idx / 2]);
        idx = idx / 2; 
    }
}

void MinHeapInsert(MinHeap* heap, int k) {
    if (heap->size == heap->capacity) {
        return;
    }

    heap->size++; 
    heap->arr[heap->size] = k;

    MinHeapifyUp(heap, heap->size);
}

int MinHeapExtractMin(MinHeap* heap) {
    if (heap->size < 1) { 
        exit(1);
    }

    int root = heap->arr[1]; 

    if (heap->size == 1) {
        heap->size--;
        return root;
    }

    heap->arr[1] = heap->arr[heap->size];
    heap->size--; 

    if (heap->size > 0) { 
        MinHeapifyDown(heap, 1);
    }
    
    return root;
}

void FreeMinHeap(MinHeap* heap) {
    if (heap == NULL) {
        return;
    }
    if (heap->arr != NULL) {
        free(heap->arr);
    }
    free(heap);
}

int main() {
    int N;
    scanf("%d", &N);

    MinHeap* pq = CreateMinHeap(N); 

    for (int i = 0; i < N; i++) {
        int card_size;
        scanf("%d", &card_size);
        MinHeapInsert(pq, card_size);
    }

    int total_comparisons = 0;

    while (pq->size > 1) {
        int first_smallest = MinHeapExtractMin(pq);
        int second_smallest = MinHeapExtractMin(pq);

        int current_sum = first_smallest + second_smallest;
        total_comparisons += current_sum;

        MinHeapInsert(pq, current_sum);
    }

    printf("%d\n", total_comparisons);

    FreeMinHeap(pq);

    return 0;
}
