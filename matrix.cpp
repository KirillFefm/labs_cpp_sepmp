#include <iostream>
#include <random>
#include <chrono>
#include <cmath>
#include "interface_vector.cpp"

template<typename T>
class Matrix {
	subvector<T> data;
	unsigned _cols, _rows;

public:
	Matrix(unsigned rows, unsigned cols, T value = 0) : _rows(rows), _cols(cols) {
		// это логичнее загнать в конструктор вектора по одинаковому значению для заданого размера
		for(unsigned i = 0; i < rows * cols; i++){
			data.push_back(value);
		}
	}

	static Matrix Identity(unsigned n){
		Matrix m(n, n, 0);
		for(unsigned i = 0; i < n; i++){
			m(i, i) = 1;  // 1 -- это тип int, а не Т, надо использовать явное приведение
		}
		return m;
	}

	static Matrix getSpecificDeterminant(unsigned n, T determinant){
		std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
		std::uniform_real_distribution<double> dis(-10.0, 10.0);
		
		Matrix L = Identity(n);
		Matrix U = Identity(n);
		
		for(unsigned i = 0; i < n; i++){
			for(unsigned j = i + 1; j < n; j++){
				L(j, i) = dis(gen);
			}
		}
		
		for(unsigned i = 0; i < n; i++){
			for(unsigned j = i + 1; j < n; j++){
				U(i, j) = dis(gen);
			}
		}
		
		double diag_prod = 1.0;
		for(unsigned i = 0; i < n - 1; i++){
			double val = dis(gen);
			if(std::abs(val) < 0.1) val = 1.0;
			U(i, i) = val;
			L(i, i) = 1.0;
			diag_prod *= val;
		}
		U(n-1, n-1) = determinant / diag_prod;
		L(n-1, n-1) = 1.0;
		
		return multiply(L, U);
	}

	unsigned rows() const { return _rows; }
	unsigned cols() const { return _cols; }

	T& operator()(unsigned row, unsigned col){
		return data[row * _cols + col];
	}

	T operator()(unsigned row, unsigned col) const {
		return data[row * _cols + col];
	}

// Тут один метод можно определить через другой
	Matrix& transpose(){
		Matrix temp(_cols, _rows);
		for(unsigned i = 0; i < _rows; i++){
			for(unsigned j = 0; j < _cols; j++){
				temp(j, i) = (*this)(i, j);
			}
		}
		*this = temp;
		return *this;
	}

	Matrix transposed() const {
		Matrix temp(_cols, _rows);
		for(unsigned i = 0; i < _rows; i++){
			for(unsigned j = 0; j < _cols; j++){
				temp(j, i) = (*this)(i, j);
			}
		}
		return temp;
	}

	void swapRows(unsigned i, unsigned j){
		for(unsigned k = 0; k < _cols; k++){
			T temp = (*this)(i, k);
			(*this)(i, k) = (*this)(j, k);
			(*this)(j, k) = temp;
		}
	}

	void multiplyRow(unsigned i, T factor){
		for(unsigned k = 0; k < _cols; k++){
			(*this)(i, k) *= factor;
		}
	}

	void addRow(unsigned i, unsigned j, T factor){
		for(unsigned k = 0; k < _cols; k++){
			(*this)(i, k) += (*this)(j, k) * factor;
		}
	}

// А вот это было бы неплохо сделать оператором умножения для двух матриц
	static Matrix multiply(const Matrix& A, const Matrix& B){
		// нет проверки на соотвествие размеров
		Matrix result(A._rows, B._cols, 0);
		for(unsigned i = 0; i < A._rows; i++){
			for(unsigned j = 0; j < B._cols; j++){
				for(unsigned k = 0; k < A._cols; k++){
					result(i, j) += A(i, k) * B(k, j);
				}
			}
		}
		return result;
	}

	subvector<T> operator*(const subvector<T>& vec) const {
		subvector<T> result;
		// Нет проверки на соотвествие размеров
		for(unsigned i = 0; i < _rows; i++){
			T sum = 0;
			for(unsigned j = 0; j < _cols; j++){
				sum += (*this)(i, j) * vec[j];
			}
			result.push_back(sum);		// плохая идея без использования resize перед использованием. можно попасть на много перевыделений памяти. так что сначала нужно выделить достуточное количество памяти
		}
		return result;
	}
};

template<typename T>
T determinant(const Matrix<T>& mat){
	unsigned n = mat.rows();
	Matrix<T> m = mat;
	T det = 1;
	
	for(unsigned i = 0; i < n; i++){
		unsigned pivot = i;
		for(unsigned j = i + 1; j < n; j++){
			if(std::abs(m(j, i)) > std::abs(m(pivot, i))){
				pivot = j;
			}
		}
		
		if(std::abs(m(pivot, i)) < 1e-10){
			return 0;
		}
		
		if(pivot != i){
			m.swapRows(i, pivot);
			det = -det;
		}
		
		det *= m(i, i);
		
		for(unsigned j = i + 1; j < n; j++){
			T factor = m(j, i) / m(i, i);
			// так вроде бы для этого был написан отдельный метод addRow выше?
			for(unsigned k = i; k < n; k++){
				m(j, k) -= factor * m(i, k);
			}
		}
	}
	
	return det;
}

