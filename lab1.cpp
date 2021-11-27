#include <iostream>
#include <exception>
#include <cstring>
#include <fstream>
#include <cassert>
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

template<class T>
class DynamicArray : public Sequence<T> {

private:
    size_t size_;
    T *array_;

public:
    DynamicArray() {
        size_ = 0;
        array_ = nullptr;
    }

    DynamicArray(int size) {
        if (size >= 0) {

            array_ = new T[size];
            for (int i = 0; i < size; i++)
                array_[i] = 0;

            size_ = size;

        } else
            throw out_of_range("DynamicArray(int size) -> count < 0");
    };

    DynamicArray(const T *items, int count) {

        if (count < 0)
            throw out_of_range("DynamicArray(T* items, int count) -> count < 0");

        array_ = new T[count];
        for (int i = 0; i < count; i++)
            array_[i] = items[i];

        size_ = count;
    };

    DynamicArray(const DynamicArray<T> &arr) {
        DynamicArray<T>(arr.size_);
        for (int i = 0; i < size_; ++i)
            this->array_[i] = arr.array_[i];
    };

    size_t getSize() const override {
        return size_;
    };

    T &operator[](int count) override {
        if (count >= size_)
            throw out_of_range("DynamicArray -> operator[] -> count >= size_");
        return array_[count];
    }

    void resize(int new_size) override {
        if (new_size < 0)
            throw std::length_error("DynamicArray -> operator[] -> new_size < 0");

        if (new_size == 0) {
            delete[] array_;
            array_ = nullptr;
            return;
        }

        T *new_data = new T[new_size];

        if (new_size > size_)
            memcpy(new_data, array_, size_ * sizeof(T));
        else
            memcpy(new_data, array_, new_size * sizeof(T));

        size_ = new_size;
        delete[] array_;

        array_ = new_data;
    };

    void append(const T &data) override {
        resize(size_ + 1);
        array_[size_ - 1] = data;
    };

    void prepend(const T &data) override {
        resize(size_ + 1);
        for (int i = size_ - 1; i >= 0; i--) {
            array_[i + 1] = array_[i];
        }
        array_[0] = data;
    };

    T getFirst() {
        if (size_ == 0)
            throw std::logic_error("DynamicArray -> getFirst -> size_ = 0 ");
        return array_[0];
    }

    T getLast() {
        if (size_ == 0)
            throw std::logic_error("DynamicArray -> getLast -> size_ = 0 ");
        return array_[size_ - 1];
    }

    void deleteFirst() override {
        if (size_ == 0)
            throw std::logic_error("DynamicArray -> deleteFirst -> size_ = 0 ");
        array_[0] = T(0);
        for(int i = 1; i < size_; i++){
            array_[i-1] = array_[i];
        }
        resize(size_ - 1);
    };

    void GetSubsequence(int startIndex, int endIndex) override {
        for (int i = startIndex; i <= endIndex; i++) {
            cout << array_[i] << " ";
        }
    };

    void quickSort(int (*function)(T, T), int start, int end){
        if (start < end) {
            T temp;
            T pivot = array_[(end + start) / 2];
            int l = start,
                    r = end;
            while(l <= r)
            {
                while (function(array_[l], pivot) == -1 )
                    l++;
                while (function(array_[r], pivot) == 1)
                    r--;
                if (l <= r) {
                    temp = array_[r];
                    array_[r] = array_[l];
                    array_[l] = temp;
                    l++;
                    r--;
                }
            }
            quickSort(function, start, r);
            quickSort(function, l, end);
        }
        return ;
    };

    void bubbleSort(int (*function)(T, T))
    {
        for(int i = 0; i < size_ - 1; i++){
            for(int j = 0; j < size_ - i - 1; j++){
                if(function(array_[j], array_[j + 1]) == 1)
                    swap(array_[j], array_[j + 1]);
            }
        }
    }

    void sortMerger(int (*function)(T, T), T *brr, int first, int end)
    {
        int temp, middle;

        if(first == end)
            return ;
        if(end - first == 1)
        {
            if (function(array_[first], array_[end]) == 1)
            {
                temp = array_[first];
                array_[first] = array_[end];
                array_[end] = temp;
                return;
            }
        }

        middle = (end + first) / 2;

        sortMerger(function, brr, first, middle);
        sortMerger(function, brr, middle + 1, end);

        int l = first;
        int r = middle + 1;

        int c = first;
        while (end + 1 != c) {
            if (l > middle)
                brr[c++] = array_[r++];
            else if (r > end)
                brr[c++] = array_[l++];
            else if (function(array_[l], array_[r]) == 1)
                brr[c++] = array_[r++];
            else
                brr[c++] = array_[l++];
        }

        for (int i = 0; i < c; i++)
            array_[i] = brr[i];

    };

