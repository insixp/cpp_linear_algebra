#include <vector>
#include <math.h>
#include <iomanip>
#include "errors.h"

using namespace std;


template <class VECTOR_TYPE>
bool linear_dependence (vector<VECTOR_TYPE> vector_a, vector<VECTOR_TYPE> vector_b){
    if(vector_a.size() != vector_b.size())
        throw BAD_VECTOR_SIZE_EXCEPTION;
    VECTOR_TYPE lambda  = vector_a[0]   / vector_b[0];
    for(int i = 1; i < vector_a.size(); i++){
        if(!vector_a[i] || !vector_b[i]){
            if(vector_a[i] != vector_b[i])
                return false;
        } else {
            if(vector_a[i] / vector_b[i]    != lambda)
                return false;
        }
    }
    return true;
}

template <class VECTOR_TYPE>
VECTOR_TYPE inner_product(vector<VECTOR_TYPE> vector_a, vector<VECTOR_TYPE> vector_b){
    VECTOR_TYPE     inner_product   = 0;

    if(vector_a.size() != vector_b.size())
        throw BAD_VECTOR_SIZE_EXCEPTION;

    for(int i = 0; i < vector_a.size(); i++){
            //   Not hermitian -> TBD;
            inner_product   += vector_a[i] * vector_b[i];
    }
    return inner_product;
}


template <class VECTOR_TYPE>
bool orthogonal (vector<VECTOR_TYPE> vector_a, vector<VECTOR_TYPE> vector_b){
    return inner_product(vector_a, vector_b) == 0;
}

template <class VECTOR_TYPE>
VECTOR_TYPE   norm(vector<VECTOR_TYPE> vector_a){
    return sqrt(inner_product(vector_a, vector_a));
}

template <class VECTOR_TYPE>
vector<VECTOR_TYPE> vector_projection(vector<VECTOR_TYPE> vector_a, vector<VECTOR_TYPE> vector_b){
    vector<VECTOR_TYPE>    projection_vec;

    return ((inner_product(vector_b, vector_a)/(pow(norm(vector_a), 2))) *  vector_a);
}


//  Operators overloading.
template <class SCALAR_TYPE, class VECTOR_TYPE>
vector<VECTOR_TYPE> operator*(SCALAR_TYPE scalar, vector<VECTOR_TYPE> vec_a){
    for(int i = 0; i < vec_a.size(); i++){
        vec_a[i]    *= scalar;
    }
    return vec_a;
}
template <class VECTOR_TYPE, class SCALAR_TYPE>
vector<VECTOR_TYPE> operator*(vector<VECTOR_TYPE> vec_a, SCALAR_TYPE scalar){
    for(int i = 0; i < vec_a.size(); i++){
        vec_a[i]    *= scalar;
    }
    return vec_a;
}

template <class VECTOR_TYPE>
void operator-=(vector<VECTOR_TYPE> &vec_a, vector<VECTOR_TYPE> vec_b){
    // vector<VECTOR_TYPE>     res_vec = vec_a;
    for(int i = 0; i < vec_a.size(); i++){
        vec_a[i]    -= vec_b[i];
    }
}

template <class VECTOR_TYPE>
ostream& operator<<(ostream& ost, vector<VECTOR_TYPE> vec_a){
    for(int i = 0; i < vec_a.size(); i++){
        if(i == 0)
            ost << "(";
        if(i == vec_a.size() - 1){
            ost << vec_a[i] << ")";
        } else{
            if(i == 0){
                ost << vec_a[i] << ", ";
            } else {
                ost << vec_a[i] << ", ";
            }
        }
    }
    return ost;
}