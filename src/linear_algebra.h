#include <vector>
#include <iostream>
#include "errors.h"

using namespace std;

//  Structs
typedef struct {
    int         height;
    int         width;
}   matrix_propetries;

typedef struct {
    int     x_index;
    int     y_index;
}   matrix_index;

//  Class
template <class MATRIX_TYPE>
class MATRIX
{
    private:
        const matrix_propetries             matrix_prop;
        vector<vector<MATRIX_TYPE>>         matrix;

    public:

        //  Constructor
        MATRIX();

        MATRIX(const matrix_propetries matrix_prop) : matrix_prop(matrix_prop){
            //  Initiate matrix with zeros
            this->matrix.resize(this->matrix_prop.height);
            for(int i = 0; i < this->matrix_prop.height; i++){
                this->matrix[i].resize(this->matrix_prop.width, (MATRIX_TYPE)0);
            }
        }

        MATRIX(const int width, const int height) : matrix_prop({height, width}){
            //  Initiate matrix with zeros
            this->matrix.resize(this->matrix_prop.height);
            for(int i = 0; i < this->matrix_prop.height; i++){
                this->matrix[i].resize(this->matrix_prop.width, (MATRIX_TYPE)0);
            }
        }

        MATRIX(const vector<vector<MATRIX_TYPE>>    matrix_in) : matrix_prop({matrix_in.size(), matrix_in[0].size()}){
            //  Both checks are for when the matrix width is not the same so we check its the same.
            if(matrix_in.size() != this->matrix_prop.height){
                throw BAD_MATRIX_SIZE_EXCEPTION;
            }
            for(int i = 0; i < this->matrix_prop.height; i++){
                if(matrix_in[i].size() != this->matrix_prop.width){
                    throw BAD_MATRIX_SIZE_EXCEPTION;
                }
            }
            this->matrix        = matrix_in;
        }

        //  Get functions
        matrix_propetries   get_matrix_propetries(){
            return this->matrix_prop;
        }

        MATRIX_TYPE get_index(matrix_index matrix_index){
            return this->matrix[matrix_index.x_index][matrix_index.y_index];
        }

        MATRIX get_sub_matrix(matrix_propetries matrix_prop, matrix_index matrix_in){

            //  Init variables
            MATRIX                          res_matrix_class(matrix_prop);
            vector<MATRIX_TYPE>             curr_vec;
            vector<vector<MATRIX_TYPE>>     res_matrix;

            //  Setting res_matrix size
            res_matrix.resize(matrix_prop.height);
            for(int i = 0; i < matrix_prop.height; i++){
                res_matrix[i].resize(matrix_prop.width, (MATRIX_TYPE)0);
            }


            //  Setting tmp vector
            for(int i = matrix_prop.height; i < matrix_prop.height + matrix_in.y_index; i++){
                vector<MATRIX_TYPE>     curr_vec(this->matrix[i].begin() + (matrix_in.x_index), this->matrix[i].begin() + (matrix_in.x_index + matrix_prop.width));
                res_matrix[i]           = curr_vec;
            }
            res_matrix_class.set_matrix_vectors(res_matrix);
            return res_matrix_class;
        }

        int     rank(){

        }

        void    print_matrix(){
            for(int i = 0; i < this->matrix_prop.height; i++){
                for(int j = 0; j < this->matrix_prop.width; j++){
                    if(j == 0)
                        cout << "[";
                    if(j == this->matrix_prop.width - 1)
                        cout << this->matrix[i][j] << "]";
                    else
                        cout << this->matrix[i][j] << ", ";
                }
                cout << endl;
            }
        }

        //  Set functions
        void set_index(matrix_index matrix_index, MATRIX_TYPE value){
            this->matrix[matrix_index.x_index][matrix_index.y_index]    = value;
        }

        void operator=(const vector<vector<MATRIX_TYPE>> matrix_in){
            if(matrix_in.size() != this->matrix_prop.height){
                throw BAD_MATRIX_SIZE_EXCEPTION;
            }
            for(int i = 0; i < this->matrix_prop.height; i++){
                if(matrix_in[i].size() != this->matrix_prop.width){
                    throw BAD_MATRIX_SIZE_EXCEPTION;
                }
            }     
            for(int i = 0; i < this->matrix_prop.height; i++){
                for(int j = 0; j < this->matrix_prop.width; j++){
                    this->matrix[i][j]     = matrix_in[i][j];
                }
            }
        }

        vector<MATRIX_TYPE> &operator[](const int index){
            return this->matrix[index];
        }

        //  Matrix addition
        // template<class MATRIX_T>
        MATRIX operator+(MATRIX matrix_b) {
            matrix_propetries matrix_b_prop     = matrix_b.get_matrix_propetries();
            if(matrix_b_prop.height != this->matrix_prop.height || matrix_b_prop.width != this->matrix_prop.width){
                throw BAD_MATRIX_SIZE_EXCEPTION;
            }
            MATRIX     res_matrix(this->matrix_prop.width, this->matrix_prop.height);
            for(int i = 0; i < this->matrix_prop.height; i++){
                for(int j = 0; j < this->matrix_prop.width; j++){
                    res_matrix[i][j]    = matrix_b[i][j] + this->matrix[i][j];
                }
            }
            return res_matrix;
        }

        MATRIX operator*(MATRIX matrix_b) {
            matrix_propetries matrix_b_prop     = matrix_b.get_matrix_propetries();
            if(matrix_b_prop.height != this->matrix_prop.width){
                throw BAD_MATRIX_SIZE_EXCEPTION;
            }
            MATRIX     res_matrix(matrix_b_prop.width, this->matrix_prop.height);
            for(int i = 0; i < this->matrix_prop.height; i++){
                for(int j = 0; j < matrix_b_prop.width; j++){
                    for(int k = 0; k < this->matrix_prop.width; k++){
                        res_matrix[i][j]    += this->matrix[i][k] * matrix_b[k][j];
                    }
                }
            }
            return res_matrix;
        }
};

template <class VECTOR_TYPE>
bool linear_independence (vector<VECTOR_TYPE> vector_a, vector<VECTOR_TYPE> vector_b){
    if(vector_a.size() != vector_b.size())
        return false;
    VECTOR_TYPE     lambda  = vector_a[0]   / vector_b[0];
    for(int i = 1; i < vector_a.size(); i++){
        if(vector_a[i] / vector_b[i]    != lambda)
            return false;
    }
    return true;
}

template <class MATRIX_TYPE>
MATRIX<MATRIX_TYPE> Diagonalize(MATRIX<MATRIX_TYPE> matrix_in, MATRIX<MATRIX_TYPE> *diagonalizing){

}