
#include "Cashe.h"

struct Sheep{
    string name;
    int age;
};

template<class I>
int HashFunction(I key, size_t size){ // ПЕРЕДЕЛАТЬ НА ДВОЙНОЕ ХЭШИРОВАНИЕ
    int k;
    k = tolower(key[0]) % size;
    return (k);
};

int main(){
    int (*function)(string, size_t) = HashFunction;
//    HashTable<string, struct Sheep> hashtable(function, 4);

    struct Sheep Enn, Kate, Dolly, Mark;
    Enn.name = "Enn Unisted";
    Kate.name = "Kate Markov";
    Dolly.name = "Molly Green";
    Mark.name = "Mark Arkined";

    Enn.age = 13;
    Kate.age = 10;
    Dolly.age = 25;
    Mark.age = 15;

    cout << Enn.name << " - " << HashFunction(Enn.name, 4) << endl;
    cout << Kate.name << " - " << HashFunction(Kate.name, 4) << endl;
    cout << Dolly.name << " - " << HashFunction(Dolly.name, 4) << endl;
    cout << Mark.name << " - " << HashFunction(Mark.name, 4) << endl << endl;

//    hashtable.append(Enn.name, Enn);
//    hashtable.append(Mark.name, Mark);
//    hashtable.append(Dolly.name, Dolly);
//    hashtable.append(Kate.name, Kate);

//    hashtable.remove(Kate.name);

//    hashtable.append(Kate.name);
//    hashtable.printvect();

    Cashe<string, struct Sheep> cash(4, function, 40);
    cash.push(Enn.name, Enn);
    if(cash.search(Enn.name))
        cout << "OK";

//    cash.remove();


    return (0);
}