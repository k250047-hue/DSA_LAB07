
#include <iostream>
#include <vector>
using namespace std;

int digitSum(int num)
{
    int sum = 0;

    while (num > 0)
    {
        sum += num % 10;
        num /= 10;
    }

    return sum;
}

void showArray(vector<int>& ids)
{
    for (int i = 0; i < ids.size(); i++)
        cout << ids[i] << " ";

    cout << endl;
}

void radixSort(vector<int>& ids)
{
    int size = ids.size();
    vector<int> temp(size);
    int place = 1;

    for (int pass = 1; pass <= 4; pass++)
    {
        int count[10] = {0};

        for (int i = 0; i < size; i++)
        {
            int digit = (ids[i] / place) % 10;
            count[digit]++;
        }

        int evenCount = 0;

        for (int i = 0; i < size; i++)
        {
            int digit = (ids[i] / place) % 10;
            if (digit % 2 == 0)
                evenCount++;
        }

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (int i = size - 1; i >= 0; i--)
        {
            int digit = (ids[i] / place) % 10;
            temp[count[digit] - 1] = ids[i];
            count[digit]--;
        }

        for (int i = 0; i < size; i++)
            ids[i] = temp[i];

        cout << "\nAfter ";
        if (pass == 1)
            cout << "units";
        else if (pass == 2)
            cout << "tens";
        else if (pass == 3)
            cout << "hundreds";
        else
            cout << "thousands";

        cout << " pass: ";
        showArray(ids);

        cout << "IDs with even digit at this position: "
             << evenCount << endl;

        place *= 10;
    }
}

int main()
{
    int size;

    cout << "Enter number of students (at least 20): ";
    cin >> size;

    if (size < 20)
    {
        cout << "Please enter at least 20 students." << endl;
        return 0;
    }

    vector<int> ids(size);

    cout << "Enter the last four digits of student IDs: ";
    for (int i = 0; i < size; i++)
    {
        cin >> ids[i];

        if (ids[i] < 0 || ids[i] > 9999)
        {
            cout << "Enter IDs between 0 and 9999." << endl;
            return 0;
        }
    }

    radixSort(ids);

    cout << "\nSorted IDs: ";
    showArray(ids);

    cout << "\nDuplicate IDs and their frequencies:\n";
    bool found = false;

    for (int i = 0; i < size; )
    {
        int j = i + 1;

        while (j < size && ids[j] == ids[i])
            j++;

        if (j - i > 1)
        {
            cout << ids[i] << " occurs " << j - i
                 << " times" << endl;
            found = true;
        }

        i = j;
    }

    if (!found)
        cout << "No duplicate IDs found." << endl;

    int highestSum = -1;
    int highestID = ids[0];

    cout << "\nDigit sums:\n";

    for (int i = 0; i < size; i++)
    {
        int sum = digitSum(ids[i]);

        cout << ids[i] << " = " << sum << endl;

        if (sum > highestSum)
        {
            highestSum = sum;
            highestID = ids[i];
        }
    }

    cout << "ID with highest digit sum: " << highestID
         << " (sum = " << highestSum << ")" << endl;

    int bestStart = -1;
    int bestLength = 0;
    int currentStart = 0;
    int currentLength = 0;

    for (int i = 0; i < size; i++)
    {
        if (digitSum(ids[i]) % 2 == 0)
        {
            if (currentLength == 0)
                currentStart = i;

            currentLength++;

            if (currentLength > bestLength)
            {
                bestLength = currentLength;
                bestStart = currentStart;
            }
        }
        else
        {
            currentLength = 0;
        }
    }

    cout << "\nLongest sequence with even digit sums: ";

    if (bestLength == 0)
    {
        cout << "No such IDs";
    }
    else
    {
        for (int i = bestStart; i < bestStart + bestLength; i++)
            cout << ids[i] << " ";

        cout << "\nSequence length: " << bestLength;
    }

    cout << endl;
    return 0;
}