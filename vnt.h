//
// Created by shawn on 11/4/18.
//

#ifndef SAFE_MATRIX_VNT_H
#define SAFE_MATRIX_VNT_H

#include "safe_matrix.hpp"

class VNT{

    int row, col, size;

    SafeMatrix<int> matrix;
    struct Pos {
        int row;
        int col;
    };

    // initialize matrix with INT32_MAX
    void init_matrix();

    // insert x and every subsequent number after x back into matrix, resulting in a sorted matrix
    // worst time m*n*(m+n) which is proportional to (m+n)
    void insert_and_reinsert_the_rest(int);

    // find insertion point by finding row first then column, worst complexity m+n
    Pos find_insertion_point(int);


public:
    // constructors
    VNT();
    VNT(int, int);

    // add a int to non-full VNT. worst time mn(m+n)
    void add(int);

    // extract smallest element and leave object a VNT. worst time mn(m+n)
    int getMin();

    // sort n x n numbers in array using the object. O(n^3)
    void sort(int*, int);

    // return true if number is in the object. worst time m+n
    bool find(int);

    SafeArray<int> & operator[] (int);
};


#endif //SAFE_MATRIX_VNT_H
