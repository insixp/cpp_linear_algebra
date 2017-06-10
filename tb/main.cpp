#include <iostream>
#include "../src/linear_algebra.h"

using namespace std;


int main(){

    MATRIX<float>       matrix_a({{1, 2, 3}, {1, 1, 1}, {2, 3, 2}});

    cout << fixed << setprecision(3) << matrix_a.base(1) << endl;

    return 0;
}