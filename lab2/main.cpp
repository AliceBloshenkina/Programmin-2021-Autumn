#include "Cashe.h"
#include <windows.h>

struct Sheep{
    string name;
    int age;
};

template<class I>
int HashFunction(I key, size_t size){
    int k;
    k = tolower(key[0]) % size;
    return (k);
};

int main(){
    int (*function)(string, size_t) = HashFunction;
    int size = 4;

    // ТЕСТЫ ДЛЯ ХЭШ-ТАБЛИЦЫ
    HashTable<string, struct Sheep> hashtable(function, size);

    struct Sheep Enn, Kate, Molly, Mark;
    Enn.name = "Enn Unisted";
    Kate.name = "Kate Markov";
    Molly.name = "Molly Green";
    Mark.name = "Mark Arkined";

    Enn.age = 13;
    Kate.age = 10;
    Molly.age = 25;
    Mark.age = 15;

    cout << Enn.name << " - " << HashFunction(Enn.name, size) << endl;
    cout << Kate.name << " - " << HashFunction(Kate.name, size) << endl;
    cout << Molly.name << " - " << HashFunction(Molly.name, size) << endl;
    cout << Mark.name << " - " << HashFunction(Mark.name, size) << endl << endl;


    hashtable.append(Enn.name, Enn);
    hashtable.append(Molly.name, Molly);
    hashtable.append(Mark.name, Mark);
    hashtable.append(Kate.name, Kate);

    cout << "Removing :" << endl;

    cout << "WAS - ";
    hashtable.printa(1);
    if (hashtable.search(Enn.name)){
        hashtable.remove(Enn.name);
        cout << "Now - ";
        hashtable.printa(1);
        if (!hashtable.search(Enn.name))
            cout << "A first element - correct" << endl << endl;
    }

    cout << "WAS - ";
    hashtable.printa(1);
    if (hashtable.search(Mark.name)){
        hashtable.remove(Mark.name);
        cout << "Now - ";
        hashtable.printa(1);
        if (!hashtable.search(Mark.name))
            cout << "A last element -  correct" << endl << endl;
    }

    hashtable.append(Enn.name, Enn);
    hashtable.append(Mark.name, Mark);
    cout << "WAS - ";
    hashtable.printa(1);
    if (hashtable.search(Enn.name)){
        hashtable.remove(Enn.name);
        cout << "Now - ";
        hashtable.printa(1);
        if (!hashtable.search(Enn.name))
            cout << "A middle element - correct" << endl << endl;
    }


    struct Sheep one = hashtable.get(Kate.name);

    cout << "Get is work - " << one.name << " " << one.age << endl << endl;


    cout << "CASHE: " << endl;
    Cashe<string, struct Sheep> cash(4, function, 20);
    cash.push(Enn.name, Enn);
    if (cash.search(Enn.name))
        cout << "Append is work" << endl;
    Sleep(10);
    cash.push(Mark.name, Mark);
    Sleep(10);
    cash.push(Molly.name, Molly);
    Sleep(10);
    if (!cash.search(Enn.name) && cash.search(Mark.name))
        cout << "Time to delete is working";
    return (0);
}