    ~DynamicArray() {
        delete[] array_;
        array_ = nullptr;
        size_ = 0;
    };
};

template<class T>
class LinkedList : public Sequence<T> {
private:
    struct Item {
        T data;
        Item *next;
    };
    struct List {
        Item *head;
        Item *tail;
    };
    List *list_;
    size_t size_;

public:
    LinkedList() {
        list_ = new List;
        list_->head = nullptr;
        list_->tail = nullptr;
        size_ = 0;
    };

    LinkedList(int count) : LinkedList() {
        for (int i = 0; i < count; ++i)
            append(0);
    };

    LinkedList(const T *items, int count) : LinkedList() {
        for (int i = 0; i < count; ++i)
            append(items[i]);
    };

    LinkedList(const LinkedList<T> &list) : LinkedList() {
        Item *ptr = list.list_->head;
        for (int i = 0; i < list.size_; i++) {
            append(ptr->data);
            ptr = ptr->next;
        }
    };

    size_t getSize() const override {
        return size_;
    };

    void append(const T &data) override {

        Item *ptr = new Item;

        ptr->data = data;
        ptr->next = nullptr;

        if (list_->head == nullptr) {
            list_->head = ptr;
            list_->tail = ptr;
        } else {
            list_->tail->next = ptr;
            list_->tail = ptr;
        }
        size_++;
    };

    void resize(int newSize) override {
        Item *ptr = list_->head;
        if (newSize == size_) {
            return;
        } else if (newSize < size_) {
            for (int i = 0; i < newSize; ++i) {
                ptr = ptr->next;
            }
            Item *ptr_prev;
            while (ptr) {
                ptr_prev = ptr;
                ptr = ptr->next;
                //delete ptr_prev->data;
                ptr_prev->next = nullptr;
                delete ptr_prev;
            }
        } else if (newSize > size_) {
            for (int i = size_; i < newSize; i++) {
                append(T(0));
            }
        }
    };

    void prepend(const T &data) override {
        Item *ptr = new Item;
        if (!ptr) {
            return;
        }
        ptr->data = data;
        if (!list_->head) {
            ptr->next = nullptr;
            list_->tail = ptr;
        } else
            ptr->next = list_->head;
        list_->head = ptr;
        size_++;

    };

    Item *getFirst() {
        if (list_->head == nullptr)
            throw std::logic_error("LinkedList -> getFirst -> list_->head == nullptr ");
        return list_->head;
    }

    void setFirst(Item *ptr){
        if (ptr)
            list_->head = ptr;
    }

    Item *getLast() {
        if (list_->tail == nullptr)
            throw std::logic_error("LinkedList -> getLast -> list_->tail == nullptr ");
        return list_->tail;
    }

    void deleteFirst() override {
        if (list_->head == nullptr)
            throw std::logic_error("LinkedList -> deleteFirst -> list_->head == nullptr ");

        Item *ptr = list_->head->next;
        Item *ptr_prev = list_->head;

        ptr_prev->next = nullptr;
        delete ptr_prev;
        list_->head = ptr;

        size_ -= 1;
    };

    T &operator[](int count) override {
        if (count >= size_)
            throw out_of_range("LinkedList -> operator[] -> count >= size_");

        Item *ptr = list_->head;

        for (int i = 0; i < count; ++i) {
            ptr = ptr->next;
        }

        return ptr->data;
    }

    void GetSubsequence(int startIndex, int endIndex) override {
        Item *ptr = list_->head;
        for (int i = 0; i < startIndex; ++i) {
            ptr = ptr->next;
        }
        for (int i = startIndex; i <= endIndex; ++i) {
            cout << ptr->data << " ";
            ptr = ptr->next;
        }
    };

    void quickSort(int(*function)(T, T), Item *start, Item *end, Item *m_prev) {
        if (start == end || start == nullptr || end == nullptr)
            return;

        Item *pivot = start;
        Item *ptr = start->next;
        Item *prev = start;
        Item *prev_pivot = nullptr;

        while (ptr != end->next && ptr != nullptr && pivot->next != nullptr && pivot != end->next && ptr != pivot) {

            if (function(ptr->data, pivot->data) == -1) {
                if (list_->head == start)
                    list_->head = ptr;
                if (pivot == start)
                    prev_pivot = ptr;
                if (ptr == end)
                    end = prev;
                prev->next = ptr->next;
                if(!ptr->next)
                    list_->tail = prev->next;
                ptr->next = start;
                start = ptr;
                if(m_prev != nullptr)
                    m_prev->next = ptr;
                ptr = prev->next;
            } else {
                prev = ptr;
                ptr = ptr->next;
            }
        }

        quickSort(function, start, prev_pivot, nullptr);
        quickSort(function, pivot->next, end, pivot);
    }



