// SafeMatrix: A templatized matrix class with matrix arithmetics and bound checks.
// Author: Shawn Yang
// 9/23/2018

#ifndef SAFE_MATRIX_SAFE_MATRIX_TEST_H
#define SAFE_MATRIX_SAFE_MATRIX_TEST_H

#include "safe_matrix.hpp"
#include <iostream>

template <typename T>
void test_safe_array(const int l, const int h) {
    std::cout << "::: Testing Safe Array class :::" << std::endl;
    SafeArray<T> safe_ary(l,h);
    for (int i=l ;i<=h; i++){
        safe_ary[i]= i*10;
    }
    for (int i=l; i<=h; i++){
        std::cout<<"safe_ary["<<i<<"]:"<<safe_ary[i]<<std::endl;
    }
    std::cout << std::endl;
}


template<typename T>
void test_safe_matrix (const int row_l, const int row_h, const int col_l, const int col_h){
    int row_size = row_h - row_l + 1;
    int col_size = col_h - col_l + 1;

    auto load_matrix = [](SafeMatrix<T> &safe_matrix,const int row_l, const int row_h, const int col_l, const int col_h){
        try{
            std::cout << "loading numbers..." << std::endl;
            for (int i=row_l; i<=row_h; i++){
                for (int j=col_l; j<=col_h;j++){
                    safe_matrix[i][j] = i*10+j;
                }
            }
        }
        catch (std::exception &e){
            std::cout<<"loading failed..."<< std::endl;
        }

    };

    auto verify_matrix = [=](SafeMatrix<T> &safe_matrix,const int row_l, const int row_h, const int col_l, const int col_h){
        try{
            for (int i=row_l; i<=row_h; i++){
                for (int j=col_l; j<=col_h;j++){
                    if (safe_matrix[i][j]!=i*10+j)
                        std::cout<<"test failed: incorrect value."<<std::endl;
                }
            }
            std::cout << "test passed!" << std::endl;
        }
        catch(std::exception &e){
            std::cout<<"verification failed..."<< std::endl;
        }

    };

    auto read_matrix = [=](SafeMatrix<T> &safe_matrix,const int row_l, const int row_h, const int col_l, const int col_h){
        try{
            std::cout << "reading numbers..." << std::endl;
            for (int i=row_l; i<=row_h; i++){
                for (int j=col_l; j<=col_h;j++){
                    std::cout<<"safe_matrix["<<i<<"]["<<j<<"]:"<<safe_matrix[i][j]<<std::endl;
                }
            }
        }
        catch (std::exception &e){
            std::cout<<"reading failed..."<< std::endl;
        }

    };

    auto check_bounds = [](SafeMatrix<T> &safe_matrix,const int row_l, const int row_h, const int col_l, const int col_h){
        try{
            std::cout<<"safe_matrix["<<row_l<<"]["<<col_l<<"]:"<<safe_matrix[row_l][col_l]<<std::endl;
        }
        catch (std::out_of_range &e){
            e;
        }
        try{
            std::cout<<"safe_matrix["<<row_h<<"]["<<col_h<<"]:"<<safe_matrix[row_h][col_h]<<std::endl;
        }
        catch (std::out_of_range &e){
            e;
        }

        try{
            std::cout<<"safe_matrix["<<row_l<<"]["<<col_l-1<<"]:"<<safe_matrix[row_l][col_l-1]<<std::endl;
        }
        catch (std::out_of_range &e){
            e;
        }

        try{
            std::cout<<"safe_matrix["<<row_h<<"]["<<col_h+1<<"]:"<<safe_matrix[row_h][col_h+1]<<std::endl;
        }
        catch (std::out_of_range &e){
            e;
        }
        try{
            std::cout<<"safe_matrix["<<row_l-1<<"]["<<col_l<<"]:"<<safe_matrix[row_l-1][col_l]<<std::endl;
        }
        catch (std::out_of_range &e){
            e;
        }
        try{
            std::cout<<"safe_matrix["<<row_h+1<<"]["<<col_h<<"]:"<<safe_matrix[row_h+1][col_h]<<std::endl;
        }
        catch (std::out_of_range &e){
            e;
        }
        catch (std::exception &e){
            e;
            std::cout<<"test failed..."<<std::endl;
        }
        std::cout << "test passed!" << std::endl;
    };



    std::cout << std::endl << "================ Testing Safe Matrix class ================" << std::endl;

    ///////////////////////////////////////////////////////////////////////////////////////////////
    std::cout  << std::endl<< ":::::::: Testing empty parameter constructor ::::::::" << std::endl;
    std::cout << "initialising..." << std::endl;
    SafeMatrix<T> safe_matrix_noparam;
    std::cout << "test passed!" << std::endl;


    ///////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << std::endl << ":::::::: Testing two-parameter constructor ::::::::" << std::endl;
    std::cout << "initialising..." << std::endl;
    SafeMatrix<T> safe_matrix_2param(row_size, col_size);
    load_matrix(safe_matrix_2param, 0, row_h-row_l, 0, col_h-col_l);
    read_matrix(safe_matrix_2param, 0, row_h-row_l, 0, col_h-col_l);
    verify_matrix(safe_matrix_2param, 0, row_h-row_l, 0, col_h-col_l);


    ///////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << std::endl << ":::::::: Testing four-parameter constructor ::::::::" << std::endl;
    std::cout << "initialising..." << std::endl;
    SafeMatrix<T> safe_matrix_4param(row_l, row_h, col_l, col_h);
    load_matrix(safe_matrix_4param, row_l, row_h, col_l, col_h);
    read_matrix(safe_matrix_4param, row_l, row_h, col_l, col_h);
    verify_matrix(safe_matrix_4param, row_l, row_h, col_l, col_h);


    ///////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << std::endl << ":::::::: Testing Copy constructor ::::::::" << std::endl;
    std::cout << "initialising with safe_matrix_4param..." << std::endl;
    SafeMatrix<T> safe_matrix_copy(safe_matrix_4param);
    read_matrix(safe_matrix_copy, row_l, row_h, col_l, col_h);
    verify_matrix(safe_matrix_copy, row_l, row_h, col_l, col_h);


    ///////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << std::endl << ":::::::: Testing operator=  ::::::::" << std::endl;
    std::cout << "copying..." << std::endl;
    safe_matrix_2param = safe_matrix_4param;
    safe_matrix_noparam = safe_matrix_2param;
    read_matrix(safe_matrix_noparam, row_l, row_h, col_l, col_h);
    verify_matrix(safe_matrix_noparam, row_l, row_h, col_l, col_h);

    ///////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << std::endl << ":::::::: Testing Bounds Safety  ::::::::" << std::endl;
    std::cout << "initialising..." << std::endl;
    SafeMatrix<T> safe_matrix_bounds(row_l, row_h, col_l, col_h);
    load_matrix(safe_matrix_bounds, row_l, row_h, col_l, col_h);
    check_bounds(safe_matrix_bounds, row_l, row_h, col_l, col_h);
}




#endif //SAFE_MATRIX_SAFE_MATRIX_TEST_H
