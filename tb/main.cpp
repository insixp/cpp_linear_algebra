#include <iostream>
#include "../src/linear_algebra.h"

using namespace std;


int main(){

    MATRIX<float>   matrix_a(2, 2);
    // vector<vector<float>>   a {{1, 0}, {0, 1}};
    matrix_a        = {{1, 0}, {0, 1}};
    matrix_a.print_matrix();
    MATRIX<float>   matrix_b(2, 3);

    matrix_a + matrix_b;
    matrix_b + matrix_a;

    return 0;
}