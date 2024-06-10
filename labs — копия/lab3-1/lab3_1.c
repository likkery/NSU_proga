#include <stdio.h>


void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


int partition(int mas[], int low, int high) {
    int pivot = mas[high], lowInd = (low - 1);

    for (int j = low; j < high; j++) 
        if (mas[j] < pivot) {
            lowInd++;
            swap(&mas[lowInd], &mas[j]);
        }
    
    swap(&mas[lowInd + 1], &mas[high]);

    return (lowInd + 1);
}


void quickSort(int mas[], int low, int high) {
    if (low < high) {
        int partInd = partition(mas, low, high);

        quickSort(mas, low, partInd - 1);
        quickSort(mas, partInd + 1, high);
    }
}


int main() {
    int masLen;

    scanf_s("%d", &masLen);

    int mas[masLen];

    for (int i = 0; i < masLen; i++)
        scanf_s("%d", mas + i);

    quickSort(mas, 0, masLen - 1);

    for (int i = 0; i < masLen; i++)
        printf("%d ", mas[i]);

    return 0;
}