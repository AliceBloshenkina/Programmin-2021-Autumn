#ifndef LAB2_HASHTABLE_H
#define LAB2_HASHTABLE_H

#include <iostream>
#include <exception>
#include <cstring>
#include <fstream>
#include <complex>
#include <ctime>
#include <vector>


using namespace std;

template<class I, class V>
struct HashItem{
    I key; // name
    V value; //sheep
    bool is_empty = true;
    struct HashItem<I, V> *next;
};

template<class I, class V>
class HashTable{

private:
    vector<HashItem<I, V>> table_;
    size_t size_;
    int (*fcnt)(I, size_t);

public:

    HashTable(int (*function)(I key, size_t), size_t size) {
        size_ = size;
        fcnt = function;
        table_.resize(size_);
    };

    void append(I key, V value){
        int i = fcnt(key, size_);
        if(table_[i].is_empty == true && table_[i].next == nullptr){
            table_[i].value = value;
            table_[i].key = key;
            table_[i].is_empty = false;
        } else {
            struct HashItem<I, V> *item = &table_[i];
            struct HashItem<I, V> *new_ptr = new HashItem<I, V>;
            new_ptr->key = key;
            new_ptr->value = value;
            new_ptr->next = nullptr;
            new_ptr->is_empty = false;
            while (item->next != nullptr && item->is_empty == false){
                item = item->next;
            }

            if (item->is_empty == true){ // удалить?? или ремув изменить
                new_ptr->next = item->next;
                item = new_ptr;
            } else {
                item->next = new_ptr;
            }
        }
    };

    bool search(I key){
        int i = fcnt(key, size_);
        struct HashItem<I, V> *item = &table_[i];
        while(item->key != key){
            if(item->next == nullptr)
                return (false);
            item = item->next;
        }
        return (true);
    };

    void remove(I key){
        if (search(key) == false){
            throw std::logic_error("You are trying to remove a non-existent item ");
        }
        int i = fcnt(key, size_);
        struct HashItem<I, V> *item = &table_[i];
        struct HashItem<I, V> *item_prev = nullptr;

        while (item->key != key){
            item_prev = item;
            item = item->next;
        }

        if (item->next == nullptr){ // если в начале и дальше пусто
            if (table_[i].key == item->key)
                table_.erase(table_.begin() + i);
            delete item;
            if (item_prev) // конце и дальше пусто
                item_prev->next = nullptr;
        } else {
            if (item_prev) { // если в середине
                item_prev->next = item->next;
                delete item;
            } else { // если в начале и дальше есть элементы
                table_[i] = *item->next;
                delete item;
            }
        }
    };

    V get(I key){
        int i = fcnt(key, size_);
        struct HashItem<I, V> *item = &table_[i];
        while (item->key != key){
            if (item->next == nullptr)
                return (nullptr);
            item = item->next;
        }
        return (item->value);
    };

};

#endif //LAB2_HASHTABLE_H
