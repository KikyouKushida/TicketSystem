#ifndef Inc
#define Inc

#include <cstring>
#include <string>
#include <iostream>
#include <memory>
#include <cstdio>
#include <fstream>
#include <functional>
#include <cassert>
#include <cstdlib>

#endif

namespace sjtu 
{
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */

const int w = 3;

template<typename T>
class vector 
{

private:

	int maxSize, currentLength;
	T** a;

	void doubleSpace(){
		T** b = a;
		a = new T*[2 * maxSize];
		for(int i = 0; i < 2 * maxSize; ++i) a[i] = nullptr;
		for(int i = 0; i < maxSize; ++i) a[i] = b[i];
		delete[] b;
		maxSize *= 2;
		return ;
	}

	void halfSpace(){
		T** b = a;
		a = new T*[maxSize / 2]; 
		for(int i = 0; i < maxSize / 2; ++i) a[i] = b[i];
		for(int i = maxSize / 2; i < maxSize; ++i) if(b[i] != nullptr) delete b[i];
		delete[] b;
		maxSize /= 2;
		return ;
	}

public:

	int get_maxSize() const{
		return maxSize;
	}

	int get_currentLength() const{
		return currentLength;
	}
	/**
	 * TODO
	 * a type for actions of the elements of a vector, and you should write
	 *   a class named const_iterator with same interfaces.
	 */
	/**
	 * you can see RandomAccessIterator at CppReference for help.
	 */
	class const_iterator;
	class iterator 
	{
	// The following code is written for the C++ type_traits library.
	// Type traits is a C++ feature for describing certain properties of a type.
	// For instance, for an iterator, iterator::value_type is the type that the 
	// iterator points to. 
	// STL algorithms and containers may use these type_traits (e.g. the following 
	// typedef) to work properly. In particular, without the following code, 
	// @code{std::sort(iter, iter1);} would not compile.
	// See these websites for more information:
	// https://en.cppreference.com/w/cpp/header/type_traits
	// About value_type: https://blog.csdn.net/u014299153/article/details/72419713
	// About iterator_category: https://en.cppreference.com/w/cpp/iterator
	public:
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::output_iterator_tag;
		iterator(const T** new_val, const vector* new_bel){
			bel = new_bel;
			val = new_val;
		}
		iterator(T** new_val, const vector* new_bel){
			bel = new_bel;
			val = new_val;
		}
		//iterator(const vector* new_bel){
		//	bel = new_bel;
		//	val = &(nullptr);
		//}
		iterator(const iterator& other){
			bel = other.get_bel();
			val = other.get_val();
		}
		iterator(const const_iterator& other){
			bel = other.get_bel();
			val = other.get_val();
		}
		T** get_val() const{
			return val;
		}
		const vector* get_bel() const{
			return bel;
		}
	private:
		T** val;
		const vector* bel;
		/**
		 * TODO add data members
		 *   just add whatever you want.
		 */
	public:
		/**
		 * return a new iterator which pointer n-next elements
		 * as well as operator-
		 */
		iterator operator+(const int &n) const 
		{
			return iterator(val + n, bel);
			//TODO
		}
		iterator operator-(const int &n) const 
		{
			return iterator(val - n, bel);
			//TODO
		}
		// return the distance between two iterators,
		// if these two iterators point to different vectors, throw invaild_iterator.
		int operator-(const iterator &rhs) const 
		{
			return abs(val - rhs.get_val());
			//TODO
		}
		iterator& operator+=(const int &n) 
		{
			val += n;
			return *this;
			//TODO
		}
		iterator& operator-=(const int &n) 
		{
			val -= n;
			return *this;
			//TODO
		}
		/**
		 * TODO iter++
		 */
		iterator operator++(int) {
			iterator old(*this);
			++val;
			return old;
		}
		/**
		 * TODO ++iter
		 */
		iterator& operator++() {
			++val;
			return *this;
		}
		/**
		 * TODO iter--
		 */
		iterator operator--(int) {
			iterator old(*this);
			--val;
			return old;
		}
		/**
		 * TODO --iter
		 */
		iterator& operator--() {
			--val;
			return *this;
		}
		/**
		 * TODO *it
		 */
		T& operator*() const{
			return **val;
		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory address).
		 */
		bool operator==(const iterator &rhs) const {
			return val == rhs.get_val();
		}
		bool operator==(const const_iterator &rhs) const {
			return val == rhs.get_val();
		}
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const {
			return val != rhs.get_val();
		}
		bool operator!=(const const_iterator &rhs) const {
			return val != rhs.get_val();
		}
	};
	/**
	 * TODO
	 * has same function as iterator, just for a const object.
	 */
	class const_iterator 
	{
	public:
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::output_iterator_tag;
		const_iterator(const T** new_val, const vector* new_bel){
			bel = new_bel;
			val = new_val;
		}
		const_iterator(T** new_val, const vector* new_bel){
			bel = new_bel;
			val = new_val;
		}
		//const_iterator(const vector* new_bel){
		//	bel = new_bel;
		//	val = &(nullptr);
		//}
		const_iterator(const iterator& other){
			bel = other.get_bel();
			val = other.get_val();
		}
		const_iterator(const const_iterator& other){
			bel = other.get_bel();
			val = other.get_val();
		}
		T** get_val() const{
			return val;
		}
		const vector* get_bel() const{
			return bel;
		}
	private:
		T** val;
		const vector* bel;
		/**
		 * TODO add data members
		 *   just add whatever you want.
		 */
	public:
		/**
		 * return a new iterator which pointer n-next elements
		 * as well as operator-
		 */
		const_iterator operator+(const int &n) const 
		{
			return iterator(val + n, bel);
			//TODO
		}
		const_iterator operator-(const int &n) const 
		{
			return iterator(val - n, bel);
			//TODO
		}
		// return the distance between two iterators,
		// if these two iterators point to different vectors, throw invaild_iterator.
		int operator-(const const_iterator &rhs) const 
		{
			return abs(val - rhs.get_val());
			//TODO
		}
		const_iterator& operator+=(const int &n) 
		{
			val += n;
			return *this;
			//TODO
		}
		const_iterator& operator-=(const int &n) 
		{
			val -= n;
			return *this;
			//TODO
		}
		/**
		 * TODO iter++
		 */
		const_iterator operator++(int) {
			const_iterator old(*this);
			++val;
			return old;
		}
		/**
		 * TODO ++iter
		 */
		const_iterator& operator++() {
			++val;
			return *this;
		}
		/**
		 * TODO iter--
		 */
		const_iterator operator--(int) {
			const_iterator old(*this);
			--val;
			return old;
		}
		/**
		 * TODO --iter
		 */
		const_iterator& operator--() {
			--val;
			return *this;
		}
		/**
		 * TODO *it
		 */
		const T& operator*() const{
			return **val;
		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory address).
		 */
		bool operator==(const iterator &rhs) const {
			return val == rhs.get_val();
		}
		bool operator==(const const_iterator &rhs) const {
			return val == rhs.get_val();
		}
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const {
			return val != rhs.get_val();
		}
		bool operator!=(const const_iterator &rhs) const {
			return val != rhs.get_val();
		}

	};
	/**
	 * TODO Constructs
	 * At least two: default constructor, copy constructor
	 */
	vector() {
		currentLength = 0;
		maxSize = 2;
		a = new T*[2];
		a[0] = a[1] = nullptr;
	}
	vector(const vector &other) {
		if(this == &other);
		else {
			currentLength = other.currentLength;
			maxSize = other.maxSize;
			a = new T*[maxSize];
			for(int i = 0; i < maxSize; ++i) a[i] = nullptr;
			for(int i = 0; i < currentLength; ++i) a[i] = new T(other[i]);
		}
	}
	/**
	 * TODO Destructor
	 */
	~vector() {
		for(int i = 0; i < maxSize; ++i) if(a[i] != nullptr) delete a[i];
		delete[] a;
	}
	/**
	 * TODO Assignment operator
	 */
	vector &operator=(const vector &other) {
		if(this == &other) return *this;
		else {
			this->~vector();
			currentLength = other.currentLength;
			maxSize = other.maxSize;
			a = new T*[maxSize];
			for(int i = 0; i < maxSize; ++i) a[i] = nullptr;
			for(int i = 0; i < currentLength; ++i) a[i] = new T(other[i]);
			return *this;
		}
	}
	/**
	 * assigns specified element with bounds checking
	 * throw index_out_of_bound if pos is not in [0, size)
	 */
	T & at(const size_t &pos) {
		return *(a[pos]);
	}
	const T & at(const size_t &pos) const {
		return *(a[pos]);
	}
	/**
	 * assigns specified element with bounds checking
	 * throw index_out_of_bound if pos is not in [0, size)
	 * !!! Pay attentions
	 *   In STL this operator does not check the boundary but I want you to do.
	 */
	T & operator[](const size_t &pos) {
		return *(a[pos]);
	}
	const T & operator[](const size_t &pos) const {
		return *(a[pos]);
	}
	/**
	 * access the first element.
	 * throw container_is_empty if size == 0
	 */
	const T & front() const {
		return *(a[0]);
	}
	/**
	 * access the last element.
	 * throw container_is_empty if size == 0
	 */
	const T & back() const {
		return *(a[currentLength - 1]);
	}
	/**
	 * returns an iterator to the beginning.
	 */
	iterator begin() {
		return iterator(a + 0, this);
	}
	const_iterator cbegin() const {
		return const_iterator(a + 0, this);
	}
	/**
	 * returns an iterator to the end.
	 */
	iterator end() {
		return iterator(a + currentLength, this);
	}
	const_iterator cend() const {
		return const_iterator(a + currentLength, this);
	}
	/**
	 * checks whether the container is empty
	 */
	bool empty() const {
		return get_currentLength() == 0;
	}
	/**
	 * returns the number of elements
	 */
	size_t size() const {
		return (size_t)get_currentLength();
	}
	/**
	 * clears the contents
	 */
	void clear() {
		while(currentLength) pop_back();
		return ;
	}
	/**
	 * inserts value before pos
	 * returns an iterator pointing to the inserted value.
	 */
	iterator insert(iterator pos, const T &value) {
		if(currentLength + 2 > maxSize) doubleSpace();
		int ind = currentLength;
		for(int i = 0; i < currentLength; ++i){
			iterator it(a + i, this);
			if(it == pos){
				ind = i;
				break;
			}
		}
		int moveLength = currentLength - ind;
		memmove(a + ind + 1, a + ind, moveLength * sizeof(T**));
		a[ind] = new T(value);
		currentLength += 1;
		return iterator(a + ind, this);
	}
	/**
	 * inserts value at index ind.
	 * after inserting, this->at(ind) == value
	 * returns an iterator pointing to the inserted value.
	 * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
	 */
	iterator insert(const size_t &ind, const T &value) {
		if(currentLength + 2 > maxSize) doubleSpace();
		if(ind < currentLength){
			int moveLength = currentLength - ind;
			memmove(a + ind + 1, a + ind, moveLength * sizeof(T**));
		}
		a[ind] = new T(value);
		currentLength += 1;
		return iterator(a + ind, this);
	}
	/**
	 * removes the element at pos.
	 * return an iterator pointing to the following element.
	 * If the iterator pos refers the last element, the end() iterator is returned.
	 */
	iterator erase(iterator pos) {
		int ind;
		for(int i = 0; i < currentLength; ++i){
			iterator it(a + i, this);
			if(it == pos){
				ind = i;
				break;
			}
		}
		delete a[ind];
		a[ind] = nullptr;
		if(ind + 1 < currentLength){
			int moveLength = currentLength - ind - 1;
			memmove(a + ind, a + ind + 1, moveLength * sizeof(T**));
		}
		a[currentLength - 1] = nullptr; 
		currentLength -= 1;
		if(currentLength * w < maxSize && currentLength > 0) halfSpace();
		if(ind == currentLength) return end();
		else return iterator(a + ind, this);
	}
	/**
	 * removes the element with index ind.
	 * return an iterator pointing to the following element.
	 * throw index_out_of_bound if ind >= size
	 */
	iterator erase(const size_t &ind) {
		delete a[ind];
		a[ind] = nullptr;
		if(ind + 1 < currentLength){
			int moveLength = currentLength - ind - 1;
			memmove(a + ind, a + ind + 1, moveLength * sizeof(T**));
		}
		a[currentLength - 1] = nullptr; 
		currentLength -= 1;
		if(currentLength * w < maxSize && currentLength > 0) halfSpace();
		if(ind == currentLength) return end();
		else return iterator(a + ind, this);
	}
	
	/**
	 * adds an element to the end.
	 */
	void push_back(const T &value) {
		insert(currentLength, value);
		return ;
	}
	/**
	 * remove the last element from the end.
	 * throw container_is_empty if size() == 0
	 */
	void pop_back() {
		erase(currentLength - 1);
		return ;
	}
};


}