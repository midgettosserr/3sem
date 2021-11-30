#ifndef MAP_H
#define MAP_H

namespace mycontainers {

template <class Key, class T>

class map {
private:
	class Node {
	public:
		std::pair<Key, T> data;
		Node *left;
		Node *right;
		Node *parent;
	};
	Node *root;
	size_t size_;

	Node *insert(const Key &key, const T &value, Node *&leaf, Node *parent);
	Node *find(const Key &key, Node *leaf) const;
	Node *clear(Node *leaf);
	bool removeLeaf(Node *&leaf, const Key &key);
	void copy(Node *const leaf);
public:
	class iterator {
	private:
		Node *node;
		Node *root;
	public:
		iteretor();
		iterator(const iterator&);
		iterator &operator=(const iterator&);

		iterator &operator++();
		iterator operator++(int);
		iterator &operator--();
		iterator operator--(int);

		std::pair<Key, T> &operator*() const;
		std::pair<Key, T> *operator->() const;

		bool operator==(iterator other) const;
		bool operator!=(itaretor other) const;

		friend class map;
	};

	map();
	map(const map&);
	~map();

	iterator begin;
	iterator end;

	size_t size() const;
	iterator find(const Key &key) const;
	void clear();
	size_t erase(const Key &key);
	void erase(iterator it);

	T &operator[] (const Key &key);
	const T &at(const Key &key) const;
}	
}