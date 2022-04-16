#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 100
int array[MAX_NUM];
size_t array_size = 0;

typedef struct {
    size_t low;
    size_t high;
} parameters;

int cmp(const void  *a, const void *b) {
    return *((int *)a) - *((int *)b);
}

void *runner(void *param) {
    size_t low, high;
    low = ((parameters *)param)->low;
    high = ((parameters *)param)->high;
    // printf("Low: %lu, high: %lu\n", low, high);
    qsort(array + low, high - low, sizeof(int), cmp);
    pthread_exit(0);
}    //Do the sort function



void init_array() {
    printf("Please enter the number of elements:");
    scanf("%ld", &array_size);
    for(size_t i = 0; i != array_size; ++i) {
        scanf("%d", &array[i]);
    }
}      //input the data and store in array

void merge_array(int *result) {
    size_t low1 = 0, high1 = array_size / 2;
    size_t low2 = array_size / 2, high2 = array_size;
    size_t i = 0;
    while(low1 < high1 && low2 < high2) {
        if(array[low1] < array[low2]) {
            result[i++] = array[low1++];
        } else {
            result[i++] = array[low2++];
        }
    }
    if(low2 < high2) {
        low1 = low2;
        high1 = high2;
    }
    while(low1 < high1) {
        result[i++] = array[low1++];
    }
}

void print_array(int *arr, size_t size) {
    for(size_t i = 0; i != size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    pthread_t tid[2];
    pthread_attr_t attr; //set the threads
    init_array();
    printf("Original array:\n");
    print_array(array, array_size);
    parameters data[2];
    data[0].low = 0;
    data[0].high = array_size / 2;
    data[1].low = array_size / 2;
    data[1].high = array_size;
    pthread_attr_init(&attr);
    // create two threads to sort the two halves of the array 
    for(size_t i = 0; i != 2; ++i) {
        pthread_create(&tid[i], &attr, runner, &data[i]);
    }
    // wait for the thread to exit */
    for(size_t i = 0; i != 2; ++i) {
        pthread_join(tid[i], NULL);
    }
    printf("Thread 0:\n");
    print_array(array, array_size / 2);
    printf("Thread 1:\n");
    print_array(array + array_size / 2, array_size - array_size / 2);
    int *sorted_array = malloc(sizeof(int) * array_size);
    merge_array(sorted_array);
    printf("After merging:\n");
    print_array(sorted_array, array_size);
    return 0;
}
