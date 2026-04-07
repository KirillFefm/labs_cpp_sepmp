#include "interface_vector.hpp"

template<typename T>
class Matrix {
    subvector<T> data;
    unsigned _cols, _rows;

public:
    Matrix(unsigned rows, unsigned cols, T value = 0);
    static Matrix Identity(unsigned n);
    static Matrix getSpecificDeterminant(unsigned n, T determinant);
    
    unsigned rows() const;
    unsigned cols() const;
    T& operator()(unsigned row, unsigned col);
    T operator()(unsigned row, unsigned col) const;
    
    Matrix& transpose();
    Matrix transposed() const;
    void swapRows(unsigned i, unsigned j);
    void multiplyRow(unsigned i, T factor);
    void addRow(unsigned i, unsigned j, T factor);
    static Matrix multiply(const Matrix& A, const Matrix& B);
    subvector<T> operator*(const subvector<T>& vec) const;
};

template<typename T> T determinant(const Matrix<T>& mat);
template<typename T> subvector<T> gaussianElimination(Matrix<T> A, subvector<T> b);