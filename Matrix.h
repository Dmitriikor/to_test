#ifndef MATRIX_TEMPLATE_H__

#define MATRIX_TEMPLATE_H__
 


#include <Windows.h>
#include <stdexcept>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>

//using T = char;
//using pointer_type = T*;


struct Coordinates {
	size_t i;
	size_t j;

};

template <typename T>
class Matrix {
private:
	size_t N;
	size_t M;
	T** arr; 
	static T** allocate(size_t N, size_t M);

private:

	template <class str_i_T>
	struct  str_i {
		Matrix& my_matrix;
		size_t i;

		str_i(Matrix& m, size_t i) : my_matrix(m), i(i) {
		}

		T& operator[](size_t j) {
			return my_matrix.arr[i][j];
		}
	};

	template <class const_str_i_T>
	struct  const_str_i {
		const Matrix& my_matrix;
		size_t i;

		const_str_i(const Matrix& m, size_t i) : my_matrix(m), i(i) {
		}

		const T& operator[](size_t j) const {
			return my_matrix.arr[i][j];
		}
	};
public:
	Matrix();
	Matrix(size_t N, size_t M);
	Matrix(size_t N, size_t M, const T& value);
	Matrix(const Matrix& other);
	~Matrix();


	Matrix& operator=(const Matrix& other);

	template <typename T>
	Matrix<T>::str_i Matrix<T>::operator[](size_t i);
	template <typename T>
	Matrix<T>::str_i Matrix<T>::operator[](size_t i) const;

	//str_i operator[](size_t i);
	//const_str_i operator[](size_t i) const;

	size_t get_N() const;

	size_t get_M() const;

	void resize(size_t N_, size_t M_);

	//после всех
	//void resize(size_t strings, size_t columns, const T& value = T());
	//void resize(size_t strings, size_t columns);
	//void resize(size_t strings, size_t columns, const T& value);

	void fill(const T& value);

	bool is_empty();

	void print() const;
	void print(std::ofstream& output) const;
	void print(std::ostream& output) const;

	void set_at(const size_t N, const size_t M, const T& data);
	void set_at(Coordinates cell, const T& data);

	T& get_at(size_t N, size_t M);
	T& get_at(Coordinates cell);

	const T& get_at(size_t N, size_t M) const;
	const T& get_at(Coordinates cell) const;

	void clear();

};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Matrix_v1_start
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
Matrix<T>::Matrix() : N(0), M(0), arr(nullptr)
{

}
template <typename T>
Matrix<T>::Matrix(size_t N, size_t M) : N(N), M(M)
{
	if (N == 0 || M == 0)
	{
		//!!set_empty
		N = M = 0;
		arr = nullptr;
		return;
	}

	arr = allocate(N, M);
}
template <typename T>
void Matrix<T>::resize(size_t N_, size_t M_)
{
	T** new_arr;
	new_arr = allocate(N_, M_);

	int min_N_lim = N;
	if (N_ < N) min_N_lim = N_;
	int min_M_lim = M;
	if (M_ < M) min_M_lim = M_;

	std::cout << "\n";
	for (size_t i = 0; i < min_N_lim; i++)
	{

		for (size_t j = 0; j < min_M_lim; j++)
		{
			new_arr[i][j] = arr[i][j];

		}
	}
	clear();
	N = N_;
	M = M_;
	arr = new_arr;
}
template <typename T>
Matrix<T>::Matrix(const Matrix& other) : N(other.N), M(other.M)
{
	if (N == 0) 
	{
		arr = nullptr;
		return;
	}

	arr = allocate(N, M);
	//!!! copy-function
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			arr[i][j] = other.arr[i][j];
		}
	}
}
template <typename T>
Matrix<T>::~Matrix()
{
	clear();
}
template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other)
{
	if (this != &other)
	{
		clear();

		if (other.arr != nullptr)
		{
			N = other.N;
			M = other.M;

			arr = allocate(N, M);

			//!!! copy-function
			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < M; j++)
				{
					arr[i][j] = other.arr[i][j];
				}
			}
		}
	}

	return *this;
}


template <typename T>
template <class str_i_T>
Matrix<T>::str_i Matrix<T>::operator[](size_t i) {
	return str_i(*this, i);
}
template <typename T>
template <class const_str_i_T>
Matrix<T>::const_str_i Matrix<T>::operator[](size_t i) const {
	return const_str_i(*this, i);
}


template <typename T>
T** Matrix<T>::allocate(size_t N_, size_t M_)
{
	T** new_arr = new T * [N_]();

	for (size_t i = 0; i < N_; i++) {
		new_arr[i] = new T[M_]();
	}

	return new_arr;
}
template <typename T>
size_t Matrix<T>::get_N() const {
	return N;
}
template <typename T>
size_t Matrix<T>::get_M() const {
	return M;
}

template <typename T>
void Matrix<T>::fill(const T& value)
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			arr[i][j] = value;
		}
	}
}
template <typename T>
void Matrix<T>::set_at(size_t i, size_t j, const T& data) {
	if (i >= N)
		throw std::out_of_range("out_of_range in void set_at : metod i = " + std::to_string(i) + " > matrix N = " + std::to_string(N));

	if (j >= M)
		throw std::out_of_range("out_of_range in void set_at : metod j = " + std::to_string(j) + " > matrix M = " + std::to_string(M));

	if (arr == nullptr)
		throw std::length_error("length_error in void set_at : NO create_matrix");

	arr[i][j] = data;
}
template <typename T>
void Matrix<T>::set_at(Coordinates cell, const T& data) {
	set_at(cell.i, cell.j, data);
}
template <typename T>
T& Matrix<T>::get_at(size_t i, size_t j) {
	if (i >= N)
		throw std::out_of_range("out_of_range in void get_at : metod i = " + std::to_string(i) + " > matrix N = " + std::to_string(N));

	if (j >= M)
		throw std::out_of_range("out_of_range in void get_at : metod j = " + std::to_string(j) + " > matrix M = " + std::to_string(M));

	if (arr == nullptr)
		throw std::length_error("length_error in void get_at : NO create_matrix");

	return arr[i][j];
}
template <typename T>
T& Matrix<T>::get_at(Coordinates cell) {
	return get_at(cell.i, cell.j);
}
template <typename T>
void Matrix<T>::clear() {
	if (arr != nullptr)
	{
		for (size_t i = 0; i < N; i++) {
			delete[] arr[i];
		}
		delete[] arr;

		arr = nullptr;
		N = 0;
		M = 0;
	}
}
template <typename T>
bool Matrix<T>::is_empty()
{
	if (arr == nullptr)
		return true;

	return false;
}
template <typename T>
void Matrix<T>::print() const
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			std::cout << arr[i][j];
					}
		std::cout << "\n";
	}
}
template <typename T>
void Matrix<T>::print(std::ofstream& output) const
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			output << arr[i][j];
		}
		output << "\n";
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Matrix_v1_end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif //! MATRIX_TEMPLATE_H__
