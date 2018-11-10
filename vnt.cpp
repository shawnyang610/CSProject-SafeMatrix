//
// Created by shawn on 11/4/18.
//

#include "vnt.h"
#include <cmath>

VNT::VNT() : matrix(SafeMatrix<int>(1, 1)), row(1), col(1), size(0) {
    init_matrix();
}
VNT::VNT(int m, int n) : matrix(SafeMatrix<int>(m, n)), row(m), col(n), size(0) {
    init_matrix();
};

SafeArray<int>& VNT::operator[](int i) {
    return this->matrix[i];
}

void VNT::init_matrix() {
    for (int i=0; i< this->row; i++){
        for (int j=0;j<this->col;j++){
            matrix[i][j] = INT32_MAX;
        }
    }
}

void VNT::insert_and_reinsert_the_rest(int x) {
    Pos pos;
    int temp =x;
    // insert x and every subsequent number after x back into matrix, resulting in a sorted matrix
    // worst time m*n*(m+n) which is proportional to (m+n)
    do {
        x = temp;
        pos = find_insertion_point(x);
        temp = matrix[pos.row][pos.col];
        matrix[pos.row][pos.col] = x;
    } while (temp!=INT32_MAX);
}

VNT::Pos VNT::find_insertion_point(int x) {

    Pos pos{this->row-1,0};

    // find a row where x >= first element of the row
    while (pos.row>0) {
        if (this->matrix[pos.row][0] > x)
            pos.row--;
        else
            break;
    }
    // find a col where x > matrix[row][col]
    while (pos.col<this->col) {
        if (pos.col < this->col-1 && x >= this->matrix[pos.row][pos.col])
            pos.col++;
        // if such a position couldnt be found at last index of a row, reset column and increment row and return
        else if (pos.col==this->col-1 && x >= this->matrix[pos.row][pos.col]){
            pos.row++;
            pos.col = 0;
            break;
        }
        else
            break;
    }
    return pos;
}


void VNT::add(int x) {
    // 0. check if matrix is full, if not, proceed
    // 1. row <-- find_inserting_row(matrix)
    // 2. col <-- find_inserting_col(matrix, row)
    // 3. temp <-- matrix[row][col];
    // 4. matrix[row][col] <-- x
    // 5. this->add (temp) add each following number back to matrix until matrix[row][col]==INT_MAX
    // Analysis: each add operation goes through m rows and n cols to find the insertion point
    // the total cost is the total number of numbers following insertion point * (m + n) which is proportional to m+n
    // Best time: (m+n), worst time: m*n(m+n)

    if (size == col * row) return;
    insert_and_reinsert_the_rest(x);
    size++;
}


int VNT::getMin() {
    int ret = 0;
    // if matrix is empty, return 0
    if (matrix[0][0]==INT32_MAX){
        return ret;
    }

    ret = matrix[0][0];

    // Create a new VNL object and add remaining numbers left in matrix, complexity: matrix size * (m+n)
    VNT temp (this->row, this->col);
    for (int r =0; r<this->row; r++){
        for (int c=0; c<this->col; c++){
            if ((r!=0 || c!=0) && matrix[r][c]!=INT32_MAX){
                temp.add(matrix[r][c]);
            }
        }
    }
    // copy value from temp to matrix
    matrix = temp.matrix;
    this->size = temp.size;

    return ret;
}

void VNT::sort(int * ary, int size) {
    // best time complexity: O(n^3), worst O(n^5)

    // resize matrix to m * n = size of array
    int n = ceil(sqrt(size));
    this->matrix = SafeMatrix<int>(n,n);
    this->row = n;
    this->col = n;
    this->size = 0;
    init_matrix();

    // add() numbers into matrix. complexity size * add() = n*n*add()
    // best time: n*n(m+n) = O(n^3), worst time: n*n*n*n*(m+n) = O(n^5)
    for (int i=0; i<size; i++){
        add(ary[i]);
    }
    // write number back into array. complexity: n^2
    bool is_end=false;
    int i=0;
    for (int r=0;r<this->row; r++){
        for (int c=0; c<this->col; c++){
            if (i>=size)
                is_end = true;
            if (is_end) break;
            ary[i++] = matrix[r][c];
        }
        if (is_end) break;
    }
}

bool VNT::find(int x) {
    // worst time complexity m+n

    Pos pos {this->row-1,0}; // initialize starting search position

    // find row, worst time complexity: # of rows
    while (pos.row>0) {
        if (this->matrix[pos.row][0] > x)
            pos.row--;
        else
            break;
    }

    // search through col, worst time: # of cols
    for (;pos.col<this->col; pos.col++){
        if (x==this->matrix[pos.row][pos.col])
            return true;
    }
    return false;
}