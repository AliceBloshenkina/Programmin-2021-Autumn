#include "Sequence.h"
#include "DynamicArray.h"
#include "LinkedList.h"

int compareInt(const int data1, const int data2){
    if (data1 > data2)
        return (1);
    if (data1 < data2)
        return (-1);
    return (0);
}

template<class T>
class Sorting{
public:

    void Sort(Sequence<T>* sequence, int (*function)(const T data1, const T data2)){
        int i;
        clock_t time, time2;
        cout << "1. Merge sort \n2. Bubble sort\n3. Quick sort\n";
        cin >> i;
        switch(i)
        {
            case 1:
                if (dynamic_cast<LinkedList<T>*>(sequence)){
                    LinkedList<T>* lst = dynamic_cast<LinkedList<T>*>(sequence);
//                    lst->GetSubsequence(0, lst->getSize() - 1);
//                    cout << endl;
//                    time = clock();
                    lst->setFirst(lst->sortMerger(function, lst->getFirst()));
//                    cout << static_cast<double>(clock() - time)/CLOCKS_PER_SEC;
//                    lst->GetSubsequence(0, lst->getSize() - 1);
                }
                if(dynamic_cast<DynamicArray<T>*>(sequence)){
                    DynamicArray<T>* arr = dynamic_cast<DynamicArray<T>*>(sequence);
//                    arr->GetSubsequence(0, arr->getSize() - 1);
//                    cout << endl;
                    T brr[arr->getSize()];
                    time = clock();
                    arr->sortMerger(function, brr, 0, arr->getSize() - 1);
                    cout << clock() - time;
//                    arr[0] = clock() - time;
//                    arr->GetSubsequence(0, arr->getSize() - 1);
                }
                break;
            case 2:
                if (dynamic_cast<LinkedList<T>*>(sequence)){
                    LinkedList<T>* lst = dynamic_cast<LinkedList<T>*>(sequence);
//                    lst->GetSubsequence(0, lst->getSize() - 1);
//                    cout << endl;
                    time = clock();
                    lst->bubbleSort(function);
                    cout << clock() - time;
//                    arr[0] = clock() - time;
//                    lst->GetSubsequence(0, lst->getSize() - 1);
                }
                if (dynamic_cast<DynamicArray<T>*>(sequence)){
                    DynamicArray<T>* arr = dynamic_cast<DynamicArray<T>*>(sequence);
//                    arr->GetSubsequence(0, arr->getSize() - 1);
                    time = clock();
                    arr->bubbleSort(function);
                    cout << clock() - time;
//                    arr[0] = clock() - time;
//                    cout << endl;
//                    arr->GetSubsequence(0, arr->getSize() - 1);
                }
                break;
            case 3:
                if (dynamic_cast<LinkedList<T>*>(sequence)){
                    LinkedList<T>* lst = dynamic_cast<LinkedList<T>*>(sequence);
                    lst->GetSubsequence(0, lst->getSize() - 1);
                    cout << endl;
//                    time = clock();
                    lst->quickSort(function, lst->getFirst(), lst->getLast(), nullptr);
//                    time2 = clock();
//                    cout << time2 - time;

//                    arr[0] = clock() - time;
                    lst->GetSubsequence(0, lst->getSize() - 1);
                }
                if (dynamic_cast<DynamicArray<T>*>(sequence)){
                    DynamicArray<T>* arr = dynamic_cast<DynamicArray<T>*>(sequence);
//                    arr->GetSubsequence(0, arr->getSize() - 1);
                    time = clock();
                    arr->quickSort(function, 0, arr->getSize() - 1);
                    cout << clock() - time;
//                    arr[0] = clock() - time;
//                    cout << endl;
//                    arr->GetSubsequence(0, arr->getSize() - 1);
                }
                break;
        }
    }
};

int main() {

    Sorting<int> srt;
    int (*fcnt)(const int, const int) = compareInt;
    int size = 150; //10000
    LinkedList<int> lst;

    for(int i = 0; i < size; i++){
        lst.append((rand() % size) + 1);
    }

    srt.Sort(&lst, fcnt);
}
