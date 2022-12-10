#ifndef RAY_TEMPLATE_H_ 

#define RAY_TEMPLATE_H_ 

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <initializer_list>

template <typename T>
class Ray_template {
private:

	T* ray_ = nullptr;

	size_t LEFT = 0;
	size_t F_LEFT = 0;
	size_t RIGHT = 0;
	size_t F_RIGHT = 0;

	size_t COEFFICIENT = 0;

	size_t saved_LEFT = LEFT;
	size_t saved_RIGHT = RIGHT;

	void create_();

	void LEFT_increase_();

	void RIGHT_increase_();

	// LEFT|------------------0------------------|RIGHT
	// LEFT|------------------0-------F_RIGHT----|RIGHT
	// LEFT|----F_LEFT--------0-------F_RIGHT----|RIGHT
	// LEFT|----LEFT - F_LEFT-0-------F_RIGHT----|RIGHT
	// LEFT|----INDEX---------0-------F_RIGHT----|RIGHT
	// LEFT|-------------LEFT+-+RIGHT------------|RIGHT

	T& get_element_(size_t index);

	const T& get_element_(size_t index) const;

	template<typename T>
	friend void print(const Ray_template<T>& Ray);
public:

	Ray_template();
	//LEFT, RIGHT
	Ray_template(size_t LEFT, size_t RIGHT);
	//LEFT, RIGHT, COEFFICIENT
	Ray_template(size_t LEFT, size_t RIGHT, size_t COEFFICIENT);

	Ray_template(const Ray_template& other);

	Ray_template(const std::initializer_list<T>& li);

	Ray_template(const T* val, size_t size);

	// LEFT
	void add_to_first(const T& value);

	//RIGHT
	void add_to_back(const T& value);

	T& at_(size_t index);

	const T& at_(size_t index) const;

	T& operator[](size_t index);


	const T& operator[](size_t index) const;

	void push_back(const T& value);

	void push_begin(const T& value);

	//LEFT
	void pop_front();

	//RIGHT
	void pop_back();

	void remove(size_t index);

	void insert(size_t index, T& value);

	size_t size() const;

	size_t capacity() const;

	void cut();

	void shrink_to_fit();

	void clear();

	~Ray_template();

	Ray_template& operator=(const Ray_template& other);
};

template <typename T>
void Ray_template<T>::create_() {
	ray_ = new T[LEFT + RIGHT]();
}

template <typename T>
void Ray_template<T>::LEFT_increase_() {
	int new_LEFT = LEFT * COEFFICIENT;
	size_t new_long = new_LEFT + RIGHT;
	T* new_ray = new T[new_long]();

	size_t N = F_LEFT + F_RIGHT; //количество переносимых элементов 
	size_t diff = new_LEFT - LEFT + (LEFT - F_LEFT); // сдвиг относительно начала
	for (size_t i = LEFT - F_LEFT; i < N; ++i) { //!!!выход за границы массива
		new_ray[i + diff] = std::move(ray_[i]);
	}

	delete[] ray_;

	ray_ = new_ray;
	LEFT = new_LEFT;
}

template <typename T>
void Ray_template<T>::RIGHT_increase_() {
	int new_RIGHT = RIGHT * COEFFICIENT;
	size_t new_long = LEFT + new_RIGHT;
	T* new_ray = new T[new_long]();

	size_t N = F_LEFT + F_RIGHT; //количество переносимых элементов 
	size_t diff = LEFT - F_LEFT; // сдвиг относительно начала
	for (size_t i = 0; i < N; ++i) { //!!!выход за границы массива
		new_ray[i + diff] = std::move(ray_[i + diff]);
	}

	delete[] ray_;

	ray_ = new_ray;
	RIGHT = new_RIGHT;
}

template <typename T>
T& Ray_template<T>::get_element_(size_t index) {
	return ray_[(LEFT - F_LEFT) + index];
}

template <typename T>
const T& Ray_template<T>::get_element_(size_t index) const {
	return ray_[(LEFT - F_LEFT) + index];
}

template <typename T>
Ray_template<T>::Ray_template<T>() :Ray_template<T>(10u, 10u, 2) {

}

