#include <iostream>
#include "../src/linear_algebra.h"

using namespace std;


int main(){

    MATRIX<float>   my_matrix(2, 5);
    //my_matrix.print_matrix();
    matrix_propetries matrix_prop = {2, 3};
    matrix_index matrix_in = {0, 0};
    MATRIX<float> res_matrix    = my_matrix.get_sub_matrix(matrix_prop, matrix_in);
    res_matrix.print_matrix();
    return 0;
}