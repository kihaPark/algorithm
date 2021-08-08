#include <iostream>


// tested x64, c++17

using namespace std;

void TestSelectionSort()
{
    const int size = 10;
    int data[size] = { 7, 5, 9, 0, 3, 1, 6, 2, 4, 8 };

    for (int i = 0; i < size; ++i) {
        int min_id = i;

        for (int j = i + 1; j < size; ++j) {
            if (data[min_id] <= data[j]) // ascend
                continue;

            min_id = j;
        }

        swap(data[i], data[min_id]);
    }

    cout << "selection sort: ";
    for (int i = 0; i < size; ++i) {
        cout << data[i] << ' ';
    }
}


void TestInsertionSort()
{
    const int size = 10;
    int data[size] = { 7, 5, 9, 0, 3, 1, 6, 2, 4, 8 };

    for (int i = 1; i < size; ++i) {
        for (int j = i; j > 0; --j) {
            if (data[j - 1] < data[j]) // ascend
                break;

            swap(data[j - 1], data[j]);
        }
    }

    cout << endl << "insertion sort: ";
    for (int i = 0; i < size; ++i) {
        cout << data[i] << ' ';
    }
}


void QuickSort1(int* data, int begin, int end)
{
    // right pivot process
    if (begin >= end)
        return;

    int i = begin, j = begin;
    int& pivot = data[end];

    for (; j < end; ++j) {
        if (data[j] < pivot)
            swap(data[i++], data[j]);
    }
    swap(data[i], pivot);

    QuickSort1(data, begin, i - 1);
    QuickSort1(data, i + 1, end);

    // left pivot process
    /*int i = end, j = end;
    int& pivot = data[begin];

    for (; j > begin; --j) {
        if (data[j] > pivot)
            swap(data[i--], data[j]);
    }
    swap(data[i], pivot);

    QuickSort1(data, begin, i - 1);
    QuickSort1(data, i + 1, end);*/
}

void QuickSort2(int* data, int begin, int end)
{
    // left pivot process
    if (begin >= end)
        return;

    int left = begin + 1;
    int right = end;
    int& pivot = data[begin];

    while (left <= right) {
        while (left <= end && data[left] <= pivot)
            left++;

        while (right > begin && data[right] >= pivot)
            right--;

        if (left <= right)
            swap(data[left], data[right]);
    }
    swap(pivot, data[right]);

    QuickSort2(data, begin, right - 1);
    QuickSort2(data, right + 1, end);
}

void TestQuickSort()
{
    const int size = 10;
    int data[size] = { 7, 5, 9, 0, 3, 1, 6, 2, 4, 8 };

    QuickSort1(data, 0, size - 1);
    //QuickSort2(data, 0, size - 1);

    cout << endl << "quick sort: ";
    for (int i = 0; i < size; ++i) {
        cout << data[i] << ' ';
    }
}


void TestCountingSort()
{
    const int size = 15;
    int data[size] = { 7, 5, 9, 0, 3, 1, 6, 2, 9, 1, 4, 8, 0, 5, 2 };
    int sort[size] = { 0, };

    const int max_value = 9;
    int counting[max_value + 1] = {0, };

    for (int i = 0; i < size; ++i)
        counting[data[i]] += 1;

    // 굳이 누적시켜서 처리할 필요가 있을까?
    for (int i = 1; i <= max_value; ++i)
        counting[i] += counting[i - 1];

    for (int i = size - 1; i >= 0; --i) {
        sort[counting[data[i]] - 1] = data[i];
        counting[data[i]] -= 1;
    }

    cout << endl << "counting sort: ";
    for (int i = 0; i < size; ++i)
        cout << sort[i] << ' ';
}


int main()
{
    TestSelectionSort();
    TestInsertionSort();
    TestQuickSort();
    TestCountingSort();

    return 0;
}

