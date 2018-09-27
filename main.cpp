// SafeMatrix: A templatized matrix class with bound check and arithmetics functionality.
// Author: Shawn Yang
// 9/23/2018

#include "tests.hpp"
#include <iostream>




int main() {
    test_safe_array<int>(5,10);
    int ROW_L = 5;
    int ROW_H = 10;
    int COL_L = 0;
    int COL_H = 2;

    test_safe_matrix<int>(ROW_L, ROW_H, COL_L, COL_H);

    return 0;
}