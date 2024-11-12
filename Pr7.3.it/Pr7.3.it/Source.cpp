#include <iostream>
#include <iomanip>
#include <time.h>
#include <unordered_map>
using namespace std;

void Create(int** a, const int rowCount, const int colCount, const int Low,
    const int High);
void Input(int** a, const int rowCount, const int colCount);
void Print(int** a, const int rowCount, const int colCount);
int Part1_Count(int** a, const int rowCount, const int colCount);
void Part2_MaxRepeating(int** a, const int rowCount, const int colCount);
bool IsMaxInRowN(int** a, const int n, const int k, const int colCount);
bool IsMinInColK(int** a, const int n, const int k, const int rowCount);

int main() {
    srand((unsigned)time(NULL));
    int Low = -17;
    int High = 15;
    int rowCount, colCount;
    cout << "rowCount = "; cin >> rowCount;
    cout << "colCount = "; cin >> colCount;
    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    Input(a, rowCount, colCount);
    Print(a, rowCount, colCount);

    // Підрахунок кількості рядків без нулів
    int count = Part1_Count(a, rowCount, colCount);
    cout << "The number of rows that do not contain any null elements: " << count << endl;

    // Пошук максимального елемента, що повторюється більше одного разу
    Part2_MaxRepeating(a, rowCount, colCount);

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

void Create(int** a, const int rowCount, const int colCount, const int Low,
    const int High) {
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            a[i][j] = Low + rand() % (High - Low + 1);
}

void Input(int** a, const int rowCount, const int colCount) {
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            cout << "a[" << i << "][" << j << "] = ";
            cin >> a[i][j];
        }
        cout << endl;
    }
}

void Print(int** a, const int rowCount, const int colCount) {
    cout << endl;
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++)
            cout << setw(4) << a[i][j];
        cout << endl;
    }
    cout << endl;
}

// Підрахунок кількості рядків без нулів
int Part1_Count(int** a, const int rowCount, const int colCount) {
    int count = 0;

    for (int i = 0; i < rowCount; i++) {
        bool hasZero = false;
        for (int j = 0; j < colCount; j++) {
            if (a[i][j] == 0) {
                hasZero = true;
                break;
            }
        }
        if (!hasZero) {
            count++;
        }
    }

    return count;
}

// Пошук максимального елемента, що повторюється більше одного разу
void Part2_MaxRepeating(int** a, const int rowCount, const int colCount) {
    unordered_map<int, int> frequency;

    // Підрахунок кількості повторів для кожного числа
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            frequency[a[i][j]]++;
        }
    }

    int maxVal = -1;
    bool found = false;
    // максимальне значення, яке повторюється більше одного разу
    for (const auto& elem : frequency) {
        if (elem.second > 1 && elem.first > maxVal) {
            maxVal = elem.first;
            found = true;
        }
    }

    if (found) {
        cout << "The maximum number that occurs more than once: " << maxVal << endl;
    }
    else {
        cout << "No numbers occur more than once." << endl;
    }
}

bool IsMaxInRowN(int** a, const int n, const int k, const int colCount) {
    for (int j = 0; j < colCount; j++)
        if (a[n][j] > a[n][k]) {
            return false;
        }
    return true;
}

bool IsMinInColK(int** a, const int n, const int k, const int rowCount) {
    for (int i = 0; i < rowCount; i++)
        if (a[i][k] < a[n][k]) {
            return false;
        }
    return true;
}

