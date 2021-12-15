#ifndef POP_SEQUENCE_H
#define POP_SEQUENCE_H

#include <iostream>
#include <exception>
#include <cstring>
#include <fstream>
#include <complex>
#include <ctime>

using namespace std;

template<class T>
class Sequence {
public:
    virtual size_t getSize() const = 0;

    virtual T &operator[](int count) = 0;

    virtual void resize(int new_size) = 0;

    virtual void append(const T &data) = 0;

    virtual void prepend(const T &data) = 0;

    virtual void deleteFirst() = 0;

    virtual void GetSubsequence(int startIndex, int endIndex) = 0;
};


#endif //POP_SEQUENCE_H
