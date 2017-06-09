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

        vector<MATRIX_TYPE>  get_matrix_row(int index){
            vector<MATRIX_TYPE>     res_vector;
            res_vector.resize(this->matrix_prop.width);
            for(int i = 0; i < this->matrix_prop.width; i++){
                res_vector[i]       = this->matrix[i][index];
            }
            return res_vector;
        }

        vector<MATRIX_TYPE>  get_matrix_col(int index){
            return this->matrix[index];
        }

    public:

        //  Constructor
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

        //  Get functions
        matrix_propetries   get_matrix_propetries(){
            return this->matrix_prop;
        }

        void    print_matrix(){
            cout << this->matrix[0][0] << endl;
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

        //  Set functions
        MATRIX operator=(const vector<vector<MATRIX_TYPE>> matrix_in){
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
            print_matrix();
        }

        //  Matrix addition
        // template<class MATRIX_T>
        MATRIX operator+(MATRIX &matrix_b) {
            print_matrix();
            return matrix_b;
        }
};