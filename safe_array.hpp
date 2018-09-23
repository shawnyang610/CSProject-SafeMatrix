//
// Created by shawn on 9/23/18.
//

#ifndef SAFE_MATRIX_SAFE_ARRAY_H
#define SAFE_MATRIX_SAFE_ARRAY_H
#include <iostream>

template <typename T>
class SafeArray {
    T *safe_ary;
    int l,h,size;

public:
    // constructors
    SafeArray();
    SafeArray(const int);
    SafeArray(const int, const int);
    // copy constructor
    SafeArray(const SafeArray<T>&);
    //destructor
    ~SafeArray();

    void resize(const int, const int);

    //overload operator=
    SafeArray<T>& operator=(const SafeArray &);

    //overload operator[], so we can write sm[3][2]
    T &operator[](const int);

};

// implementation

template <typename T>
SafeArray<T>::SafeArray() {
    l=0;
    h=-1;
    size = 0;
    safe_ary=nullptr;
}

template <typename T>
SafeArray<T>::SafeArray(const int size) {
    if (size ==0) {
        l=0;
        h=-1;
        SafeArray<T>::size=0;
        safe_ary=nullptr;
    }
    else if (size<0) {
        std::cout<<"size cannot be negative number."<<std::endl;
        exit(1);
    }

    else {
        l = 0;
        h = size - 1;
        SafeArray::size=size;
        safe_ary = new T[size];
    }
}

template <typename T>
SafeArray<T>::SafeArray(const int l, const int h) {
    if (h == -1 && l == 0){
        SafeArray<T>::l=0;
        SafeArray<T>::h=-1;
        SafeArray<T>::size=0;
        safe_ary=nullptr;
    }
    else if (h-l<0){
        std::cout<<"size cannot be negative number."<<std::endl;
        exit(1);
    }
    else {
        SafeArray::l = l;
        SafeArray::h = h;
        size = h - l + 1;
        safe_ary = new T[size];
    }
}

template <typename T>
SafeArray<T>::SafeArray(const SafeArray<T>& safe_ary) {
    SafeArray<T>::l=safe_ary.l;
    SafeArray<T>::h=safe_ary.h;
    SafeArray<T>::size=safe_ary.size;
    SafeArray<T>::safe_ary = new T[SafeArray<T>::size];
    for (int i=0; i<SafeArray<T>::size; i++)
        SafeArray<T>::safe_ary[i]=safe_ary.safe_ary[i];
}

template <typename T>
SafeArray<T>::~SafeArray() {
    delete[] safe_ary;
}

template <typename T>
SafeArray<T>& SafeArray<T>::operator=(const SafeArray &) {
    //TODO
}

template <typename T>
T& SafeArray<T>::operator[](const int i) {
    if (i<l || i>h){
        std::cout<<"index out of range."<<std::endl;
        exit(1);
    }
    return safe_ary[i-l];
}

template <typename T>
void SafeArray<T>::resize(const int l, const int h) {
    SafeArray<T>::l = l;
    SafeArray<T>::h = h;
    SafeArray<T>::size = h-l+1;
    delete[] safe_ary;
    safe_ary = new T[SafeArray<T>::size];
}
#endif //SAFE_MATRIX_SAFE_ARRAY_H
