#include <iostream>
#include "../src/linear_algebra.h"

using namespace std;


int main(){

    MATRIX<float>   matrix_a({{1, 1}, {3, 1}});
    MATRIX<float>   matrix_b({{2, 0, 2}, {0, 2, 2}});
    // MATRIX<float>   c = matrix_a + matrix_b;
    cout << matrix_a.rank() << endl;

    return 0;
}