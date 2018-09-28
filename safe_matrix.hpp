// SafeMatrix: A templatized matrix class with matrix arithmetics and bound checks.
// Author: Shawn Yang
// 9/23/2018

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
    void init_empty_safematrix();
    void init_nonempty_safematrix(const int, const int, const int, const int);
};


// Implementation starts from here


template <typename T>
SafeMatrix<T>::SafeMatrix(){
    init_empty_safematrix();
}

template <typename T>
SafeMatrix<T>::SafeMatrix(const int row_size, const int col_size) {
    row_l=0;
    row_h= row_size-1;
    col_l=0;
    col_h=col_size-1;

    init_nonempty_safematrix(row_l, row_h, col_l, col_h);
}

template <typename T>
SafeMatrix<T>::SafeMatrix(const int row_l, const int row_h, const int col_l, const int col_h) {
    init_nonempty_safematrix(row_l, row_h, col_l, col_h);
}

template <typename T>
SafeMatrix<T>::SafeMatrix(const SafeMatrix<T>& safe_matrix) {
    this-> row_l = safe_matrix.row_l;
    this-> row_h = safe_matrix.row_h;
    this-> row_size = safe_matrix.row_size;
    this-> col_l = safe_matrix.col_l;
    this-> col_h = safe_matrix.col_h;
    this-> col_size = safe_matrix.col_size;

    this-> safe_ary = new SafeArray<T>[safe_matrix.row_size];
    for (int i=0; i<safe_matrix.row_size; i++){
        this->safe_ary[i]=safe_matrix.safe_ary[i];
    }
}

template <typename T>
SafeMatrix<T>::~SafeMatrix() {
    delete[] safe_ary;
}

template <typename T>
SafeMatrix<T>& SafeMatrix<T>::operator=(const SafeMatrix & safe_matrix) {
    if (this == &safe_matrix){
        return *this;
    }
    delete [] this->safe_ary;
    this-> row_l = safe_matrix.row_l;
    this-> row_h = safe_matrix.row_h;
    this-> row_size = safe_matrix.row_size;
    this-> col_l = safe_matrix.col_l;
    this-> col_h = safe_matrix.col_h;
    this-> col_size = safe_matrix.col_size;

    this-> safe_ary = new SafeArray<T>[safe_matrix.row_size];
    for (int i=0; i<safe_matrix.row_size; i++){
        this->safe_ary[i]=safe_matrix.safe_ary[i];
    }
    return *this;
}

template<typename T>
SafeArray<T>& SafeMatrix<T>::operator[](const int i) {
    if (i<row_l || i>row_h){
        std::cout<<"index out of range."<<std::endl;
        throw std::out_of_range("index is out of range");
    }
    else
        return safe_ary[i-row_l];
}


template <typename T>
void SafeMatrix<T>::init_empty_safematrix() {
    row_l=0;
    row_h=-1;
    row_size=row_h-row_l+1;
    col_l=0;
    col_h=-1;
    col_size=col_h-col_l+1;
    safe_ary= nullptr;
}

template <typename T>
void SafeMatrix<T>::init_nonempty_safematrix(const int row_l, const int row_h, const int col_l, const int col_h) {
    this->row_l = row_l;
    this->row_h = row_h;
    this->row_size = row_h - row_l +1;
    this->col_l= col_l;
    this->col_h= col_h;
    this->col_size= col_h - col_l + 1;
    this->safe_ary= SafeArray<SafeArray<T>>(row_l, row_h, col_l, col_h) ;
}


#endif //SAFE_MATRIX_SAFE_MATRIX_H
