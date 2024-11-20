#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <string>
#include <cmath>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Прототип тестованої функції
void ProcessFile(const std::string& inputFilename, const std::string& outputFilename);

void ProcessFile(const std::string& inputFilename, const std::string& outputFilename) {
    std::ifstream fin(inputFilename);
    if (!fin) {
        throw std::runtime_error("Помилка відкриття вхідного файлу");
    }

    std::ofstream fout(outputFilename);
    if (!fout) {
        throw std::runtime_error("Помилка відкриття вихідного файлу");
    }

    double num;
    double maxNegative = -1e9;
    double minPositive = 1e9;
    bool foundNegative = false, foundPositive = false;

    while (fin >> num) {
        if (num < 0 && num > maxNegative) {
            maxNegative = num;
            foundNegative = true;
        }
        if (num > 0 && num < minPositive) {
            minPositive = num;
            foundPositive = true;
        }
    }

    if (foundNegative) {
        fout << "MaxNegative: " << maxNegative << std::endl;
    }
    else {
        fout << "MaxNegative: None" << std::endl;
    }

    if (foundPositive) {
        fout << "MinPositive: " << minPositive << std::endl;
    }
    else {
        fout << "MinPositive: None" << std::endl;
    }

    fin.close();
    fout.close();
}

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestProcessFile)
        {
            // Створення тестового вхідного файлу
            const std::string inputFile = "test_input.txt";
            const std::string outputFile = "test_output.txt";
            std::ofstream fout(inputFile);
            fout << "-10\n5\n-3\n0\n2.5\n-0.5\n";
            fout.close();

            // Виклик функції
            ProcessFile(inputFile, outputFile);

            // Перевірка результатів
            std::ifstream fin(outputFile);
            std::string line;

            std::getline(fin, line);
            Assert::AreEqual(std::string("MaxNegative: -0.5"), line, L"Неправильне значення найбільшого від'ємного числа");

            std::getline(fin, line);
            Assert::AreEqual(std::string("MinPositive: 2.5"), line, L"Неправильне значення найменшого додатного числа");

            fin.close();

            // Очистка тестових файлів
            std::remove(inputFile.c_str());
            std::remove(outputFile.c_str());
        }
    };
}