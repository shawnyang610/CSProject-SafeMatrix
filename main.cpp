// SafeMatrix: A templatized matrix class with bound check and arithmetics functionality.
// Author: Shawn Yang
// 9/23/2018

#include "tests.hpp"
#include <iostream>
using namespace std;
const int ROW_L = 5;
const int ROW_H = 10;
const int COL_L = 0;
const int COL_H = 2;



int main() {
    int row_l = ROW_L;
    int row_h = ROW_H;
    int col_l = COL_L;
    int col_h = COL_H;

    std::cout<<"run default test? y/n ";
    char input;
    std::cin>>input;
    if (input=='n'){
        std::cout<<std::endl<<"enter row lower bound:";
        std::cin>>row_l;
        std::cout<<std::endl<<"enter row uppper bound:";
        std::cin>>row_h;
        std::cout<<std::endl<<"enter column lower bound:";
        std::cin>>col_l;
        std::cout<<std::endl<<"enter column uppper bound:";
        std::cin>>col_h;
    }

    test_safe_matrix<int>(row_l, row_h, col_l, col_h);

    test_VNT();



    VNT a(5,6);

    for(int i=0;i<31;i++){
        a.add(i*i);
    }
    if(a.find(25)){
        cout<<"Found 25 int VNT table\n";
    }
    if(!a.find(26)){
        cout<<"26 is not in the VNT table\n";
    }
    cout<<"The minimum value in VNT table is: "<<a.getMin()<<endl;

    int arr[10]= {2,6,9,0,3,1,8,4,7,5};
    cout<<"Unsorted array is:\n";
    for(auto e:arr)
        cout<<e<<" ";
    cout<<endl;

    a.sort(arr,10);
    cout<<"Sorted Array is:\n";
    for(auto e:arr)
        cout<<e<<" ";
    cout<<endl;

    return 0;
}