#include "pch.h"
#include "CppUnitTest.h"
#include "../Pr7.3.rec/Source.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest73rec
{
    // Тестування функції CountRowsWithoutZeros
    TEST_CLASS(UnitTest73rec)
    {
    public:

        int CountRowsWithoutZeros(int** a, const int rowCount, const int colCount, int rowNo);
        void CountFrequencies(int** a, const int rowCount, const int colCount, std::unordered_map<int, int>& frequency, int rowNo = 0, int colNo = 0);
        void FindMaxRepeating(const std::unordered_map<int, int>& frequency, std::unordered_map<int, int>::const_iterator it, int& maxVal);
        int GetMaxRepeatingValue(int** a, const int rowCount, const int colCount);

        TEST_METHOD(Test_CountRowsWithoutZeros_NoZeros)
        {
            int rowCount = 2, colCount = 2;
            int** a = new int* [rowCount];
            a[0] = new int[colCount] { 1, 2 };
            a[1] = new int[colCount] { 3, 4 };

            int count = CountRowsWithoutZeros(a, rowCount, colCount, 0);
            Assert::AreEqual(2, count);

            for (int i = 0; i < rowCount; i++)
                delete[] a[i];
            delete[] a;
        }

        TEST_METHOD(Test_CountRowsWithoutZeros_WithZeros)
        {
            int rowCount = 2, colCount = 2;
            int** a = new int* [rowCount];
            a[0] = new int[colCount] { 1, 0 };
            a[1] = new int[colCount] { 3, 4 };

            int count = CountRowsWithoutZeros(a, rowCount, colCount, 0);
            Assert::AreEqual(1, count);

            for (int i = 0; i < rowCount; i++)
                delete[] a[i];
            delete[] a;
        }

        TEST_METHOD(Test_MaxRepeating)
        {
            int rowCount = 3, colCount = 3;
            int** a = new int* [rowCount];
            a[0] = new int[colCount] { 1, 2, 2 };
            a[1] = new int[colCount] { 3, 4, 4 };
            a[2] = new int[colCount] { 5, 4, 6 };

            int maxRepeating = GetMaxRepeatingValue(a, rowCount, colCount);
            Assert::AreEqual(4, maxRepeating);

            for (int i = 0; i < rowCount; i++)
                delete[] a[i];
            delete[] a;
        }
    };

    // Реалізація функції CountRowsWithoutZeros для тестування
    int UnitTest73rec::CountRowsWithoutZeros(int** a, const int rowCount, const int colCount, int rowNo) {
        if (rowNo >= rowCount)
            return 0;
        bool hasZero = false;
        for (int colNo = 0; colNo < colCount; colNo++) {
            if (a[rowNo][colNo] == 0) {
                hasZero = true;
                break;
            }
        }
        return (!hasZero ? 1 : 0) + CountRowsWithoutZeros(a, rowCount, colCount, rowNo + 1);
    }

    // Реалізація функції CountFrequencies для тестування
    void UnitTest73rec::CountFrequencies(int** a, const int rowCount, const int colCount, std::unordered_map<int, int>& frequency, int rowNo, int colNo) {
        frequency[a[rowNo][colNo]]++;
        if (colNo < colCount - 1)
            CountFrequencies(a, rowCount, colCount, frequency, rowNo, colNo + 1);
        else if (rowNo < rowCount - 1)
            CountFrequencies(a, rowCount, colCount, frequency, rowNo + 1, 0);
    }

    // Реалізація функції FindMaxRepeating для тестування
    void UnitTest73rec::FindMaxRepeating(const std::unordered_map<int, int>& frequency, std::unordered_map<int, int>::const_iterator it, int& maxVal) {
        if (it == frequency.end())
            return;
        if (it->second > 1 && it->first > maxVal)
            maxVal = it->first;
        FindMaxRepeating(frequency, ++it, maxVal);
    }

    // Допоміжна функція для отримання максимального повторюваного значення
    int UnitTest73rec::GetMaxRepeatingValue(int** a, const int rowCount, const int colCount) {
        std::unordered_map<int, int> frequency;
        CountFrequencies(a, rowCount, colCount, frequency);
        int maxVal = INT_MIN;
        FindMaxRepeating(frequency, frequency.begin(), maxVal);
        return (maxVal == INT_MIN ? -1 : maxVal);  // Повертає -1, якщо повторюваних елементів немає
    }
}
