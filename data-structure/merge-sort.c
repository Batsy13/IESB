#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArray[n1], rightArray[n2];

    for(i = 0; i < n1; i++){
        leftArray[i] = arr[left + i];
    }
    for(j = 0; j < n2; j++){
        rightArray[j] = arr[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;

    while(i < n1 && j < n2){
        if(leftArray[i] <= rightArray[j]){
            arr[k] = leftArray[i];
            i++;
        }
        else {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    while(j < n2){
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right){
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main() {
    
    int arr[] = {72, 42, 10, 5, 24, 123, 2, 3, 13};
    int size = sizeof(arr) / sizeof(int);

    printf("Before MergeSort: ");

    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }

    mergeSort(arr, 0, size - 1);

    printf("\nAfter MergeSort: ");

    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }

    return 0;
}