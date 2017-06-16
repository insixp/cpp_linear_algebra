#include <iostream>
#include "../src/linear_algebra.h"

using namespace std;


int main(){

    MATRIX<float>       matrix_a({{2, 3, 2}, {1, 2, 3}, {2, 3, 2}});
    cout << matrix_a << endl;

    cout << matrix_a.lower_tringular() << endl;

    return 0;
}