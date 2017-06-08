#include <vector>

using namespace std;

template <class MATRIX_TYPE, int WIDTH, int HEIGHT>
class MATRIX
{
    private:
        vector<vector<matrix_type>>     matrix;

    public:
        MATRIX(){
            //  Initiate matrix with zeros
            matrix.resize(HEIGHT);
            for(int i = 0; i < HEIGHT; i++){
                matrix[i].resize(WIDTH, (MATRIX_TYPE)0);
            }
        }
}