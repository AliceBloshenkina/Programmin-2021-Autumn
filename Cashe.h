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

template<class I, class V>
class Cashe {

private:
    HashTable<I, V> hashtable_ ;
    queue<QueueItem<I>> cashe_;
    size_t size_;
    time_t time_life_;

public:
    Cashe (size_t size, int (*function)(I key, size_t), time_t time_life) : hashtable_(function, size){
        size_ = size;
        time_life_ = time_life;
    };

    V get(I key){
        while(!cashe_.empty() && cashe_.front().time_el - clock() >= time_life_){
            hashtable_.remove(cashe_.front().key);
            cashe_.pop();
        }

        return (hashtable_.get(key));

    };

    void push(I key, V value){
        while(!cashe_.empty() && cashe_.front().time_el - clock() >= time_life_){
            hashtable_.remove(cashe_.front().key);
            cashe_.pop();
        }

        if (search(key)) {
            return;
        }

        struct QueueItem<I> *new_ptr = new struct QueueItem<I>;
        new_ptr->key = key;
        new_ptr->time_el = clock();
        cashe_.push(*new_ptr);
        hashtable_.append(key, value);
    };

    bool search(I key){
        return (hashtable_.search(key));
    }

};

#endif //LAB2_CASHE_H