template<typename T>
subvector<T> gaussianElimination(Matrix<T> A, subvector<T> b){
	unsigned n = A.rows();
	
	for(unsigned i = 0; i < n; i++){
		unsigned pivot = i;
		for(unsigned j = i + 1; j < n; j++){
			if(std::abs(A(j, i)) > std::abs(A(pivot, i))){
				pivot = j;
			}
		}
		
		if(pivot != i){
			A.swapRows(i, pivot);
			T temp = b[i];
			b[i] = b[pivot];
			b[pivot] = temp;
		}
		
		for(unsigned j = i + 1; j < n; j++){
			T factor = A(j, i) / A(i, i);
			for(unsigned k = i; k < n; k++){
				A(j, k) -= factor * A(i, k);
			}
			b[j] -= factor * b[i];
		}
	}

	
	subvector<T> x;
	// про push_back без resize смотри выше
	// а вообще это должен быть консруктор от рамера и значения, которым будет заполнен вектор
	for(unsigned i = 0; i < n; i++){
		x.push_back(0);
	}
	
	for(int i = n - 1; i >= 0; i--){
		T sum = b[i];
		for(unsigned j = i + 1; j < n; j++){
			sum -= A(i, j) * x[j];
		}
		x[i] = sum / A(i, i);
	}
	
	return x;
}

template<typename T>
T vectorNorm(const subvector<T>& vec){
	T sum = 0;
	for(unsigned i = 0; i < vec.size(); i++){
		sum += vec[i] * vec[i];
	}
	return std::sqrt(sum);
}

// а это оператор вычитания двух векторов, и надо было так и сделать
template<typename T>
subvector<T> vectorSubtract(const subvector<T>& a, const subvector<T>& b){
	subvector<T> result;
	for(unsigned i = 0; i < a.size(); i++){
		result.push_back(a[i] - b[i]);
	}
	return result;
}

int main() {
	std::cout << std::fixed;
	std::cout.precision(6);
	
	std::cout << "=== Test 1: 5x5 matrix ===" << std::endl;
	Matrix<double> m5 = Matrix<double>::getSpecificDeterminant(5, 100.0);
	double det5 = determinant(m5);
	std::cout << "Determinant: " << det5 << std::endl;
	Matrix<double> m5t = m5.transposed();
	double det5t = determinant(m5t);
	std::cout << "Determinant of transposed: " << det5t << std::endl;
	std::cout << "Difference: " << std::abs(det5 - det5t) << std::endl << std::endl;
	
	std::cout << "=== Test 2: 50x50 matrix ===" << std::endl;
	Matrix<double> m50 = Matrix<double>::getSpecificDeterminant(50, 1000.0);
	double det50 = determinant(m50);
	std::cout << "Determinant: " << det50 << std::endl;
	Matrix<double> m50t = m50.transposed();
	double det50t = determinant(m50t);
	std::cout << "Determinant of transposed: " << det50t << std::endl;
	std::cout << "Difference: " << std::abs(det50 - det50t) << std::endl << std::endl;
	
	std::cout << "=== Test 3: 200x200 matrix ===" << std::endl;
	Matrix<double> m200 = Matrix<double>::getSpecificDeterminant(200, 10000.0);
	double det200 = determinant(m200);
	std::cout << "Determinant: " << det200 << std::endl;
	Matrix<double> m200t = m200.transposed();
	double det200t = determinant(m200t);
	std::cout << "Determinant of transposed: " << det200t << std::endl;
	std::cout << "Difference: " << std::abs(det200 - det200t) << std::endl << std::endl;
	
	std::cout << "=== Gaussian elimination test ===" << std::endl;
	std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<double> dis(-10.0, 10.0);
	
	unsigned n = 100;
	Matrix<double> A(n, n);
	for(unsigned i = 0; i < n; i++){
		for(unsigned j = 0; j < n; j++){
			A(i, j) = dis(gen);
		}
	}
	
	subvector<double> b;
	for(unsigned i = 0; i < n; i++){
		b.push_back(dis(gen));
	}
	
	subvector<double> x = gaussianElimination(A, b);
	subvector<double> Ax = A * x;
	subvector<double> residual = vectorSubtract(Ax, b);
	double norm = vectorNorm(residual);
	
	std::cout << "System size: " << n << "x" << n << std::endl;
	std::cout << "Residual norm ||Ax - b||: " << norm << std::endl;
	
	return 0;
}
