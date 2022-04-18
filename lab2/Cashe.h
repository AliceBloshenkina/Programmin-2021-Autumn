#ifndef LAB2_CASHE_H
#define LAB2_CASHE_H

#include <queue>
#include <ctime>
#include "HashTable.h"

template<class I>
struct QueueItem{
    I key;
    time_t time_el;
};

// добавить const


// ДЛЯ ТРЕТИЙ ЛАБЫ 2 АЛГОРИТМА + РЕАЛИЗОВАТЬ ДЕЙКСТРУ
// ПРЕЗА + НЕ ПОИСКА КРАТЧАЙШЕГО ПУТИ
// Поиск в бинарном дереве


// массив вершин - ноде - там внутри ид тоже    хранится - в ней хранится ребро
// в одной вершине - массив ребер
// граф - массив вершин

// обход в глубину и обход в ширину
// дейкстра - поиск кратчайшего пути  ++ флойд или ктото у насти -

template<class I, class V>
class Cashe {

private:
    HashTable<I, V> hashtable_;
    queue<QueueItem<I>> cashe_;
    size_t size_;
    time_t time_life_;

public:
    Cashe (size_t size, int (*function)(I key, size_t), time_t time_life) : hashtable_(function, size ){
        size_ = size;
        time_life_ = time_life;
    };

    const V& get(I key){
        while(!cashe_.empty() &&  clock() - cashe_.front().time_el >= time_life_ ){
            hashtable_.remove(cashe_.front().key);
            cashe_.pop();
            size_--;
        }
        return (hashtable_.get(key));
    };

    void push(I key, V value){
        while((!cashe_.empty() && clock() - cashe_.front().time_el >= time_life_) || cashe_.size() == size_){
            hashtable_.remove(cashe_.front().key);
            cashe_.pop();
            size_--;
        }

        if (search(key)) {
            return;
        }

        struct QueueItem<I> *new_ptr = new struct QueueItem<I>;
        new_ptr->key = key;
        new_ptr->time_el = clock();
        size_++;
        cashe_.push(*new_ptr);
        hashtable_.append(key, value);
    };

    bool search(I key){
        return (hashtable_.search(key));
    }

};

#endif //LAB2_CASHE_H
