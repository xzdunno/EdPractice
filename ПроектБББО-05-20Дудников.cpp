#include <iostream>
#include<string>
#include<windows.h>
using namespace std;
string neededSize(string k, int size) {
    bool a = true;
    if (size == 10) {
        while (a) {
            if (k.length() > 9) {
                cout << "Число не может быть таким большим, введите нужное ";
                cin >> k;
                cin.ignore(INT_MAX, '\n');
            }
            else { a = false; }
        }
    }
    else {
        while (a) {
            if (k.length() !=8) {
                cout << "Пароль должен состоять из 8 цифр. Введите заново ";
                cin >> k;
                cin.ignore(INT_MAX, '\n');
            }
            else { a = false; }
        }
    }
    return k;
};
int checkInt(string m, int size) {
    int result = 0;
    bool a = true;
    m = neededSize(m,size);
    while (a) {
        int count = 0;
        for (int i = 0; i < m.length(); i++) {
            if (!((int(m[i]) <= 57) & (int(m[i]) >= 48))) {
                count++;
            }
        }
        if (count > 0) {
            cout << "Между требуемых цифр затесался символ. Введите число заново ";
            cin >> m;
            cin.ignore(INT_MAX, '\n');
            m = neededSize(m,size);
        }
        else { a = 0; }
    }
    for (int i = 0; i < m.length(); i++) {
        result += (int(m[i]) - 48) * pow(10, m.length() - i - 1);
    }
    return result;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");
    setlocale(0, "Rus");
    int option = 0, password = 0, i = 0, k = 0, key = 0;
    string checking;
    bool b = 1;
    while (b) {
        int A[32], B[32];
        for (int j = 0; j < 32; j++) {
            A[j] = 0;
            B[j] = 0;
        }
        password = 0, i = 0, k = 0, key = 0;
        cout << "1.Шифрование\n2.Дешифрование\n0.Закончить работу с программой" << endl << ">";
        cin >> checking;
        cin.ignore(INT_MAX, '\n');
        option = checkInt(checking,10);
        system("cls");
        switch (option) {
        case (1): {
            cout << "Введите пароль из 8 цифр: ";
            cin >> checking;
            cin.ignore(INT_MAX, '\n');
            password = checkInt(checking,8);
            while (password > 0) {
                A[i] = password % 2;
                password = password / 2;
                i++;
            }
            for (k = 0; k < i / 2; k++) {
                password = A[k];
                A[k] = A[i - k - 1];
                A[i - k - 1] = password;
            }
            cout << endl;
            password = 0;
            for (k = 0; k < i; k++) {
                B[k] = rand() % 2;
                A[k] = A[k] ^ B[k];
                password += A[k] * pow(2, i - k - 1);
                key += B[k] * pow(2, i - k - 1);
            }
            cout << endl;
            cout << "Зашифрованный пароль: " << password << endl;
            cout << "Ключ: " << key << endl;
            break;
        }
        case(2): {
            cout << "Введите зашифрованный пароль: ";
            cin >> checking;
            cin.ignore(INT_MAX, '\n');
            password = checkInt(checking,10);
            cout << "Введите ключ: ";
            cin >> checking;
            cin.ignore(INT_MAX, '\n');
            key = checkInt(checking,10);
            if (key > password) {
                while (key > 0) {
                    B[i] = key % 2;
                    key = key / 2;
                    i++;
                }
                for (k = 0; k < i / 2; k++) {
                    key = B[k];
                    B[k] = B[i - k - 1];
                    B[i - k - 1] = key;
                }
                for (k = i - 1; k >= 0; k--) {
                    A[k] = password % 2;
                    password = password / 2;
                }
                for (k = 0; k < i; k++) {
                    A[k] = A[k] ^ B[k];
                    password += A[k] * pow(2, i - k - 1);
                }
                cout << "Расшифрованный пароль: ";
                if (password < 10000000) {
                    int size = 0, password1 = password;
                    while (password1) {
                        password1 /= 10;
                        size++;
                    }
                    for (int j = 0; j < 8 - size; j++) {
                        cout << 0;
                    }
                }
                cout << password << endl;
            }
            else {
                while (password > 0) {
                    A[i] = password % 2;
                    password = password / 2;
                    i++;
                }
                for (k = 0; k < i / 2; k++) {
                    password = A[k];
                    A[k] = A[i - k - 1];
                    A[i - k - 1] = password;
                }
                for (k = i - 1; k >= 0; k--) {
                    B[k] = key % 2;
                    key = key / 2;
                }
                password = 0;
                for (k = 0; k < i; k++) {
                    A[k] = A[k] ^ B[k];
                    password += A[k] * pow(2, i - k - 1);
                }
                cout << "Расшифрованный пароль: ";
                if (password < 10000000) {
                    int size = 0, password1 = password;
                    while (password1) {
                        password1 /= 10;
                        size++;
                    }
                    for (int j = 0; j < 8 - size; j++) {
                        cout << 0;
                    }
                }
                cout << password << endl;
            }
            break;
        }
        case(0): {
            b = false;
            system("cls");
            cout << "До свидания! Всего хорошего!";
            break;
        }
        default: {
            cout << "Нет такого варианта, введите требуемый! ";
            cin >> checking;
            cin.ignore(INT_MAX, '\n');
            option = checkInt(checking,10);
            break;
        }
        }
    }
}