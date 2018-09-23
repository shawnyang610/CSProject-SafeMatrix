//
// Created by shawn on 9/23/18.
//

#ifndef SAFE_MATRIX_SAFE_MATRIX_H
#define SAFE_MATRIX_SAFE_MATRIX_H

#include "safe_array.hpp"
#include <iostream>


template<typename T>
class SafeMatrix
{
    SafeArray<T> *safe_ary;
    int row_l, row_h, row_size, col_l, col_h, col_size;
public:
    //constructor
    SafeMatrix();


    //constructor
    //params: row_size, col_size
    SafeMatrix(const int, const int);

    //constructor
    //params: row_low, row_high, col_low, col_high
    SafeMatrix(const int, const int, const int, const int);

    //constructor:copy
    SafeMatrix(const SafeMatrix<T>&);

    //destructor
    ~SafeMatrix();

    //overload operator=
    SafeMatrix<T>& operator=(const SafeMatrix &); //re-adjust size to the incoming matrix

    //overload operator[], so we can write sm[3][2]
    SafeArray<T>& operator[](const int);


private:
    void allocate_ary(T* &, const int);
};

template <typename T>
SafeMatrix<T>::SafeMatrix(){
    row_l=0;
    row_h=-1;
    row_size=row_h-row_l+1;
    col_l=0;
    col_h=-1;
    col_size=col_h-col_l+1;
    safe_ary= nullptr;
}

template <typename T>
SafeMatrix<T>::SafeMatrix(const int row_size, const int col_size) {
    row_l=0;
    row_h= row_size-1;
    SafeMatrix<T>::row_size = row_size;
    col_l=0;
    col_h=col_size-1;
    SafeMatrix<T>::col_size=col_size;
    safe_ary= new SafeArray<T>[row_size];
    for (int i=0; i<row_size;i++)
        safe_ary[i].resize(0, col_size-1);

}

template <typename T>
SafeMatrix<T>::SafeMatrix(const int row_l, const int row_h, const int col_l, const int col_h) {
    //TODO
}

template <typename T>
SafeMatrix<T>::SafeMatrix(const SafeMatrix<T>&) {
    //TODO
}

template <typename T>
SafeMatrix<T>::~SafeMatrix() {
    delete[] safe_ary;
}

template<typename T>
SafeArray<T>& SafeMatrix<T>::operator[](const int i) {
    SafeArray<T>& ret = safe_ary[i];
    return ret;
}





#endif //SAFE_MATRIX_SAFE_MATRIX_H
