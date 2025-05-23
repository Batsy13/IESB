#include <stdio.h>

void bubbleSort(int arr[], int total)
{
    int i, j, temp;
    int swapped;

    for (i = 0; i < total - 1; i++)
    {
        swapped = 0;

        for (j = 0; j < total - i - 1; j++)
        {

            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }

        }
        if (swapped == 0)
        {
            break;
        }
    }
}

int main()
{
    int arr[] = {72, 42, 10, 5, 24, 123, 2, 3, 13};
    int n = sizeof(arr) / sizeof(int);

    printf("Before sort: \n");
    for(int i = 0; i < n ; i++){
        printf("%d ", arr[i]);
    }
    
    printf("\n-------------------------\n");
    
    bubbleSort(arr, n);
    
    printf("After sort: \n");
    for(int i = 0; i < n ; i++){
        printf("%d ", arr[i]);
    }


    return 0;
}