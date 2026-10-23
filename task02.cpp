
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int levelCounts[100] = {0};

void display(vector<int>& arr, int start, int end)
{
    cout << "[";
    for (int i = start; i <= end; i++)
    {
        cout << arr[i];
        if (i < end)
            cout << ", ";
    }
    cout << "]";
}

int partitionArray(vector<int>& arr, int start, int end)
{
    int pivot = arr[end];
    int pos = start - 1;

    for (int j = start; j < end; j++)
    {
        if (arr[j] <= pivot)
        {
            pos++;
            swap(arr[pos], arr[j]);
        }
    }

    swap(arr[pos + 1], arr[end]);
    return pos + 1;
}

void mergeArrays(vector<int>& arr, int start, int middle, int end)
{
    vector<int> leftPart(arr.begin() + start, arr.begin() + middle + 1);
    vector<int> rightPart(arr.begin() + middle + 1, arr.begin() + end + 1);

    int i = 0, j = 0, k = start;

    while (i < leftPart.size() && j < rightPart.size())
    {
        if (leftPart[i] <= rightPart[j])
            arr[k++] = leftPart[i++];
        else
            arr[k++] = rightPart[j++];
    }

    while (i < leftPart.size())
        arr[k++] = leftPart[i++];

    while (j < rightPart.size())
        arr[k++] = rightPart[j++];
}

void sortProducts(vector<int>& arr, int start, int end, int level)
{
    if (start >= end)
        return;

    cout << "\nLevel " << level << ": ";

    if (level % 2 != 0)
    {
        cout << "Quick Sort Partitioning\n";

        int pivotPos = partitionArray(arr, start, end);

        cout << "Pivot: " << arr[pivotPos] << endl;

        cout << "Left subarray: ";
        if (start < pivotPos)
        {
            display(arr, start, pivotPos - 1);
            levelCounts[level]++;
        }
        else
            cout << "[]";

        cout << "\nPivot subarray: [" << arr[pivotPos] << "]";
        levelCounts[level]++;

        cout << "\nRight subarray: ";
        if (pivotPos < end)
        {
            display(arr, pivotPos + 1, end);
            levelCounts[level]++;
        }
        else
            cout << "[]";

        cout << endl;

        sortProducts(arr, start, pivotPos - 1, level + 1);
        sortProducts(arr, pivotPos + 1, end, level + 1);
    }
    else
    {
        cout << "Merge Sort Division\n";

        int middle = start + (end - start) / 2;

        cout << "Left subarray: ";
        display(arr, start, middle);

        cout << "\nRight subarray: ";
        display(arr, middle + 1, end);
        cout << endl;

        levelCounts[level] += 2;

        sortProducts(arr, start, middle, level + 1);
        sortProducts(arr, middle + 1, end, level + 1);

        mergeArrays(arr, start, middle, end);

        cout << "Merged subarray: ";
        display(arr, start, end);
        cout << endl;
    }
}

int main()
{
    int size;

    cout << "Enter number of product IDs (at least 20): ";
    cin >> size;

    if (size < 20)
    {
        cout << "Please enter at least 20 product IDs." << endl;
        return 0;
    }

    vector<int> products(size);

    cout << "Enter product IDs: ";
    for (int i = 0; i < size; i++)
        cin >> products[i];

    sortProducts(products, 0, size - 1, 1);

    cout << "\n--- SUBARRAY COUNTS ---\n";

    for (int i = 1; i < 100; i++)
    {
        if (levelCounts[i] > 0)
            cout << "Level " << i << ": "
                 << levelCounts[i] << " subarrays generated\n";
    }

    cout << "\nFinal sorted product IDs: ";
    display(products, 0, size - 1);
    cout << endl;

    return 0;
}