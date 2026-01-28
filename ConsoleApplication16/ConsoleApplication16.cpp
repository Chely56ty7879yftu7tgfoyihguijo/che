#include <iostream>
#include <fstream>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(NULL));
  
    int a;
    ifstream fin("size.txt");       // связываем объект с файлом
fin >>a; // запись строки в файл
fin.close(); // закрываем файл

    int** dir;

    dir = new int* [a];

    for (int i = 0; i < a; ++i) {
        dir[i] = new int[a];
    }
    for (int i = 0; i < a; i++) {
        for (int y = 0; y < a; y++) {
            dir[i][y] = (rand() % 100);
        }
    }

    cout << "Исходная матрица:\n";
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++) {
            cout << dir[i][j] << "\t";
        }
        cout << "\n";
    }

    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1 - Сумма элементов главной диагонали\n";
        cout << "2 - Поменять местами макс элементы выше и ниже главной диагонали\n";
        cout << "3 - Из элементов столбцов после минимального вычесть минимальный элемент\n";
        cout << "0 - Выход\n";
        cout << "Выбор: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int sum = 0;
            for (int i = 0; i < a; i++) {
                sum += dir[i][i];
            }
            cout << "Сумма главной диагонали: " << sum << "\n";
            break;
        }
        case 2: {
            int max_above = dir[0][1];
            pair<int, int> pos_above = { 0,1 };
            int max_below = dir[1][0];
            pair<int, int> pos_below = { 1,0 };

            // Поиск max выше
            for (int i = 0; i < a; i++) {
                for (int j = i + 1; j < a; j++) {
                    if (dir[i][j] > max_above) {
                        max_above = dir[i][j];
                        pos_above = { i,j };
                    }
                }
            }
            for (int i = 1; i < a; i++) {
                for (int j = 0; j < i; j++) {
                    if (dir[i][j] > max_below) {
                        max_below = dir[i][j];
                        pos_below = { i,j };
                    }
                }
            }
            swap(dir[pos_above.first][pos_above.second], dir[pos_below.first][pos_below.second]);
            cout << "Макс элементы выше и ниже диагонали поменяны местами.\n";
            cout << "Матрица после операции 2:\n";
            for (int i = 0; i < a; i++) {
                for (int j = 0; j < a; j++) {
                    cout << dir[i][j] << "\t";
                }
                cout << "\n";
            }
            break;
        }
        case 3: {
            int min_val = dir[0][0];
            int min_col = 0;
            for (int i = 0; i < a; i++) {
                for (int j = 0; j < a; j++) {
                    if (dir[i][j] < min_val) {
                        min_val = dir[i][j];
                        min_col = j;
                    }
                }
            }
            cout << "Минимальный элемент: " << min_val << " в столбце " << min_col << "\n";

            for (int j = min_col + 1; j < a; j++) {
                for (int i = 0; i < a; i++) {
                    dir[i][j] -= min_val;
                }
            }
            cout << "Операция 3 выполнена.\n";
            cout << "Матрица после операции 3:\n";
            for (int i = 0; i < a; i++) {
                for (int j = 0; j < a; j++) {
                    cout << dir[i][j] << "\t";
                }
                cout << "\n";
            }
            break;
        }
        case 0:
            cout << "Выход.\n";
            break;
        default:
            cout << "Неверный выбор!\n";
        }
    } while (choice != 0);


}
