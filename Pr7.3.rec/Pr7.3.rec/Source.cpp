#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <time.h>
using namespace std;

void PrintRow(int** a, const int rowNo, const int colCount, int colNo) {
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < colCount - 1)
        PrintRow(a, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

void PrintRows(int** a, const int rowCount, const int colCount, int rowNo) {
    PrintRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        PrintRows(a, rowCount, colCount, rowNo + 1);
    else
        cout << endl;
}

void InputRow(int** a, const int rowNo, const int colCount, int colNo) {
    cout << "a[" << rowNo << "][" << colNo << "] = ";
    cin >> a[rowNo][colNo];
    if (colNo < colCount - 1)
        InputRow(a, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

void InputRows(int** a, const int rowCount, const int colCount, int rowNo) {
    InputRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        InputRows(a, rowCount, colCount, rowNo + 1);
    else
        cout << endl;
}

void CreateRow(int** a, const int rowNo, const int colCount, const int Low, const int High, int colNo) {
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < colCount - 1)
        CreateRow(a, rowNo, colCount, Low, High, colNo + 1);
}

void CreateRows(int** a, const int rowCount, const int colCount, const int Low, const int High, int rowNo) {
    CreateRow(a, rowNo, colCount, Low, High, 0);
    if (rowNo < rowCount - 1)
        CreateRows(a, rowCount, colCount, Low, High, rowNo + 1);
}

// чи рядок містить нуль
bool HasZeroInRow(int** a, const int rowNo, const int colCount, int colNo) {
    if (a[rowNo][colNo] == 0)
        return true;
    if (colNo < colCount - 1)
        return HasZeroInRow(a, rowNo, colCount, colNo + 1);
    return false;
}

//підрахунок рядків, які не містять нульових елементів
int CountRowsWithoutZeros(int** a, const int rowCount, const int colCount, int rowNo) {
    if (rowNo >= rowCount)
        return 0;
    return (!HasZeroInRow(a, rowNo, colCount, 0) ? 1 : 0) + CountRowsWithoutZeros(a, rowCount, colCount, rowNo + 1);
}

// підрахунок частот значень у матриці
void CountFrequencies(int** a, const int rowCount, const int colCount, unordered_map<int, int>& frequency, int rowNo = 0, int colNo = 0) {
    frequency[a[rowNo][colNo]]++;
    if (colNo < colCount - 1)
        CountFrequencies(a, rowCount, colCount, frequency, rowNo, colNo + 1);
    else if (rowNo < rowCount - 1)
        CountFrequencies(a, rowCount, colCount, frequency, rowNo + 1, 0);
}

// максимальний
// елемента, що повторюється більше одного разу
void FindMaxRepeating(const unordered_map<int, int>& frequency, unordered_map<int, int>::const_iterator it, int& maxVal) {
    if (it == frequency.end())
        return;
    if (it->second > 1 && it->first > maxVal)
        maxVal = it->first;
    FindMaxRepeating(frequency, ++it, maxVal);
}

void MaxRepeating(int** a, const int rowCount, const int colCount) {
    unordered_map<int, int> frequency;
    CountFrequencies(a, rowCount, colCount, frequency);

    int maxVal = INT_MIN;
    FindMaxRepeating(frequency, frequency.begin(), maxVal);

    if (maxVal == INT_MIN) {
        cout << "No numbers occur more than once." << endl;
    }
    else {
        cout << "The maximum number that occurs more than once: " << maxVal << endl;
    }
}

int main() {
    srand((unsigned)time(NULL));
    int Low = -7;
    int High = 7;
    int rowCount, colCount;
    cout << "rowCount = ";
    cin >> rowCount;
    cout << "colCount = ";
    cin >> colCount;

    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    InputRows(a, rowCount, colCount, 0);
    PrintRows(a, rowCount, colCount, 0);

    //  функція для підрахунку рядків без нулів
    int count = CountRowsWithoutZeros(a, rowCount, colCount, 0);
    cout << "Number of rows without any zero elements: " << count << endl;

    // функція для пошуку максимального повторюваного числа
    MaxRepeating(a, rowCount, colCount);

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}
