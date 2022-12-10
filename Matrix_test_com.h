//#ifndef MATRIX_TEST_H__
//
//#define MATRIX_TEST_H__
//#include <Windows.h>
//
//#include <stdexcept>
//#include <iostream>
//#include <fstream>
//#include <string>
//
//using T = char;
//using pointer_type = T*;
//
//
//struct Coordinates {
//	size_t i;
//	size_t j;
//
//	//size_t& x = i;
//	//size_t& y = j;
//};
//
//
//class Matrix {
//private:
//	size_t N;
//	size_t M;
//	T** arr; //T** arr = nullptr;
//	//int crt_cntr = 0;
//
//
//	static T** allocate(size_t N, size_t M);
//private:
//	struct str_i {
//		Matrix& my_matrix;
//		size_t i;
//
//		str_i(Matrix& m, size_t i) : my_matrix(m), i(i) {
//			//str_i::i = i;
//		}
//
//		T& operator[](size_t j) {
//			return my_matrix.arr[i][j];
//		}
//	};
//
//	struct const_str_i {
//		const Matrix& my_matrix;
//		size_t i;
//
//		const_str_i(const Matrix& m, size_t i) : my_matrix(m), i(i) {
//			//str_i::i = i;
//		}
//
//		const T& operator[](size_t j) const {
//			return my_matrix.arr[i][j];
//		}
//	};
//public:
//	Matrix();
//
//	//Matrix(size_t N, size_t M, const T& value = T());
//	Matrix(size_t N, size_t M);
//	Matrix(size_t N, size_t M, const T& value);
//
//	Matrix(const Matrix& other);
//	~Matrix();
//
//
//	void resize(size_t N_, size_t M_);
//
//	Matrix& operator=(const Matrix& other);
//
//	str_i operator[](size_t i);
//	const_str_i operator[](size_t i) const;
//
//	size_t get_N() const;
//	size_t get_M() const;
//
//	//после всех
//	//void resize(size_t strings, size_t columns, const T& value = T());
//	//void resize(size_t strings, size_t columns);
//	//void resize(size_t strings, size_t columns, const T& value);
//
//	void fill(const T& value);
//
//	bool is_empty();
//
//	void print() const;
//	void print(std::ofstream& output) const;
//	void print(std::ostream& output) const;
//
//	void set_at(const size_t N, const size_t M, const T& data);
//	void set_at(Coordinates cell, const T& data);
//
//	T& get_at(size_t N, size_t M);
//	T& get_at(Coordinates cell);
//
//	const T& get_at(size_t N, size_t M) const;
//	const T& get_at(Coordinates cell) const;
//
//	void clear();
//
//};
//
//#endif //! MATRIX_TEST_H__
//
