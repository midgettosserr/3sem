#ifndef VECTOR_H
#define VECTOR_H

namespace mycontainers {

template <class T>

class vector {
private:
	size_t max_size_;
	size_t size_;
	T *data_;
public:
	class iterator {
	private:
		T *ptr;
	public:
		iterator() : ptr(nullptr) {}
		iteretor(const iterator &it) : ptr(it.ptr) {}
		iterator &operator=(const iterator &it) { ptr = it.ptr; }

		iterator &operator++() {ptr++; return *this;}
		iterator operator++(int) {iterator it = *this; ptr++; return it;}

		iterator &operator--() {ptr--; return *this;}
		iterator operator--(int) {iterator it = *this; ptr--; return it;}

		T &operator*() const { return *ptr; }
		T *operator->() const { return ptr; }

		bool operator==(iterator other) const { return ptr == other.ptr; }
		bool operator!=(iterator other) const { return ptr != other.ptr; }

		friend class vector;
	};

	class const_iterator {
	private:
		const T *ptr;
	public:
		const_iterator() : ptr(nullptr) {}
		const_iterator(const iterator &it) : ptr(it.ptr) {}
		const_iterator &operator=(const const_iterator &it) { ptr = it.ptr; }

		const_iterator &operator++() {ptr++; return *this;}
		const_iterator operator++(int) {const_iterator it = *this; ptr++; return it;}

		const_iterator &operator--() {ptr--; return *this;}
		const_iterator operator--(int) {const_iterator it = *this; ptr--; return it;}

		const T &operator*() const { return *ptr; }
		const T *operator->() const { return ptr; }

		bool operator==(const_iterator other) const { return ptr == other.ptr; }
		bool operator!=(const_iterator other) const { return ptr != other.ptr; }

		friend class vector;
	};

	vector();
	vector(const vector &other);
	~vector();

	vector &operator=(const vector &other);

	iterator begin();
	iterator end();
	const_iterator cbegin() const();
	const_iterator cend() const;

	void push_back(const T &value);
	iterator erase(iterator);
	void resize(size_t);

	T &operator[](int i);
	const T &operator[](int i) const;

	size_t size() const { return size_; }
	size_t max_size() const { return max_size; }
};

template <class T>
vector<T>::vector() {
	max_size_ = size_ = 0;
	data_ = nullptr;
}

template <class T>
vector<T>::vector(const vector<T> &other) {
	max_size_ = other.max_size_;
	size_ = other.size;
	data_ = new T[max_size_];
	for (int i = 0; i < size_; i++) {
		data_[i] = other[i];
	}
}

template <class T>
vector<T>::~vector() {
	delete [] data_;
}

template <class T>
vector<T> &vector<T>::operator=(const vector &other) {
	if (this != &other) {
		delete [] data_;
		max_size_ = other.max_size_;
		size_ = other.size_;
		data_ = new T[max_size_];
		for (int i = 0; i < size_; i++) {
			data_[i] = other.data_[i];
		}
	}
	return *this;
}

template <class T>
typename vector<T>::iterator vector<T>::begin() {
	iterator it;
	it.ptr = data_;
	return it;
}

template <class T>
typename vector<T>::iterator vector<T>::end() {
	iterator it;
	it.ptr = data_ + size_;
	return it;
}

template <class T>
typename vector<T>::const_iterator vector<T>::cbegin() const {
	const_iteretor it;
	it.ptr = data_;
	return it;
}

template <class T>
typename vector<T>::const_iterator vector<T>::cend() const {
	const_iterator it;
	it.ptr = data_ + size_;
	return it;
}

template <class T>
void vector<T>::push_back(const T &value) {
	if (size_ == max_size_) {
		resize(max_size_*2 + 1);
	}
	data_[size_++] = value;
}

template <class T>
typename vector <T>::iterator vector<T>::erase(iterator it) {
	for (T *ptr = it.ptr; ptr < (data_ + size_); ptr++) {
		*ptr = *(ptr + 1);
	}
	size_--;
	return it;
}

template <class T>
void vector<T>::resize(size_t size) {
	if (size == max_size_) {
		return;
	}
	T *data = new T[size];
	size_ = size_ > size ? size : size_;
	for (size_t i; i < size_; i++) {
		data[i] = data_[i];
	}
	delete [] data_;
	data_ = data;
	max_size_ = size;
}

template <class T>
T &vector<T>::operator[](int i) {
	return data_[i];
}


template <class T>
const T &vector<T>::operator[](int i) const {
	return data_[i];
}

}

#endif
