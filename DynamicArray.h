
#ifndef POP_DYNAMICARRAY_H
#define POP_DYNAMICARRAY_H

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

    T getFirst(){
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

    void quickSort(int (*function)(const T, const T), int start, int end){
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

    void bubbleSort(int (*function)(const T, const T))
    {
        for(int i = 0; i < size_ - 1; i++){
            for(int j = 0; j < size_ - i - 1; j++){
                if(function(array_[j], array_[j + 1]) == 1)
                    swap(array_[j], array_[j + 1]);
            }
        }
    }

    void sortMerger(int (*function)(const T, const T), T *brr, int first, int end) {
        int temp, middle;

        if (first == end)
            return;
        if (abs(end - first) == 1) {
            if (function(array_[first], array_[end]) == 1) {
                swap(array_[first], array_[end]);
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

        for (int i = first; i < c; i++){
            array_[i] = brr[i];

    }

    };

    ~DynamicArray() {
        delete[] array_;
        array_ = nullptr;
        size_ = 0;
    };
};

#endif //POP_DYNAMICARRAY_H
