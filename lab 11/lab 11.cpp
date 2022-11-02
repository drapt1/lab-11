#include <iostream>
#include <cstdlib>
#include <locale.h>
#pragma warning(disable: 4996)
using namespace std;
 
struct Elem {
    int key;
    Elem* pnext;
    static unsigned siz;
};
 
unsigned Elem::siz = 0;
 
int first_elem(Elem* *pbeg, Elem* *pend, int d) {
    Elem* ph = new Elem;
    ph->key = d;
    ph->pnext = 0;
    *pbeg = ph;
    *pend = ph;
    ++Elem::siz;
 
    return 0;
}
int add_elem(Elem* *pend, int d) {
    Elem* ph = new Elem;
    ph->key = d;
    ph->pnext = 0;
    (*pend)->pnext = ph;
    *pend = ph;
    ++Elem::siz;
 
    return 0;
}
int del_elem(Elem* *pbeg, Elem* *pend, int k) {
    Elem* tmp = *pbeg;
    if (!*pbeg) {
        cout << "Ошибка: список пуст" << endl;
        return 0;
    }
 
    if ((*pbeg)->key == k) {
        if (*pbeg == *pend) {
            *pbeg = 0;
            *pend = 0;
            delete tmp;
            --Elem::siz;
        }
        else {
            *pbeg = (*pbeg)->pnext;
            delete tmp;
            --Elem::siz;
        }
    }
    else {
        while (tmp->pnext && tmp->pnext->key != k) {
            tmp = tmp->pnext;
        }
        if (tmp->pnext) {
            Elem* tmp1 = tmp->pnext->pnext;
            delete tmp->pnext;
            tmp->pnext = tmp1;
            --Elem::siz;
            if (!tmp->pnext) {
                *pend = tmp;
            }
        }
        else{
            return 0;
        }
    }
    return 1;
}
void del_list(Elem *pbeg) {
    if (pbeg != NULL) {
        del_list(pbeg->pnext);
        delete pbeg;
        --Elem::siz;
 
    }
}
void del(Elem* *pbeg, Elem* *pend, unsigned const n)
{
    Elem** tmp = pbeg;
    Elem* prev = nullptr;
    for (int rem = Elem::siz; rem > n; --rem)
    {
        prev = *tmp;
        tmp = &(*tmp)->pnext;
    }
    del_list(*tmp);
    *pend = prev;
    *tmp = nullptr;
}
void print_elem(Elem *pbeg) {
    Elem* ph = pbeg;
    cout << "siz: " << Elem::siz << '\n';
    while (ph) {
        cout << ph->key << ' ';
        ph = ph->pnext;
    }
    cout << endl;
}
int main() {
    setlocale(LC_ALL, "Russian");
    Elem* pbeg = 0;
    Elem* pend = 0;
    int d;
    int a;
    int k;
    int g = 0;
    int z;
    char ch;
    bool exit = false;
    do {
        system("cls");
        cout << "1 - добавить элемент/создать\n2 - удалить один\n3 - удалить несколько\n4 - просмотр\n5 - выход" << endl;
        cin >> ch;
        switch (ch) {
        case '1':
            if (!pbeg) {
                cout << "Введите 1 элемент списка: " << endl;
                cin >> d;
                first_elem(&pbeg, &pend, d);
                break;
            }
            else {
                cout << "Введите новый элемент списка: " << endl;
                cin >> a;
                add_elem(&pend, a);
                break;
            }
            g = 1;
        case '2':
            cout << "Введите значение элемента для удаления: " << endl;
            cin >> k;
            if (del_elem(&pbeg, &pend, k) == 0) {
                cout << "Элемент для удаления не найден" << endl;
            }
            break;
        case '3':
            cout << "Сколько хотите удалить элементов с конца: " << endl;
            cin >> z;
            del(&pbeg, &pend, z);
            break;
        case '4':
            if (g == 1) {
                cout << "Список всех элементов" << endl;
                print_elem(pbeg);
            }
            else
                cout << "Список пуст" << endl;
            break;
        case '5':
            exit = true;
            break;
        }
        _flushall;
        system("Pause");
    } while (!exit);
    if (pbeg != NULL) {
        del_list(pbeg->pnext);
        delete pbeg;
        Elem::siz = 0;
    }
    return 0;
}
