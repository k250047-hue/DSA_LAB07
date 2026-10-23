
#include <iostream>
#include <vector>
using namespace std;

int bitCount(int num)
{
    int total = 0;

    while (num > 0)
    {
        if (num % 2 == 1)
            total++;

        num /= 2;
    }

    return total;
}

string binaryValue(int num, int width)
{
    string bin = "";

    for (int i = 0; i < width; i++)
    {
        bin = char('0' + num % 2) + bin;
        num /= 2;
    }

    return bin;
}

void printArrays(vector<int>& data, int width)
{
    cout << "Decimal: ";
    for (int i = 0; i < data.size(); i++)
        cout << data[i] << " ";

    cout << "\nBinary:  ";
    for (int i = 0; i < data.size(); i++)
        cout << binaryValue(data[i], width) << " ";

    cout << endl;
}

void radixSort(vector<int>& data, int width)
{
    int total = data.size();
    vector<int> temp(total);

    for (int bit = 0; bit < width; bit++)
    {
        int zeroCount = 0, oneCount = 0;

        for (int i = 0; i < total; i++)
        {
            if ((data[i] >> bit) & 1)
                oneCount++;
            else
                zeroCount++;
        }

        int index = 0;

        for (int i = 0; i < total; i++)
        {
            if (((data[i] >> bit) & 1) == 0)
                temp[index++] = data[i];
        }

        for (int i = 0; i < total; i++)
        {
            if ((data[i] >> bit) & 1)
                temp[index++] = data[i];
        }

        for (int i = 0; i < total; i++)
            data[i] = temp[i];

        cout << "\n====================================\n";
        cout << "Pass " << bit + 1 << " - Bit Position " << bit;

        if (bit == 0)
            cout << " (LSB)";
        else if (bit == width - 1)
            cout << " (MSB)";

        cout << "\n====================================\n";
        cout << "Zeros: " << zeroCount << endl;
        cout << "Ones: " << oneCount << endl;

        printArrays(data, width);
    }
}

int main()
{
    int size;

    cout << "Enter the number of elements (at least 10): ";
    cin >> size;

    if (size < 10)
    {
        cout << "Please enter at least 10 elements." << endl;
        return 0;
    }

    vector<int> data(size);
    int maxValue = 0;

    cout << "Enter decimal integers:\n";

    for (int i = 0; i < size; i++)
    {
        cin >> data[i];

        if (data[i] < 0)
        {
            cout << "Please enter non-negative integers." << endl;
            return 0;
        }

        if (data[i] > maxValue)
            maxValue = data[i];
    }

    int width = 1;
    int tempValue = maxValue;

    while (tempValue >= 2)
    {
        width++;
        tempValue /= 2;
    }

    cout << "\nBinary Representations:\n";

    for (int i = 0; i < size; i++)
        cout << data[i] << " = " << binaryValue(data[i], width) << endl;

    radixSort(data, width);

    cout << "\n====================================\n";
    cout << "Final Sorted Array\n";
    cout << "====================================\n";
    printArrays(data, width);

    cout << "\n====================================\n";
    cout << "Additional Analysis\n";
    cout << "====================================\n";

    cout << "Longest Binary Representation:\n";
    cout << maxValue << " = " << binaryValue(maxValue, width) << endl;
    cout << "Length = " << width << " bits\n";

    int maxBits = bitCount(maxValue);
    int sameCount = 0;

    cout << "\nLargest Input Value:\n";
    cout << maxValue << " = " << binaryValue(maxValue, width) << endl;
    cout << "Number of set bits (1s): " << maxBits << endl;

    cout << "\nNumbers with the same number of set bits:\n";

    for (int i = 0; i < size; i++)
    {
        if (bitCount(data[i]) == maxBits)
        {
            cout << data[i] << " ";
            sameCount++;
        }
    }

    cout << "\nCount: " << sameCount << endl;

    return 0;
}