#include "safe_array.hpp"
#include "safe_matrix.hpp"
#include <iostream>

template <typename T>
void test_safe_array(const int l, const int h) {
    SafeArray<T> safe_ary(l,h);
    for (int i=l ;i<=h; i++){
        safe_ary[i]= i*10;
    }
    for (int i=l; i<=h; i++){
        std::cout<<"safe_ary["<<i<<"]:"<<safe_ary[i]<<std::endl;
    }
}

template<typename T>
void test_safe_matrix (const int row_size, const int col_size){
    SafeMatrix<T> safe_matrix(row_size, col_size);
    for (int i=0; i<row_size; i++){
        for (int j=0; j<col_size;j++){
            safe_matrix[i][j] = i*10+j;
        }
    }

    for (int i=0; i<row_size; i++){
        for (int j=0; j<col_size;j++){
            T res = safe_matrix[i][j];
            std::cout<<"safe_matrix["<<i<<"]["<<j<<"]:"<<res<<std::endl;
        }
    }
}


int main() {
    std::cout << "Testing Safe Array class:" << std::endl;

    test_safe_array<int>(5,10);
    test_safe_matrix<int>(5,10);
    return 0;
}