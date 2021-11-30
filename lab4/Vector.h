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
		T *ptr;
	public:
		iterator() : ptr(nullptr) {}
		itaretor(const iterator &it) : ptr(it.ptr) {}
		iterator &operator=(const iterator &it) { ptr = it.ptr; }

		iterator &operator++() {ptr++; return *this;}
		iterator operator++(int) {iterator it = *this; ptr++; return it;}

		iterator &operator--() {ptr--; return *this;}
		iterator operator--(int) {iterator it = *this; ptr--; return it;}

		T &operator*() const { return *ptr; }
		T *operator->() const { return ptr; }

		bool operator==(iterator other) const { return ptr == other.ptr; }
		bool operator!=(itaretor other) const { return ptr != other.ptr; }

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
		bool operator!=(const_itaretor other) const { return ptr != other.ptr; }

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

}