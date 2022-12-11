#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int array[1000];
    unsigned int top;
} MinHeap;

#define fst_child_index(index) ((index + 1) * 2 - 1)
#define snd_child_index(index) ((index + 1) * 2)
#define parent_index(index) ((index - 1) / 2)
#define swap(type, a, b) \
    type c = a;          \
    a = b;               \
    b = c;
#define fst_leaf_index(heap) parent_index(heap.top) + 1

void print_heap(MinHeap heap)
{
    printf("{");
    for (int i = 0; i <= heap.top; i++)
        printf("%d,", heap.array[i]);
    printf("\b}\n");
}
void bubble_up(MinHeap *heap, unsigned int index)
{
    int *item = &heap->array[index];
    while (parent_index((item - heap->array)) >= 0 && *item < heap->array[parent_index((item - heap->array))])
    {
        printf("item at %d\n", item - heap->array);
        printf("swapping %d with %d\n", *item, heap->array[parent_index((item - heap->array))]);
        swap(int, *item, heap->array[parent_index((item - heap->array))]);
        item = heap->array + parent_index((item - heap->array));
    }
}

int min_child_index(MinHeap heap, unsigned int index)
{
    int fst_child_ind = fst_child_index((index));
    int snd_child_ind = snd_child_index((index));
    if (fst_child_ind > heap.top)
        return -1;
    if (snd_child_ind > heap.top)
        return fst_child_ind;

    return (heap.array[fst_child_ind] > heap.array[snd_child_ind] ? snd_child_ind : fst_child_ind);
}

void bubble_down(MinHeap *heap, unsigned int index)
{
    int *item = &heap->array[index];
    int aux;
    index = min_child_index(*heap, index);
    while ((index != -1) && (*item > heap->array[index]))
    {
        swap(int, *item, heap->array[index]);
        item = &heap->array[index];
        index = min_child_index(*heap, index); // update index
    }
}

void remove_index(MinHeap *heap, unsigned int index)
{
    int *item = &heap->array[index];
    int aux;
    index = min_child_index(*heap, index);
    while ((index != -1)) // bubbling down
    {
        swap(int, *item, heap->array[index]);
        item = &heap->array[index];
        index = min_child_index(*heap, index); // update index
    }
    *item = 0;
    swap(int, *item, heap->array[heap->top]);
    heap->top--;
    bubble_up(heap, item - heap->array);
}

MinHeap *heapify(int v[], int N)
{
    MinHeap *heap = malloc(sizeof(MinHeap));
    heap->top = 0;
    for (int i = 0; i < N; i++)
    {
        heap->array[heap->top] = v[i];
        bubble_up(heap, i);
        heap->top++;
    }
    heap->top = N - 1;
    return heap;
}
void k_largest(int v[], int N, int out[], int k)
{
    int i =0;
    for (i = 0; i < k;i++)
        out[i] = v[i];
    MinHeap *heap = heapify(out,k);
    for(;i<N;i++){
        if (v[i] > heap->array[0]){
            heap->array[0] = v[i];
            bubble_down(heap,0);
            }
    }
    print_heap(*heap);
}

int main(void)
{
    int arr[] = {10, 30, 11, 16, 22, 35, 20, 21, 19};
    int out[3];
    k_largest(arr,8,out, 3);
}
