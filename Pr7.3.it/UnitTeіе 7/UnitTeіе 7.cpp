#include "pch.h"
#include "CppUnitTest.h"
#include "../Pr7.3.it/Source.cpp"
#include <iostream>
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTeст7
{
    TEST_CLASS(UnitTest7)
    {
    public:

        TEST_METHOD(TestPart1_Count_NoZeroRows)
        {
            const int rowCount = 3;
            const int colCount = 3;
            int** a = new int* [rowCount];
            for (int i = 0; i < rowCount; i++)
                a[i] = new int[colCount];

            a[0][0] = 1; a[0][1] = 2; a[0][2] = 3;
            a[1][0] = 4; a[1][1] = 5; a[1][2] = 6;
            a[2][0] = 7; a[2][1] = 8; a[2][2] = 9;

            // виклик функції
            int result = Part1_Count(a, rowCount, colCount);

            Assert::AreEqual(result, 3); // усі рядки без нулів

            for (int i = 0; i < rowCount; i++)
                delete[] a[i];
            delete[] a;
        }

        TEST_METHOD(TestPart1_Count_WithZeroRow)
        {
            const int rowCount = 3;
            const int colCount = 3;
            int** a = new int* [rowCount];
            for (int i = 0; i < rowCount; i++)
                a[i] = new int[colCount];

            a[0][0] = 1; a[0][1] = 2; a[0][2] = 3;
            a[1][0] = 0; a[1][1] = 0; a[1][2] = 0; 
            a[2][0] = 7; a[2][1] = 8; a[2][2] = 9;

            // виклик функції
            int result = Part1_Count(a, rowCount, colCount);

            // перевірка очікуваного результату
            Assert::AreEqual(result, 2); // тільки два рядки без нулів

            for (int i = 0; i < rowCount; i++)
                delete[] a[i];
            delete[] a;
        }

        TEST_METHOD(TestPart2_MaxRepeating)
        {
            const int rowCount = 3;
            const int colCount = 3;
            int** a = new int* [rowCount];
            for (int i = 0; i < rowCount; i++)
                a[i] = new int[colCount];

            a[0][0] = 1; a[0][1] = 2; a[0][2] = 3;
            a[1][0] = 2; a[1][1] = 5; a[1][2] = 6;
            a[2][0] = 7; a[2][1] = 8; a[2][2] = 9;

            std::stringstream output;

            std::streambuf* orig_buf = std::cout.rdbuf(output.rdbuf());

            Part2_MaxRepeating(a, rowCount, colCount);

            std::cout.rdbuf(orig_buf);

            std::string result = output.str();
            Assert::IsTrue(result.find("The maximum number that occurs more than once: 2") != std::string::npos);

            for (int i = 0; i < rowCount; i++)
                delete[] a[i];
            delete[] a;
        }

        TEST_METHOD(TestPart2_MaxRepeating_None)
        {
            const int rowCount = 3;
            const int colCount = 3;
            int** a = new int* [rowCount];
            for (int i = 0; i < rowCount; i++)
                a[i] = new int[colCount];

            a[0][0] = 1; a[0][1] = 2; a[0][2] = 3;
            a[1][0] = 4; a[1][1] = 5; a[1][2] = 6;
            a[2][0] = 7; a[2][1] = 8; a[2][2] = 9;

            std::stringstream output;

            std::streambuf* orig_buf = std::cout.rdbuf(output.rdbuf());

            Part2_MaxRepeating(a, rowCount, colCount);

            std::cout.rdbuf(orig_buf);

            std::string result = output.str();
            Assert::IsTrue(result.find("No numbers occur more than once.") != std::string::npos);

            
            for (int i = 0; i < rowCount; i++)
                delete[] a[i];
            delete[] a;
        }
    };
}