    void bubbleSort(int (*function)(T, T)){
        Item *ptr = list_->head;
        Item *n_tail = list_->tail;
        Item *prev = ptr;
        T temp;

        while(n_tail != ptr->next)
        {
            while(ptr->next && n_tail != ptr)
            {
                if(function(ptr->data, ptr->next->data) == 1)
                {
                    temp = ptr->data;
                    ptr->data = ptr->next->data;
                    ptr->next->data = temp;
                }
                prev = ptr;
                ptr = ptr->next;
            }
            n_tail = prev;
            ptr = list_->head;
        }
    };

    Item *sortMerger2(Item *arr, Item *brr){
        if (!arr)
            return brr;
        if (!brr)
            return arr;
        Item *crr = nullptr;
        if (arr->data < brr->data){
            crr = arr;
            crr->next = sortMerger2(arr->next, brr);
        } else {
            crr = brr;
            crr->next = sortMerger2(arr, brr->next);
        }
        return crr;
    };

    Item *sortMerger(int (*function)(T, T), Item *arr){ // list->head nullptr
        if (arr == nullptr || arr->next == nullptr)
            return arr;
        Item *arr_h = arr, *brr = arr->next;
        while ((brr != nullptr) && (brr->next != nullptr))
        {
            arr = arr->next;
            brr = brr->next->next;
        }
        brr = arr->next;
        arr->next = nullptr;

        return (sortMerger2(sortMerger(function, arr_h), sortMerger(function, brr)));
    };

};

int compareInt(int data1, int data2){
    if (data1 > data2)
        return (1);
    if (data1 < data2)
        return (-1);
    return (0);
}

template<class T>
class Sorting{
public:

    void Sort(Sequence<T>* sequence, int (*function)(T data1, T data2)){
        int i;
        cout << "1. Merge sort \n2. Bubble sort\n3. Quick sort\n";
        cin >> i;
        switch(i)
        {
            case 1:
                if (dynamic_cast<LinkedList<T>*>(sequence)){
                    LinkedList<T>* lst = dynamic_cast<LinkedList<T>*>(sequence);
                    lst->GetSubsequence(0, lst->getSize() - 1);
                    cout << endl;
                    lst->setFirst(lst->sortMerger(function, lst->getFirst()));
                    lst->GetSubsequence(0, lst->getSize() - 1);
                }
                if(dynamic_cast<DynamicArray<T>*>(sequence)){
                    DynamicArray<T>* arr = dynamic_cast<DynamicArray<T>*>(sequence);
                    arr->GetSubsequence(0, arr->getSize() - 1);
                    cout << endl;
                    T brr[arr->getSize()];
                    arr->sortMerger(function, brr, 0, arr->getSize() - 1);
                    arr->GetSubsequence(0, arr->getSize() - 1);
                }
                break;
            case 2:
                if (dynamic_cast<LinkedList<T>*>(sequence)){
                    LinkedList<T>* lst = dynamic_cast<LinkedList<T>*>(sequence);
                    lst->GetSubsequence(0, lst->getSize() - 1);
                    cout << endl;
                    lst->bubbleSort(function);
                    lst->GetSubsequence(0, lst->getSize() - 1);
                }
                if (dynamic_cast<DynamicArray<T>*>(sequence)){
                    DynamicArray<T>* arr = dynamic_cast<DynamicArray<T>*>(sequence);
                    arr->GetSubsequence(0, arr->getSize() - 1);
                    arr->bubbleSort(function);
                    cout << endl;
                    arr->GetSubsequence(0, arr->getSize() - 1);
                }
                break;
            case 3:
                if (dynamic_cast<LinkedList<T>*>(sequence)){
                    LinkedList<T>* lst = dynamic_cast<LinkedList<T>*>(sequence);
                    lst->GetSubsequence(0, lst->getSize() - 1);
                    cout << endl;
                    lst->quickSort(function, lst->getFirst(), lst->getLast(), nullptr);
                    lst->GetSubsequence(0, lst->getSize() - 1);
                }
                if (dynamic_cast<DynamicArray<T>*>(sequence)){
                    DynamicArray<T>* arr = dynamic_cast<DynamicArray<T>*>(sequence);
                    arr->GetSubsequence(0, arr->getSize() - 1);
                    arr->quickSort(function, 0, arr->getSize() - 1);
                    cout << endl;
                    arr->GetSubsequence(0, arr->getSize() - 1);
                }
                break;
        }
    }
};

int main() {

    Sorting<int> srt;

    int size = 15;
    DynamicArray<int> lst;
    for(int i = 0; i < size; i++){
        lst.append((rand() % size) + 1);
    }

    cout << endl;
    int (*fcnt)(int, int) = compareInt;
    srt.Sort(&lst, fcnt);

    return 0;
}