template <typename T>
Ray_template<T>::Ray_template<T>(size_t LEFT, size_t RIGHT) : Ray_template<T>(LEFT, RIGHT, 2u) {

}

template <typename T>
Ray_template<T>::Ray_template<T>(size_t LEFT, size_t RIGHT, size_t COEFFICIENT)
	: LEFT(LEFT), COEFFICIENT(COEFFICIENT), RIGHT(RIGHT) {

}

template <typename T>
Ray_template<T>::Ray_template<T>(const Ray_template<T>& other)
/*:LEFT(LEFT), COEFFICIENT(COEFFICIENT), RIGHT(RIGHT) */
{
	//std::cout << "copy-constructor " << std::endl;
	LEFT = other.LEFT;
	RIGHT = other.RIGHT;
	F_LEFT = other.F_LEFT;
	F_RIGHT = other.F_RIGHT;

	COEFFICIENT = other.COEFFICIENT;

	saved_LEFT = LEFT;
	saved_RIGHT = RIGHT;

	create_();

	for (size_t i = LEFT - F_LEFT; i < LEFT + F_RIGHT; ++i)
		ray_[i] = other.ray_[i];
}
template <typename T>
Ray_template<T>::Ray_template(const std::initializer_list<T>& li)
{
	LEFT = 1;
	RIGHT = 1;
	COEFFICIENT = 2;
	create_();

	for (auto it = li.begin(); it != li.end(); it++)
	{
		if (F_RIGHT == RIGHT) {
			RIGHT_increase_();
		}

		ray_[LEFT + F_RIGHT] = *it;
		++F_RIGHT;
	}
	shrink_to_fit();
}



template <typename T>
void Ray_template<T>::add_to_first(const T& value) {
	if (ray_ == nullptr)
		create_();

	if (F_LEFT == LEFT) {
		LEFT_increase_();

	}

	ray_[LEFT - F_LEFT - 1] = value;
	++F_LEFT;
}



template <typename T>
void Ray_template<T>::add_to_back(const T& value) {
	if (ray_ == nullptr)
		create_();

	if (F_RIGHT == RIGHT) {
		RIGHT_increase_();
	}

	ray_[LEFT + F_RIGHT] = value;
	++F_RIGHT;
}

template <typename T>
Ray_template<T>::Ray_template(const T* val, size_t size)
{
	LEFT = 1;
	RIGHT = 1;
	COEFFICIENT = 2;

	create_();
	int i;
	for (i = 0; i < size; ++i)
	{

		if (F_RIGHT == RIGHT) {
			RIGHT_increase_();
		}

		ray_[LEFT + F_RIGHT] = val[i];
		++F_RIGHT;
	}
	shrink_to_fit();
}


template <typename T>
T& Ray_template<T>::at_(size_t index) {
	//if (index ...)
	return Ray_template<T>::get_element_(index);
}

template <typename T>
const T& Ray_template<T>::at_(size_t index) const {
	//if (index ...)
	return Ray_template<T>::get_element_(index);
}

template <typename T>
T& Ray_template<T>::operator[](size_t index) {
	return get_element_(index);
}

template <typename T>
const T& Ray_template<T>::operator[](size_t index) const {
	return get_element_(index);
}

template <typename T>
void Ray_template<T>::push_back(const T& value) {
	add_to_back(value);
}

template <typename T>
void Ray_template<T>::push_begin(const T& value) {
	add_to_first(value);
}

template <typename T>
void Ray_template<T>::pop_front() {
	--F_LEFT;
}

template <typename T>
void Ray_template<T>::pop_back() {
	--F_RIGHT;
}

template <typename T>
void Ray_template<T>::remove(size_t index) {
	if (index > (LEFT + RIGHT))
		return;

	if (index < F_LEFT) { //индекс в левой части

		int diff = LEFT - F_LEFT;
		for (int i = index; i > 0; --i) //сдвигаем для удаления
		{
			ray_[diff + i] = ray_[diff + (i - 1)];
		}
		--F_LEFT;

		std::cout << "\n";
	}
	else {
		int diff = LEFT - F_LEFT;
		for (size_t i = index; i < F_RIGHT - 1; ++i) //куда копирую
		{
			ray_[diff + i] = ray_[diff + (i + 1)];
		}

		--F_RIGHT;
	}
}

