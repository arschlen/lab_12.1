#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Функція створення файлу даних з числами
void CreateFile(const string& filename) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "Pomilka vidkrittya faylu dlya zapisu!" << endl;
        return;
    }

    char choice;
    do {
        double num;
        cout << "Vvedit chyslo: ";
        cin >> num;
        fout << num << endl;

        cout << "Prodovzhyty vvedennya? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    fout.close();
}

// Функція перегляду вмісту файлу
void ViewFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Pomilka vidkrittya faylu dlya chytannya!" << endl;
        return;
    }

    string line;
    cout << "Vmist faylu: " << endl;
    while (getline(fin, line)) {
        cout << line << endl;
    }

    fin.close();
}

// Функція пошуку найбільшої від'ємної і найменшої додатної компоненти
void ProcessFile(const string& inputFilename, const string& outputFilename) {
    ifstream fin(inputFilename);
    if (!fin) {
        cerr << "Pomilka vidkrittya vkhidnogo faylu dlya chytannya!" << endl;
        return;
    }

    ofstream fout(outputFilename);
    if (!fout) {
        cerr << "Pomilka vidkrittya vykhidnogo faylu dlya zapisu!" << endl;
        return;
    }

    double num;
    double maxNegative = -1e9;  // Початково велике від'ємне значення
    double minPositive = 1e9;   // Початково велике додатне значення
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
        fout << "MaxNegative: " << maxNegative << endl;
    }
    else {
        fout << "MaxNegative: None" << endl;
    }

    if (foundPositive) {
        fout << "MinPositive: " << minPositive << endl;
    }
    else {
        fout << "MinPositive: None" << endl;
    }

    fin.close();
    fout.close();
}

// Функція перегляду обробленого файлу
void ViewProcessedFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Pomilka vidkrittya faylu dlya chytannya!" << endl;
        return;
    }

    string line;
    cout << "Obroblenyy fayl mistyt: " << endl;
    while (getline(fin, line)) {
        cout << line << endl;
    }

    fin.close();
}

// Меню програми
void Menu() {
    string inputFilename, outputFilename;
    cout << "Vvedit imya vkhidnogo faylu: ";
    cin >> inputFilename;

    int choice;
    do {
        cout << "\nMenyu:\n"
            << "1. Stvoryty fayl\n"
            << "2. Perehlyanuty fayl\n"
            << "3. Obrobyty fayl\n"
            << "4. Perehlyanuty obroblenyy fayl\n"
            << "0. Vykhid\n"
            << "Vash vybir: ";
        cin >> choice;

        switch (choice) {
        case 1:
            CreateFile(inputFilename);
            break;
        case 2:
            ViewFile(inputFilename);
            break;
        case 3:
            cout << "Vvedit imya vykhidnogo faylu: ";
            cin >> outputFilename;
            ProcessFile(inputFilename, outputFilename);
            break;
        case 4:
            cout << "Vvedit imya vykhidnogo faylu: ";
            cin >> outputFilename;
            ViewProcessedFile(outputFilename);
            break;
        case 0:
            cout << "Do pobachennya!" << endl;
            break;
        default:
            cout << "Nekorektnyy vybir. Sprobuyte shche raz." << endl;
        }
    } while (choice != 0);
}

int main() {
    Menu();
    return 0;
}
