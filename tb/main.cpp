#include <iostream>
#include "../src/linear_algebra.h"

using namespace std;


int main(){

    MATRIX<float>       matrix_a({{1, 1, 1}, {1, 1, 0}, {1, 0, 0}});
    cout << matrix_a.diagonalyze() << endl;

    return 0;
}