#include <iostream>
#include "../src/linear_algebra.h"

using namespace std;


int main(){

    MATRIX<float>   matrix_a({{1, 0}, {0, 1}});
    MATRIX<float>   matrix_b({{2, 0}, {0, 2}});
    MATRIX<float>   c = matrix_a + matrix_b;

    return 0;
}