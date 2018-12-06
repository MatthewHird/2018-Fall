#include <iostream>


void swap(float* a, float* b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}


int partition(float* fArray, int startIndex, int endIndex) {
    int pivot = fArray[endIndex];
    int index = startIndex;

    for (int i = startIndex; i < endIndex; ++i) {
        if (fArray[i] <= pivot) {
            swap(&fArray[index], &fArray[i]);
            index++;
        }
    }
    swap(&fArray[index], &fArray[endIndex]);
    return index;
}


void quicksort(float* fArray, int startIndex, int endIndex) {
    if (startIndex < endIndex) {
        int index = partition(fArray, startIndex, endIndex);

        quicksort(fArray, startIndex, index - 1);
        quicksort(fArray, index + 1, endIndex);
    }
}


int main() {
    float fArray[] = {3.6, 1, 75, 18.888, 12e5, 1111, 45.335};
    int size = sizeof(fArray)/sizeof(fArray[0]);

    quicksort(fArray, 0, size - 1);

    for (int i = 0; i < size; ++i)
    {
        std::cout << std::to_string(fArray[i]) << "\n";
    }
    
    return 0;
}