//
// Created by shawn on 11/4/18.
//

#ifndef SAFE_MATRIX_VNT_H
#define SAFE_MATRIX_VNT_H

#include "safe_matrix.hpp"

class VNT{
    SafeMatrix<int> matrix;
public:
    // constructor
    VNT(int, int);

    // add a int to non-full VNT. O(m+n)
    void add(int);

    // extract smallest element and leave object a VNT. O(m+n)
    int getMin();

    // sort n x n numbers in array using the object. O(n^3)
    void sort(int*, int);

    // return true if number is in the object
    bool find(int);
};


#endif //SAFE_MATRIX_VNT_H
