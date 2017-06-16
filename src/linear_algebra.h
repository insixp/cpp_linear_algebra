#include <vector>
#include <iostream>
#include "vector_ext.h"
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

//  Functions
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

        MATRIX  base(bool orthogonal){
            vector<vector<MATRIX_TYPE>>     res_vector;
            for(int i = 0; i < this->matrix.size(); i++){
                for(int j = i+1; j < this->matrix.size(); j++){
                    if(linear_dependence(this->matrix[i], this->matrix[j])){
                        goto focused_vec_itr;
                    }
                }
                res_vector.push_back(this->matrix[i]);
                focused_vec_itr:;
            }
            if(!orthogonal){
                MATRIX<MATRIX_TYPE>     res_matrix(res_vector);
                return res_matrix;
            }

            for(int i = 1; i < this->matrix_prop.height; i++){
                for(int j = i-1; j >= 0; j--){
                    res_vector[i]   -= vector_projection(res_vector[j], res_vector[i]);
                }
            }
            MATRIX<MATRIX_TYPE>     res_matrix(res_vector);
            return res_matrix;
        }

        int rank(){
            vector<vector<MATRIX_TYPE>>     tmp_matrix  = this->matrix;
            int rank    = 0;
            for(int i = 0; i < this->matrix.size(); i++){
                for(int j = i+1; j < this->matrix.size(); j++){
                    if(linear_dependence(this->matrix[i], this->matrix[j])){
                        goto focused_vec_itr;
                    }
                }
                rank++;
                focused_vec_itr:;
            }
            return rank;
        }

        int size(){
            return this->matrix_prop.height;
        }

        //  Actions

        void transpose(){
            MATRIX_TYPE     tmp_item;
            for(int i = 0; i < this->matrix_prop.height; i++){
                for(int j = 0; j < this->matrix_prop.width; j++){
                    tmp_item = this->matrix[i][j];
                    this->matrix[i][j]  = this->matrix[j][i];
                    this->matrix[i][j]  = tmp_item;
                }
            }
        }

        MATRIX lower_tringular(){
            vector<MATRIX_TYPE> dec_row;
            MATRIX<MATRIX_TYPE> res_matrix(this->matrix);

            for(int main_row = 0; main_row < this->matrix_prop.height - 1; main_row++){
                for(int i = main_row; i < this->matrix_prop.height - 1; i++){
                    if(res_matrix[main_row][main_row] == 0){
                        vector<MATRIX_TYPE>     tmp_vec;
                        tmp_vec                     = res_matrix[main_row];
                        res_matrix[main_row]        = res_matrix[main_row + 1];
                        res_matrix[main_row + 1]    = tmp_vec;
                    } else {
                        break;
                    }
                }
                res_matrix[main_row]  = (1.0/res_matrix[main_row][main_row])*(res_matrix[main_row]);
                for(int curr_row = main_row + 1; curr_row < this->matrix_prop.height; curr_row++){
                    dec_row                 = (res_matrix[curr_row][main_row])*(res_matrix[main_row]);
                    res_matrix[curr_row]    -= dec_row;
                }
            }
            return res_matrix;
        }

        MATRIX upper_tringular(){
            vector<MATRIX_TYPE> dec_row;
            MATRIX<MATRIX_TYPE> res_matrix(this->matrix);

            for(int main_row = this->matrix_prop.height - 1; main_row > 0; main_row--){
                for(int i = main_row; i > 0; i--){
                    if(res_matrix[main_row][main_row] == 0){
                        vector<MATRIX_TYPE>     tmp_vec;
                        tmp_vec                     = res_matrix[main_row];
                        res_matrix[main_row]        = res_matrix[main_row - 1];
                        res_matrix[main_row + 1]    = tmp_vec;
                    } else {
                        break;
                    }
                }
                res_matrix[main_row]  = (1.0/res_matrix[main_row][main_row])*(res_matrix[main_row]);
                for(int curr_row = main_row - 1; curr_row >= 0; curr_row--){
                    dec_row                 = (res_matrix[curr_row][main_row])*(res_matrix[main_row]);
                    res_matrix[curr_row]    -= dec_row;
                }
            }
            return res_matrix;
        }

        MATRIX diagonalyze(){
            if(this->matrix_prop.height != this->matrix_prop.width)
                throw MATRIX_NOT_SQUARE;
            if(this->matrix_prop.height != this->rank())
                throw MATRNIX_NOT_DIAGONALYZABLE;

            MATRIX<MATRIX_TYPE> res_matrix(this->matrix_prop);
            res_matrix  = this->lower_tringular().upper_tringular();
            return res_matrix; 
        }

        //  Matrix operators
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

        void  operator=(vector<vector<MATRIX_TYPE>> matrix_in) {
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

        void    operator=(MATRIX matrix_in){
            matrix_propetries       matrix_in_prop   = matrix_in.get_matrix_propetries();
            if(this->matrix_prop.height != matrix_in_prop.height || this->matrix_prop.height != matrix_in_prop.width)
                throw BAD_MATRIX_SIZE_EXCEPTION;
            for(int i = 0; i < this->matrix_prop.height; i++){
                this->matrix[i]     = matrix_in[i];
            }
        }

        vector<MATRIX_TYPE> &operator[](const int index){
            return this->matrix[index];
        }        
};

template <class MATRIX_TYPE>
ostream &operator<<(ostream& ost, MATRIX<MATRIX_TYPE> matrix_in){
    for(int i = 0; i < matrix_in.size(); i++){
        ost << matrix_in[i] << endl;
    }
    return ost;
}