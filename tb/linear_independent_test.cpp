#include <iostream>
#include "../src/linear_algebra.h"

using namespace std;


int main(){

    vector<float>       a = {1,2,3,4,5};
    vector<float>       b = {2,4,6,8,10};
    cout << linear_independence(a, b) << endl;

    return 0;
}