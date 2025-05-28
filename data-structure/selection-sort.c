#include <stdio.h>
#include <stdlib.h>

void SelectionSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int min_idx = i;

        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }

        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

int main()
{

    int arr[] = {72, 42, 10, 5, 24, 123, 2, 3, 13};
    int size = sizeof(arr) / sizeof(int);

    printf("Before sort: \n");
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }

    SelectionSort(arr, size);

    printf("\n\nAfter sort: \n");
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }

    return 0;
}