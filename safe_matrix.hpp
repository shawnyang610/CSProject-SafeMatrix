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
    SafeArray<SafeArray<T>> safe_ary;
public:
    int row_l, row_h, row_size, col_l, col_h, col_size;

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

    SafeMatrix<T> operator* (SafeMatrix &);

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

    this-> safe_ary = safe_matrix.safe_ary;
}

template <typename T>
SafeMatrix<T>::~SafeMatrix() {
}

template <typename T>
SafeMatrix<T>& SafeMatrix<T>::operator=(const SafeMatrix & safe_matrix) {
    if (this == &safe_matrix){
        return *this;
    }
    this-> row_l = safe_matrix.row_l;
    this-> row_h = safe_matrix.row_h;
    this-> row_size = safe_matrix.row_size;
    this-> col_l = safe_matrix.col_l;
    this-> col_h = safe_matrix.col_h;
    this-> col_size = safe_matrix.col_size;

    this-> safe_ary = safe_matrix.safe_ary;
    return *this;
}

template <typename T>
SafeMatrix<T> SafeMatrix<T>::operator*(SafeMatrix & safe_matrix) {
    // if illegal size, throw exception
    if (this->col_size != safe_matrix.row_size){
        throw std::invalid_argument("Wrong matrix size for multiplication.");
    }
    // create a temp matrix with calculated resulting matrix size
    SafeMatrix<T> temp (this->row_size, safe_matrix.col_size);
    // populate values into temp matrix
    for (int i=0; i<temp.row_size;i++){
        for (int j=0; j<temp.col_size; j++){
            T sum = 0;
            for (int k=0; k<safe_matrix.row_size;k++){
                sum += ((this->safe_ary[i+this->row_l][k+this->col_l]) * (safe_matrix[k+safe_matrix.row_l][j+safe_matrix.col_l]));
            }
            temp[i][j] = sum;
        }
    }
    // return temp matrix by value
    return temp;
}

template<typename T>
SafeArray<T>& SafeMatrix<T>::operator[](const int i) {

        return safe_ary[i];
}


template <typename T>
void SafeMatrix<T>::init_empty_safematrix() {
    row_l=0;
    row_h=-1;
    row_size=row_h-row_l+1;
    col_l=0;
    col_h=-1;
    col_size=col_h-col_l+1;
}

template <typename T>
void SafeMatrix<T>::init_nonempty_safematrix(const int row_l, const int row_h, const int col_l, const int col_h) {
    this->row_l = row_l;
    this->row_h = row_h;
    this->row_size = row_h - row_l +1;
    this->col_l= col_l;
    this->col_h= col_h;
    this->col_size= col_h - col_l + 1;
    this->safe_ary.resize(row_l, row_h) ;
    for (int i=row_l; i<=row_h; i++){
        safe_ary[i].resize(col_l, col_h);
    }
}


#endif //SAFE_MATRIX_SAFE_MATRIX_H
