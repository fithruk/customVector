#include <iostream>

template<typename T>
class MyVector {
private:
	size_t size;
	T* data = nullptr;
	size_t lastEl;
public:
	MyVector();
	MyVector(const size_t size);
	MyVector(const size_t size, std::nothrow_t);
	MyVector(const MyVector& other);
	MyVector& operator=(const MyVector& other);
	MyVector& operator+(const MyVector& other);
	T& operator[](size_t index);
	size_t getSize() const;
	MyVector& push_back(const T& item);
	void resize(size_t newSize, std::nothrow_t);
	~MyVector();
};

template<typename T>
MyVector<T>::MyVector() : size(40), lastEl(40 - 1) {
	data = new T[size];
}

template<typename T>
MyVector<T>::MyVector(const size_t size) : size(size), lastEl(size - 1) {
	std::cout << this << " MyVector(const size_t size) " << std::endl;
	data = new T[size];
}

template<typename T>
MyVector<T>::MyVector(const size_t size, std::nothrow_t) : size(size), lastEl(size - 1) {
	std::cout << this << " MyVector(const size_t size, std::nothrow_t) " << std::endl;
	data = new (std::nothrow) T[size];
	if (!data) {
		this->size = 0;
		this->lastEl = 0;
	}
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other) {
	std::cout << this << " copy " << std::endl;
	lastEl = other.lastEl;
	size = other.size;
	data = new T[other.size];
	for (size_t i = 0; i < other.size; i++)
		data[i] = other.data[i];
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
	std::cout << this << " operator= " << std::endl;
	if (this == &other) {
		return *this;
	}
	delete[] data;
	lastEl = other.lastEl;
	size = other.size;
	data = new T[other.size];
	for (size_t i = 0; i < other.size; i++)
		data[i] = other.data[i];
	return *this;
}

template<typename T>
MyVector<T>& MyVector<T>::operator+(const MyVector& other) {
	std::cout << this << " operator+ " << std::endl;
	if (this == &other) {
		return *this;
	}
	size_t tempSize = size;
	T* tempArray = new T[tempSize];
	for (size_t i = 0; i < size; i++)
		tempArray[i] = data[i];

	delete[] data;
	lastEl = other.lastEl;
	size += other.size;
	data = new T[size];

	for (size_t i = 0; i < tempSize; i++)
		data[i] = tempArray[i];

	for (size_t i = 0; i < other.size; i++)
		data[tempSize + i] = other.data[i];

	delete[] tempArray;
	return *this;
}

template<typename T>
T& MyVector<T>::operator[](size_t index) {
	return data[index];
}

template<typename T>
size_t MyVector<T>::getSize() const {
	return size;
}

template<typename T>
MyVector<T>& MyVector<T>::push_back(const T& item) {
	std::cout << this << " MyVector& push_back " << std::endl;
	if (lastEl + 1 >= size) {
		size_t newSize = size * 2;
		T* newData = new T[newSize];
		for (size_t i = 0; i < size; i++) {
			newData[i] = data[i];
		}
		delete[] data;
		data = newData;
		size = newSize;
	}
	data[++lastEl] = item;
	return *this;
}

template<typename T>
void MyVector<T>::resize(size_t newSize, std::nothrow_t) {
	std::cout << this << " resize(size_t newSize, std::nothrow_t) " << std::endl;
	T* newData = new (std::nothrow) T[newSize];
	if (!newData) {
		return;
	}
	size_t elementsToCopy = (newSize < size) ? newSize : size;
	for (size_t i = 0; i < elementsToCopy; i++) {
		newData[i] = data[i];
	}
	delete[] data;
	data = newData;
	size = newSize;
	lastEl = elementsToCopy - 1;
}

template<typename T>
MyVector<T>::~MyVector() {
	std::cout << this << " ~MyVector " << std::endl;
	delete[] data;
}


int main()
{
    std::cout << "Hello World!\n";
}

