#include <stdio.h>

void insertionSort(int arr[], int size) {

    int i, key, j;
    for( i = 1 ; i < size; i ++){
        key = arr[i];
        j = i - 1;

        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }

}

int main() {
    int arr[] = {72, 42, 10, 5, 24, 123, 2, 3, 13};
    int size = sizeof(arr) / sizeof(int);
    
    printf("Before Sort: \n");
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }

    insertionSort(arr, size);

    printf("\n\nAfter Sort: \n");
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }

    return 0;
}