#include <iostream>
#include "../src/linear_algebra.h"

using namespace std;


int main(){

    MATRIX<float>       matrix_a({{1, 0, 3}, {1, 0, 3}});
    MATRIX<float>       a_base  = matrix_a.base(0);
    a_base.print_matrix();

    return 0;
}