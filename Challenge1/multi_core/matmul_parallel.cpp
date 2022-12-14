#include <time.h>
#include <iostream>
#include "omp.h"

// generate random int or float matrix
template <class M>
M** matrix_gen(int size){
    time_t t;
    srand((unsigned)time(&t));
    M** matrix = new M*[size];
    for(int i=0;i<size;i++){
        matrix[i]=new M[size];
        for (int j=0;j<size;j++){
            matrix[i][j]=static_cast<M>(rand())/static_cast<M>(RAND_MAX/100);
        }
    }
    return matrix;
}
template int** matrix_gen<int>(int size);
template float** matrix_gen<float>(int size);

// generate 0 int or float matrix
template <class M>
M** matrix_gen_zero(int size){
    M** matrix = new M*[size];
    for(int i=0;i<size;i++){
        matrix[i]=new M[size];
        for (int j=0;j<size;j++){
            matrix[i][j]=static_cast<M>(0);
        }
    }
    return matrix;
}
template int** matrix_gen_zero<int>(int size);
template float** matrix_gen_zero<float>(int size);

// matrix multiplication
/*
template<class M>
M** mat_mult(M** a, M** b, int size){
    M** c = new M*[size];
    for (int i=0;i<size;i++){
        c[i] = new M[size];
        for (int j=0;j<size;j++){
            c[i][j]=0;
            for (int k=0;k<size;k++)
            {
                c[i][j]+=a[i][k]*b[k][j];
            }
        }
    }
    return c;
}
template int** mat_mult<int>(int **a, int **b, int size);
template float** mat_mult<float>(float**a, float**b, int size);*/

// matrix multiplication benchmark
template<class M>
double mat_mult_timing(M** a, M** b, int size, int num){
    // initialise the result matrix 
    M** c = matrix_gen_zero<M>(size);
    double initial = omp_get_wtime();
#pragma omp parallel num_threads(num)
#pragma omp for collapse(3)
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    double final = omp_get_wtime();
    double duration = final - initial;
    return duration; 
}
template double mat_mult_timing<int>(int **a, int **b, int size, int num);
template double mat_mult_timing<float>(float**a, float**b, int size, int num);

// print out the matrix for debugging
/*template<class M>
void printMatrix(M** matrix, int size){
    for (int i=0;i<size;i++){
        for(int j=0;j<size;j++)
            std::cout<<matrix[i][j]<<"\t";
        std::cout<<"\n";
    } 
}
template void printMatrix<int>(int** matrix, int size);
template void printMatrix<float>(float** matrix, int size);
*/

int main(int argc, char* argv[]){
    long long n = atoi(argv[1]);  
    int num = atoi(argv[2]);
    /*
    int** matrix = matrix_gen<int>(size);
    printMatrix<int>(matrix, size);
    float** matrix2 = matrix_gen<float>(size);
    printMatrix<float>(matrix2,size);
    int** c1 = mat_mult<int>(matrix,matrix, size);
    printMatrix<int>(c1, size);
    float** c2 = mat_mult<float>(matrix2, matrix2, size);
    printMatrix<float>(c2,size); 
    */
    /*int** matrix = matrix_gen<int>(n);
    float duration = mat_mult_timing<int>(matrix, matrix, n);
    std::cout<<"int time "<<duration<<"\n";
    // there are 2n^3-n^2 operations in this matrix multiplication
    std::cout<<"int operations "<<(static_cast<float>((2*n*n*n-n*n))/duration)<<"\n";
    delete matrix; 
    */
    float **matrixF = matrix_gen<float>(n);
    double duration = mat_mult_timing<float>(matrixF, matrixF, n, num);
    std::cout<<"Multicore float time "<<duration<<" s for "<<num<<"threads\n";
    std::cout<<"FLOPs "<<(static_cast<float>((2*n*n*n-n*n))/duration)<<"\n";
    delete matrixF;

    return 1;
}