template <typename T>
void Ray_template<T>::insert(size_t index, T& value) {

	if (ray_ == nullptr)
		create_();

	if (index >= (LEFT + RIGHT))
		return;

	//количество свободных
	int L = LEFT - F_LEFT;
	int R = RIGHT - F_RIGHT;

	if (L == 0) {
		LEFT_increase_();
		L = LEFT - F_LEFT;
	}

	int diff = LEFT - F_LEFT;
	++F_LEFT;
	for (int i = 0; i < index; ++i)
	{
		ray_[diff + i - 1] = std::move(ray_[diff + i]);
	}
	ray_[diff + index - 1] = value;
}

template <typename T>
size_t Ray_template<T>::size() const {
	return F_LEFT + F_RIGHT;
}

template <typename T>
size_t Ray_template<T>::capacity() const {
	return LEFT + RIGHT;
}

template <typename T>
void Ray_template<T>::cut() {
	size_t new_long = size();
	T* new_ray = new T[new_long]();

	for (size_t i = 0; i < new_long; i++)
	{
		new_ray[i] = ray_[(LEFT - F_LEFT) + i];
	}
	delete[] ray_;
	LEFT = F_LEFT;
	RIGHT = F_RIGHT;
	ray_ = new_ray;
}

template <typename T>
void Ray_template<T>::shrink_to_fit() {
	cut();
}

template <typename T>
void Ray_template<T>::clear() {
	delete[] ray_;
	ray_ = nullptr;
	LEFT = saved_LEFT;
	F_LEFT = 0;
	RIGHT = saved_RIGHT;
	F_RIGHT = 0;
}

template <typename T>
Ray_template<T>::~Ray_template() {
	clear();
	//delete[] ray_; 
	//std::cout << "\t ! \n";
}

template <typename T>
Ray_template<T>& Ray_template<T>::operator=(const Ray_template<T>& other) {
	//std::cout << "operator=" << std::endl;
	//this - адрес левого операнда
	if (this != &other) {
		LEFT = other.LEFT;
		RIGHT = other.RIGHT;
		F_LEFT = other.F_LEFT;
		F_RIGHT = other.F_RIGHT;

		COEFFICIENT = other.COEFFICIENT;

		saved_LEFT = LEFT;
		saved_RIGHT = RIGHT;

		delete[] ray_;
		create_();

		for (size_t i = LEFT - F_LEFT; i < LEFT + F_RIGHT; ++i)
			ray_[i] = other.ray_[i];
	}

	return *this;
}

template <typename T>
void print(const Ray_template<T>& Ray) {

	std::cout << "\n";
	for (size_t i = 0; i < Ray.LEFT + Ray.RIGHT; i++)
		std::cout << std::setw(2) << i << " ";
	std::cout << "\n";

	for (size_t i = 0; i < Ray.LEFT - Ray.F_LEFT; i++)
		std::cout << std::setw(2) << "_" << " ";
	for (size_t i = 0; i < Ray.F_LEFT + Ray.F_RIGHT; i++)
		std::cout << std::setw(2) << i << " ";
	for (size_t i = Ray.F_RIGHT; i < Ray.RIGHT; i++)
		std::cout << std::setw(2) << "_" << " ";
	std::cout << "\n";

	for (size_t i = 0; i < Ray.LEFT - Ray.F_LEFT; i++)
		std::cout << std::setw(2) << "." << " ";
	for (size_t i = Ray.LEFT - Ray.F_LEFT; i < Ray.LEFT + Ray.F_RIGHT; i++)
		std::cout << std::setw(2) << Ray[i] << " ";
	//std::cout << std::setw(2) << ray_[i].x << " " << ray_[i].y << " ";
	for (size_t i = Ray.F_RIGHT; i < Ray.RIGHT; i++)
		std::cout << std::setw(2) << "." << " ";
	std::cout << "\n";
}




#endif // !RAY_TEMPLATE_H_ 
