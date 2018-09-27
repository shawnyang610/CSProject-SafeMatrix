

#ifndef SAFE_MATRIX_SAFE_ARRAY_H
#define SAFE_MATRIX_SAFE_ARRAY_H
#include <iostream>

template <typename T>
class SafeArray {
    T *safe_ary;
    int l,h,size;

    // shared function for initialising empty SafeArray object
    void init_empty_safeary();

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
void SafeArray<T>::init_empty_safeary() {
    l=0;
    h=-1;
    size = 0;
    safe_ary=nullptr;
}

template <typename T>
SafeArray<T>::SafeArray() {
    init_empty_safeary();
}

template <typename T>
SafeArray<T>::SafeArray(const int size) {
    if (size<0) {
        std::cout<<"size cannot be negative number."<<std::endl;
        exit(1);
    }

    else if(size > 0) {
        l = 0;
        h = size - 1;
        this->size=size;
        safe_ary = new T[size];
    }
    else {
        init_empty_safeary();
    }
}

template <typename T>
SafeArray<T>::SafeArray(const int l, const int h) {
    if (h == -1 && l == 0){
        init_empty_safeary();
    }
    else if (h-l<0){
        std::cout<<"size cannot be negative number."<<std::endl;
        exit(1);
    }
    else {
        this->l = l;
        this->h = h;
        size = h - l + 1;
        safe_ary = new T[size];
    }
}

template <typename T>
SafeArray<T>::SafeArray(const SafeArray<T>& safe_ary) {
    this->l=safe_ary.l;
    this->h=safe_ary.h;
    this->size=safe_ary.size;
    this->safe_ary = new T[SafeArray<T>::size];
    for (int i=0; i<SafeArray<T>::size; i++)
        this->safe_ary[i]=safe_ary.safe_ary[i];
}

template <typename T>
SafeArray<T>::~SafeArray() {
    delete[] safe_ary;
}

template <typename T>
SafeArray<T>& SafeArray<T>::operator=(const SafeArray & safe_ary) {
    if (this == &safe_ary){
        return *this;
    }
    delete [] this->safe_ary;
    this->safe_ary = new T [safe_ary.size];
    for (int i=0; i<safe_ary.size; i++){
        this->safe_ary[i] = safe_ary.safe_ary[i];
    }
    this->l = safe_ary.l;
    this->h = safe_ary.h;
    this->size = safe_ary.size;
    return *this;
}

template <typename T>
T& SafeArray<T>::operator[](const int i) {
    if (i<l || i>h){
        std::cout<<"index out of range."<<std::endl;
        throw std::out_of_range("index is out of range");
    }
    else
        return safe_ary[i-l];
}

template <typename T>
void SafeArray<T>::resize(const int l, const int h) {
    this->l = l;
    this->h = h;
    this->size = h-l+1;
    delete[] safe_ary;
    safe_ary = new T[SafeArray<T>::size];
}
#endif //SAFE_MATRIX_SAFE_ARRAY_H
