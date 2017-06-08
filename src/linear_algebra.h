#include <vector>
#include <iostream>

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
        MATRIX(const matrix_propetries matrix_prop) : matrix_prop(matrix_prop)
        {
            //  Initiate matrix with zeros
            this->matrix.resize(this->matrix_prop.height);
            for(int i = 0; i < this->matrix_prop.height; i++){
                this->matrix[i].resize(this->matrix_prop.width, (MATRIX_TYPE)0);
            }
        }

        MATRIX(const int height, const int width) : matrix_prop({width, height})
        {
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
            for(int i = 0; i < this->matrix_prop.height; i++){
                for(typename vector<MATRIX_TYPE>::const_iterator j = this->matrix[i].begin(); j < this->matrix[i].end(); j++){
                    if(j == this->matrix[i].begin())
                        cout << "[";
                    if(j == this->matrix[i].end() - 1)
                        cout << *j << "]";
                    else
                        cout << *j << ", ";
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

        void set_matrix_vectors(vector<vector<MATRIX_TYPE>> matrix_in){
            this->matrix        = matrix_in;
        }
};