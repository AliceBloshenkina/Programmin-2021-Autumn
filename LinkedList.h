#ifndef POP_LINKEDLIST_H
#define POP_LINKEDLIST_H

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

    void quickSort(int(*function)(const T, const T), Item *start, Item *end, Item *m_prev) {
        if (start == end || start == nullptr || end == nullptr)
            return;

        Item *pivot = start;
        Item *ptr = start->next;
        Item *prev = start;
        Item *prev_pivot = nullptr;

        while (ptr != end->next && ptr != nullptr && pivot->next != nullptr && pivot != end) { // ptr != pivot      end->next

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

        quickSort(function, start, prev_pivot, m_prev);
        quickSort(function, pivot->next, end, pivot);
    }



    void bubbleSort(int (*function)(const T, const T)){
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

    Item *sortMerger(int (*function)(const T, const T), Item *arr){ // list->head nullptr
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

#endif //POP_LINKEDLIST_H
