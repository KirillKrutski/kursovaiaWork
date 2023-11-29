#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

int N;
int** arrayMatrix[3];
int* arrayEnd = new int[N * N * 2];
int amount;

int** matrixCreate() { // метод создания матрицы, заполнение её нулями
    int** matrix = new int* [N];
    for (int i = 0; i < N; i++) {
        matrix[i] = new int[N];
        for (int j = 0; j < N; j++) matrix[i][j] = 0;
    }
    return matrix; // возвращение значения matrix 
}

int** matrixInput() { // ввод значений матрицы пользователем
    int** matrix = matrixCreate(); // создание матрицы
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> matrix[i][j]; // ввод данных
    return matrix; // возвращение значения matrix 
}

void matrixPrint(int** matrix) { // вывод матрицы на экран пользователя(консоль)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << setw(5) << matrix[i][j] << " ";
        cout << "\n";
    }
}

void matrixChangeElements(int** a) { // метод смены значения элемента матрицы
    cout << "Enter index of row and column\n";
    int row, column, value;
    cin >> row >> column;
    while (true) {
        if (row >= N || column >= N) {
            cout << "Something wrong";
            cin >> row >> column;
        }
        else {
            break;
        }
    }
    cout << "Enter a new value\n";
    cin >> value;
    a[row][column] = value;
}

int** matrixCopy(int** a) { // метод копирования значения матрицы
    int** result = matrixCreate();
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            result[i][j] = a[i][j];
    return result;
}

int* matrixComparison() {
    amount = 0;
    int temp;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int element = arrayMatrix[0][i][j];
            for (int k = 0; k < N; k++) {
                for (int l = 0; l < N; l++) {
                    if (element == arrayMatrix[2][k][l]) arrayEnd[amount++] = element;
                }
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int element = arrayMatrix[1][i][j];
            for (int k = 0; k < N; k++) {
                for (int l = 0; l < N; l++) {
                    if (element == arrayMatrix[2][k][l]) arrayEnd[amount++] = element;
                }
            }
        }
    }
    for (int i = 0; i < amount; i++) {
        for (int j = 0; j < amount - 1; j++)
            if (arrayEnd[j] > arrayEnd[j + 1]) {
                temp = arrayEnd[j];
                arrayEnd[j] = arrayEnd[j + 1];
                arrayEnd[j + 1] = temp;
        }
    }
    cout << "End: ";
    for (int i = 0; i < amount; i++) {
        cout << arrayEnd[i] << " ";
    }
    return 0;
}


void editMatrix() {
    cout << "\nWhat matrix do u want to edit?\n" <<
        "1 - Matrix A" <<
        "\n2 - Matrix B" <<
        "\n3 - Matrix C";
    while (true) {
        int index;
        cin >> index;
        if (index == 0) break;
        matrixChangeElements(arrayMatrix[index - 1]);
    }
}

int** matrixEnter() {
    cout << "Input the first matrix A: \n"; // ввод первой матрицы
    arrayMatrix[0] = matrixInput();

    cout << "Input the second matrix B: \n"; // ввод второй матрицы
    arrayMatrix[1] = matrixInput();

    cout << "Input the third matrix C: \n"; // ввод третьей матрицы
    arrayMatrix[2] = matrixInput();
    return 0;
}

int outputInFile() {
    string file = "FileOfTheMatrices.txt"; // создание файла
    ofstream fout;
    fout.open(file);
    if (!fout.is_open()) cout << "File didn't create"; // проверка на ошибку
    else {

        fout << "\nDimension: ";
        fout << N << "\n"; // запись в файл

        fout << "Matrix A:\n"; // запись в файл
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) fout << arrayMatrix[0][i][j] << " "; // запись в файл
            fout << "\n"; // запись в файл
        }
        fout << endl; // запись в файл

        fout << "Matrix B :\n"; // запись в файл
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) fout << arrayMatrix[1][i][j] << " "; // запись в файл
            fout << "\n"; // запись в файл
        }
        fout << endl; // запись в файл

        fout << "Matrix C:\n"; // запись в файл

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) fout << arrayMatrix[2][i][j] << " "; // запись в файл
            fout << "\n"; // запись в файл
        }
        fout << endl; // запись в файл

        fout << "End: "; // запись в файл
        for (int i = 0; i < amount; i++) {
            fout << arrayEnd[i] << " ";
        }

        fout.close(); //закрытие текстового файла для предотвращения ошибок и освобождения ресурсов которыми пользовались для работы с файлом

        ifstream fin;
        fin.open(file);

        if (!fin.is_open()) //проверка открылся ли файл правильно
            cout << "\nFile did not open\n";
        else { //вывод матриц из текстового файла построчно
            cout << "\nMatrices that are in the file:\n";
            string str;
            while (!fin.eof()) {
                str = "";
                getline(fin, str);
                cout << str << endl;
            }
        }
        fin.close(); //закрытие текстового файла для предотвращения ошибок и освобождения ресурсов которыми пользовались для работы с файлом
        return 0;
    }
}

void outputMatrix() {
    cout << "The first matrix: \n";
    matrixPrint(arrayMatrix[0]);
    cout << "\nThe second matrix: \n"; // вывод второй матрицы
    matrixPrint(arrayMatrix[1]);
    cout << "\nThe third matrix: \n"; // вывод третьей матрицы
    matrixPrint(arrayMatrix[2]);
    cout << "\nDo u want to save matrices in file? (Y/n)";
    char tag;
    cin >> tag;
    if (tag == 'Y') {
        outputInFile();
    }
}

void menu() { // вывод меню на экран пользователя
    cout <<
        "\nOptions for choosing a solution to the problem:\n" <<
        "1 - Enter matrix\n" <<
        "2 - Edit matrix\n" <<
        "3 - Output matrix\n" <<
        "4 - Finding similar elements of matrices\n" <<
        "5 - Exit\n";
}

int chooseMethod() { // выбор пользователя
    menu();
    int index;
    cin >> index; // ввод индекса пользователем
    switch (index) {
    case 1: 
        matrixEnter(); break;
    case 2: 
        editMatrix(); break;
    case 3: 
        outputMatrix(); break;
    case 4: 
        matrixComparison(); break;
    case 5:
        return -1;
    }
    return 0;
}

int main() { // вызов метода меню и выбора пользователя
    cout << "\nEnter the dimension of the matrices\n"; // ввод размерности матрицы
    cin >> N;
    cout << "Welcome to matrices calculator!\n";
    while (true) {
        if (chooseMethod() == -1) break;
    }
}
