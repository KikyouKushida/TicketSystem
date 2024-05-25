#ifndef Inc
#define Inc

const bool Printing = false;
#define remosk if(Printing == true)

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

template<typename T>
class QuickSort {
public:
    static void swap(T &a, T &b){
      T c = a;
      a = b;
      b = c;
    }
    static void sort(sjtu::vector<T> &vec, int left, int right, std::function<bool(const T&, const T&)> cmp) {
        if (left < right) {
            int pivotIndex = partition(vec, left, right, cmp);
            sort(vec, left, pivotIndex - 1, cmp);
            sort(vec, pivotIndex + 1, right, cmp);
        }
    }

    static int partition(sjtu::vector<T> &vec, int left, int right, std::function<bool(const T&, const T&)> cmp) {
        T pivot = vec[right];
        int i = left - 1;
        for (int j = left; j < right; j++) {
            if (cmp(vec[j], pivot)) { 
                i++;
                swap(vec[i], vec[j]);
            }
        }
        swap(vec[i + 1], vec[right]);
        return i + 1;
    }

};

template<class T>
T& max(T &a, T &b){
  return a < b ? b : a;
}

template<class T>
T& min(T &a, T &b){
  return a < b ? a : b;
}

typedef unsigned long long ull;
const ull Prime = 197;

inline void Write(char *s, int &loc, const int &value){
  s[loc] = static_cast<unsigned char>((value >> 24) & 0xFF);
  s[loc + 1] = static_cast<unsigned char>((value >> 16) & 0xFF);
  s[loc + 2] = static_cast<unsigned char>((value >> 8) & 0xFF);
  s[loc + 3] = static_cast<unsigned char>(value & 0xFF);
  loc = loc + 4;
  return ;
}
inline void Read(char *s, int &loc, int &value){
  value = (static_cast<unsigned char>(s[loc]) << 24) |
          (static_cast<unsigned char>(s[loc + 1]) << 16) |
          (static_cast<unsigned char>(s[loc + 2]) << 8) |
          (static_cast<unsigned char>(s[loc + 3]) << 0);
  loc = loc + 4;
  return ;
}

inline void Write(char *s, int &loc, const ull &value){
  s[loc] = static_cast<unsigned char>((value >> 56) & 0xFF);
  s[loc + 1] = static_cast<unsigned char>((value >> 48) & 0xFF);
  s[loc + 2] = static_cast<unsigned char>((value >> 40) & 0xFF);
  s[loc + 3] = static_cast<unsigned char>((value >> 32) & 0xFF);
  s[loc + 4] = static_cast<unsigned char>((value >> 24) & 0xFF);
  s[loc + 5] = static_cast<unsigned char>((value >> 16) & 0xFF);
  s[loc + 6] = static_cast<unsigned char>((value >> 8) & 0xFF);
  s[loc + 7] = static_cast<unsigned char>(value & 0xFF);
  loc = loc + 8;
  return ;
}
inline void Read(char *s, int &loc, ull &value){
  value = (ull(static_cast<unsigned char>(s[loc])) << 56) |
          (ull(static_cast<unsigned char>(s[loc + 1])) << 48) |
          (ull(static_cast<unsigned char>(s[loc + 2])) << 40) |
          (ull(static_cast<unsigned char>(s[loc + 3])) << 32) |
          (ull(static_cast<unsigned char>(s[loc + 4])) << 24) |
          (ull(static_cast<unsigned char>(s[loc + 5])) << 16) |
          (ull(static_cast<unsigned char>(s[loc + 6])) << 8) |
          (ull(static_cast<unsigned char>(s[loc + 7])) << 0);
  loc = loc + 8;
  return ;
}

inline void Write(char *s, int &loc, const Char &value){
  for(int i = 0; i < 64; ++i) s[loc + i] = value[i];
  loc = loc + 64;
  return ;
}
inline void Read(char *s, int &loc, Char &value){
  for(int i = 0; i < 64; ++i) value[i] = s[loc + i];
	value.len = 0;
	for(int i = 0; i < 64; ++i) 
		if(value[i] != 0) ++value.len; 
		else break;
  loc = loc + 64;
  return ;
}

inline void Write_s(std::fstream &file, std::string &file_name, char *s, int loc){
  file.open(file_name, std::ios::in | std::ios::out | std::ios::binary);
  file.seekp(loc, std::ios::beg);
  file.write(s, 4096);
  file.close();
  return ;
}

inline void Read_s(std::fstream &file, std::string &file_name, char *s, int loc){
  file.open(file_name, std::ios::in | std::ios::out | std::ios::binary);
  file.seekg(loc, std::ios::beg);
  file.read(s, 4096);
  file.close();
  return ;
}

template<class T1, class T2> //T1: type of index, T2: type of value, in memoryRiver, Char and int
class BPT{
private:
  int M, L, MAX_N; // M fork BPT, in this problem = 56
  int node_count, current_size, root;
  bool *is_leaf;
  int *loc;
  int internal_loc, leaf_loc;
  const std::string internal_file_name, leaf_file_name, ext_file_name;
  std::fstream internal_file, leaf_file, ext_file;
  int *lb, *rb;
  struct page;
  char **cache;
  int *cache_id;
  int MAX_cache;
public:
	void construct_from_empty(){
		internal_file.open(internal_file_name, std::ios::out | std::ios::binary);
    leaf_file.open(leaf_file_name, std::ios::out | std::ios::binary);
    internal_file.close();
		leaf_file.close();
		ext_file.open(ext_file_name, std::ios::out | std::ios::binary);
		ext_file.close();
    node_count = 0;
    current_size = 0;
    internal_loc = 0;
    leaf_loc = 0;
    loc = new int[MAX_N + 5]();
    is_leaf = new bool[MAX_N + 5]();
    lb = new int[MAX_N + 5]();
    rb = new int[MAX_N + 5]();
    // Can be evaluated to be a much smaller number, to be done
		node_count = node_count + 1;
		root = node_count;
    is_leaf[node_count] = false;
    loc[node_count] = internal_loc; 
    internal_loc = internal_loc + 4096;
		char *temp = new char[4096]();
		int ptr = 0;
		Write(temp, ptr, 1);
		Write(temp, ptr, node_count + 1); //store the place where leaf is in
		page one_internal_node(node_count, temp, this);
		node_count = node_count + 1;
		is_leaf[node_count] = true;
		loc[node_count] = leaf_loc;
		leaf_loc = leaf_loc + 4096;
		memset(temp, 0, 4096);
		ptr = 0;
		Write(temp, ptr, 0);
		page one_leaf_node(node_count, temp, this);
		delete temp;
		return ;
	}
	void construct_from_last(){
		ext_file.open(ext_file_name, std::ios::in | std::ios::binary);
		ext_file.seekg(0, std::ios::beg);
		ext_file.read(reinterpret_cast<char *>(&node_count), 4);
		ext_file.read(reinterpret_cast<char *>(&current_size), 4);
		ext_file.read(reinterpret_cast<char *>(&root), 4);
		ext_file.read(reinterpret_cast<char *>(&internal_loc), 4);
		ext_file.read(reinterpret_cast<char *>(&leaf_loc), 4);
		loc = new int[MAX_N + 5]();
    is_leaf = new bool[MAX_N + 5]();
    lb = new int[MAX_N + 5]();
    rb = new int[MAX_N + 5]();
		for(int i = 1; i <= MAX_N; ++i) ext_file.read(reinterpret_cast<char *>(&is_leaf[i]), 1);
		for(int i = 1; i <= MAX_N; ++i) ext_file.read(reinterpret_cast<char *>(&loc[i]), 4);
		for(int i = 1; i <= MAX_N; ++i) ext_file.read(reinterpret_cast<char *>(&lb[i]), 4);
		for(int i = 1; i <= MAX_N; ++i) ext_file.read(reinterpret_cast<char *>(&rb[i]), 4);
		ext_file.close();
		return ;
	}
  BPT(const int &m, const int &l, const std::string &internal_file_name_, const std::string &leaf_file_name_, 
	const std::string &ext_file_name_, const int &MAX_N_, const int &MAX_cache_): 
  internal_file_name(internal_file_name_), leaf_file_name(leaf_file_name_), ext_file_name(ext_file_name_), M(m), L(l), MAX_N(MAX_N_), MAX_cache(MAX_cache_){
		cache = new char*[MAX_cache + 5];
    for(int i = 1; i <= MAX_cache; ++i) cache[i] = nullptr;
    cache_id = new int[MAX_cache + 5];
    for(int i = 1; i <= MAX_cache; ++i) cache_id[i] = 0;
    ext_file.open(ext_file_name, std::ios::in | std::ios::binary);
		if(!ext_file) construct_from_empty();
		else ext_file.close(), construct_from_last();
  }
  ~BPT(){
		ext_file.open(ext_file_name, std::ios::out | std::ios::binary);
		ext_file.seekp(0, std::ios::beg);
		ext_file.write(reinterpret_cast<char *>(&node_count), 4);
		ext_file.write(reinterpret_cast<char *>(&current_size), 4);
		ext_file.write(reinterpret_cast<char *>(&root), 4);
		ext_file.write(reinterpret_cast<char *>(&internal_loc), 4);
		ext_file.write(reinterpret_cast<char *>(&leaf_loc), 4);
		for(int i = 1; i <= MAX_N; ++i) ext_file.write(reinterpret_cast<char *>(&is_leaf[i]), 1);
		for(int i = 1; i <= MAX_N; ++i) ext_file.write(reinterpret_cast<char *>(&loc[i]), 4);
		for(int i = 1; i <= MAX_N; ++i) ext_file.write(reinterpret_cast<char *>(&lb[i]), 4);
		for(int i = 1; i <= MAX_N; ++i) ext_file.write(reinterpret_cast<char *>(&rb[i]), 4);
		ext_file.close();
    for(int i = 1; i <= MAX_cache; ++i) 
      if(cache[i] != nullptr){
        Write_back(cache[i], cache_id[i]);
        delete[] cache[i];
      }
    delete[] cache;
    delete[] cache_id;
    delete[] loc;
    delete[] is_leaf;
    delete[] lb;
    delete[] rb;
  }
  /*
    Following are some auxiliary arrays to store the data of the current node.
    Only used when Insert/Delete/Find.
  */
  // Above.
private:
  struct ret_data{
    bool splited;
    T1 y_index;
		T2 y_value;
    int new_node_id;
    ret_data(): splited(false){}
    ret_data(const bool &splited_, const T1 &y_index_, const T2 &y_value_, const int &new_node_id_): 
    splited(splited_), y_index(y_index_), y_value(y_value_), new_node_id(new_node_id_){}
    ret_data(const ret_data &other){
      splited = other.splited;
      y_index = other.y_index;
			y_value = other.y_value;
      new_node_id = other.new_node_id;
    }
  };
  int in_cache(int node_id){
    for(int i = 1; i <= MAX_cache; ++i) if(cache[i] != nullptr && cache_id[i] == node_id) return i;
    return 0;
  }
  void Write_back(char *s, int node_id){
    if(is_leaf[node_id]){
      leaf_file.open(leaf_file_name, std::ios::in | std::ios::out | std::ios::binary);
      leaf_file.seekp(loc[node_id], std::ios::beg);
      leaf_file.write(s, 4096);
      leaf_file.close();
    }
    else {
      internal_file.open(internal_file_name, std::ios::in | std::ios::out | std::ios::binary);
      internal_file.seekp(loc[node_id], std::ios::beg);
      internal_file.write(s, 4096);
      internal_file.close();
    }
    return ;
  }
  struct page{
    bool is_leaf, modified;
    int node_id, size;
    char *s;
    BPT *bpt;
    T1 *p_index; 
    T2 *p_value;
    int *chd_id;
    page(int node_id_, BPT *bpt_): bpt(bpt_), node_id(node_id_){
      s = new char[4096]();
      modified = false;
      int where = bpt->in_cache(node_id);
      if(where != 0){
        memcpy(s, bpt->cache[where], 4096);
      }
      else {
        if(bpt->is_leaf[node_id] == false){
          bpt->internal_file.open(bpt->internal_file_name, std::ios::in | std::ios::out | std::ios::binary);
          bpt->internal_file.seekg(bpt->loc[node_id], std::ios::beg);
          bpt->internal_file.read(s, 4096);
          bpt->internal_file.close();
        }
        else {
          bpt->leaf_file.open(bpt->leaf_file_name, std::ios::in | std::ios::out | std::ios::binary);
          bpt->leaf_file.seekg(bpt->loc[node_id], std::ios::beg);
          bpt->leaf_file.read(s, 4096);
          bpt->leaf_file.close();
        }
        int find_loc = 0;
        for(int i = 1; i <= bpt->MAX_cache; ++i) if(bpt->cache[i] == nullptr) find_loc = i;
        if(find_loc == 0){
          int t = rand() % bpt->MAX_cache + 1;
          bpt->Write_back(bpt->cache[t], bpt->cache_id[t]);
          find_loc = t;
        }
        bpt->cache_id[find_loc] = node_id;
        if(bpt->cache[find_loc] == nullptr) bpt->cache[find_loc] = new char[4096];
        memcpy(bpt->cache[find_loc], s, 4096);
      }
      if(bpt->is_leaf[node_id] == false){
        is_leaf = false;
        int ptr = 0;
        Read(s, ptr, size);
        p_index = new T1[bpt->M + 5]();
        p_value = new T2[bpt->M + 5]();
        chd_id = new int[bpt->M + 5]();
        for(int i = 1; i <= size - 1; ++i) Read(s, ptr, p_index[i]);
        for(int i = 1; i <= size - 1; ++i) Read(s, ptr, p_value[i]);
        for(int i = 1; i <= size; ++i) Read(s, ptr, chd_id[i]);
      }
      else{
        is_leaf = true;
        int ptr = 0;
        Read(s, ptr, size);
        p_index = new T1[bpt->L + 5]();
        p_value = new T2[bpt->L + 5]();
        chd_id = nullptr;
        for(int i = 1; i <= size; ++i) Read(s, ptr, p_index[i]);
        for(int i = 1; i <= size; ++i) Read(s, ptr, p_value[i]);
      }
    }
    page(int node_id_, char *node_s, BPT *bpt_){
      s = new char[4096]();
      memcpy(s, node_s, 4096);
      modified = true;
			node_id = node_id_;
			bpt = bpt_;
      int find_loc = 0;
      for(int i = 1; i <= bpt->MAX_cache; ++i) if(bpt->cache[i] == nullptr) find_loc = i;
      if(find_loc == 0){
        int t = rand() % bpt->MAX_cache + 1;
        bpt->Write_back(bpt->cache[t], bpt->cache_id[t]);
        find_loc = t;
      }
      bpt->cache_id[find_loc] = node_id;
      if(bpt->cache[find_loc] == nullptr) bpt->cache[find_loc] = new char[4096];
      memcpy(bpt->cache[find_loc], s, 4096);
      if(bpt->is_leaf[node_id] == false){
        is_leaf = false;
        int ptr = 0;
        Read(s, ptr, size);
        p_index = new T1[bpt->M + 5]();
        p_value = new T2[bpt->M + 5]();
        chd_id = new int[bpt->M + 5]();
        for(int i = 1; i <= size - 1; ++i) Read(s, ptr, p_index[i]);
        for(int i = 1; i <= size - 1; ++i) Read(s, ptr, p_value[i]);
        for(int i = 1; i <= size; ++i) Read(s, ptr, chd_id[i]);
      }
      else{
        is_leaf = true; 
        int ptr = 0;
        Read(s, ptr, size);
        p_index = new T1[bpt->L + 5]();
        p_value = new T2[bpt->L + 5]();
        chd_id = nullptr;
        for(int i = 1; i <= size; ++i) Read(s, ptr, p_index[i]);
        for(int i = 1; i <= size; ++i) Read(s, ptr, p_value[i]);
      }
    }
    ~page(){
      int where = bpt->in_cache(node_id);
      if(modified == true){
        if(is_leaf == false){
					int ptr = 0;
					memset(s, 0, 4096);
					Write(s, ptr, size);
					for(int i = 1; i <= size - 1; ++i) Write(s, ptr, p_index[i]);
					for(int i = 1; i <= size - 1; ++i) Write(s, ptr, p_value[i]);
					for(int i = 1; i <= size; ++i) Write(s, ptr, chd_id[i]);
					if(where == 0){
            bpt->internal_file.open(bpt->internal_file_name, std::ios::in | std::ios::out | std::ios::binary);
					  bpt->internal_file.seekp(bpt->loc[node_id], std::ios::beg);
					  bpt->internal_file.write(s, 4096);
					  bpt->internal_file.close();
          }
				}
				else{
					int ptr = 0;
					memset(s, 0, 4096);
					Write(s, ptr, size);
					for(int i = 1; i <= size; ++i) Write(s, ptr, p_index[i]);
					for(int i = 1; i <= size; ++i) Write(s, ptr, p_value[i]);
					if(where == 0){
            bpt->leaf_file.open(bpt->leaf_file_name, std::ios::in | std::ios::out | std::ios::binary);
					  bpt->leaf_file.seekp(bpt->loc[node_id], std::ios::beg);
					  bpt->leaf_file.write(s, 4096);
					  bpt->leaf_file.close();
          }
				}
        if(where != 0){
          memcpy(bpt->cache[where], s, 4096);
        }
      }
			delete[] s;
      delete[] p_index;
      delete[] p_value;
      delete[] chd_id;
    }
  };
  ret_data Insert_(int now, const T1 &x_index, const T2 &x_value){
    page cur(now, this); 
    if(is_leaf[now] == true){
      cur.modified = true;
      int l = 0, r = cur.size;
      while(l < r){
        int mid = l + r + 1 >> 1;
        if(mid == 0 || x_index > cur.p_index[mid] || (x_index == cur.p_index[mid] && x_value >= cur.p_value[mid])) l = mid;
        else r = mid - 1;
      }
      if(x_index == cur.p_index[l] && x_value == cur.p_value[l]){
        cur.modified = false;
        return ret_data();
      }
      current_size = current_size + 1;
      int ins_loc = l + 1;
      for(int i = cur.size + 1; i > ins_loc; --i) cur.p_index[i] = cur.p_index[i - 1];
      for(int i = cur.size + 1; i > ins_loc; --i) cur.p_value[i] = cur.p_value[i - 1];
      cur.p_index[ins_loc] = x_index;
      cur.p_value[ins_loc] = x_value;
      cur.size = cur.size + 1;
      if(cur.size <= L) return ret_data();
      int s1 = cur.size / 2, s2 = cur.size - s1;
      node_count = node_count + 1;
      is_leaf[node_count] = true;
      loc[node_count] = leaf_loc; 
      leaf_loc = leaf_loc + 4096;
      int ptr = 0;
      char *temp = new char[4096]();
      Write(temp, ptr, s2);
      for(int i = 1; i <= s2; ++i) Write(temp, ptr, cur.p_index[s1 + i]);
      for(int i = 1; i <= s2; ++i) Write(temp, ptr, cur.p_value[s1 + i]);
      assert(ptr <= 4096);
      page new_splited(node_count, temp, this);
      for(int i = 1; i <= s2; ++i){
        cur.p_index[s1 + i] = T1();
        cur.p_value[s1 + i] = T2();
      }
      cur.size = s1;
      delete temp; 
      return ret_data(true, new_splited.p_index[1], new_splited.p_value[1], node_count);
    }
    else {
      int l = 1, r = cur.size;
      while(l < r){
        int mid = l + r + 1 >> 1;
        if(mid == 1 || x_index > cur.p_index[mid - 1] || (x_index == cur.p_index[mid - 1] && x_value >= cur.p_value[mid - 1])) l = mid;
        else r = mid - 1;
      }
      int ins_loc = l;
      ret_data res = Insert_(cur.chd_id[ins_loc], x_index, x_value);
      if(res.splited == true){
        cur.modified = true;
        for(int i = cur.size; i > ins_loc; --i) cur.p_index[i] = cur.p_index[i - 1];
        for(int i = cur.size; i > ins_loc; --i) cur.p_value[i] = cur.p_value[i - 1];
        for(int i = cur.size + 1; i > ins_loc + 1; --i) cur.chd_id[i] = cur.chd_id[i - 1];
        cur.p_index[ins_loc] = res.y_index;
				cur.p_value[ins_loc] = res.y_value;
        cur.chd_id[ins_loc + 1] = res.new_node_id;
        if(is_leaf[res.new_node_id]){
          lb[res.new_node_id] = cur.chd_id[ins_loc];
          rb[res.new_node_id] = rb[cur.chd_id[ins_loc]];
          if(rb[cur.chd_id[ins_loc]] != 0) lb[rb[cur.chd_id[ins_loc]]] = res.new_node_id;
          rb[cur.chd_id[ins_loc]] = res.new_node_id;
        } 
        cur.size = cur.size + 1;
        if(cur.size <= M) return ret_data();
        int s1 = (cur.size + 1) / 2 - 1, s2 = cur.size - s1 - 2; // 关键字数量
        node_count = node_count + 1;
        is_leaf[node_count] = false;
        loc[node_count] = internal_loc; 
        internal_loc = internal_loc + 4096;
        int ptr = 0;
        char *temp = new char[4096]();
        Write(temp, ptr, s2 + 1);
        for(int i = 1; i <= s2; ++i) Write(temp, ptr, cur.p_index[s1 + 1 + i]);
        for(int i = 1; i <= s2; ++i) Write(temp, ptr, cur.p_value[s1 + 1 + i]);
        for(int i = 1; i <= s2 + 1; ++i) Write(temp, ptr, cur.chd_id[s1 + 1 + i]);
        assert(ptr <= 4096);
        page new_splited(node_count, temp, this);
				T1 tmp_index = cur.p_index[s1 + 1];
				T2 tmp_value = cur.p_value[s1 + 1];
        for(int i = s1 + 1; i <= cur.size - 1; ++i){
          cur.p_index[i] = T1();
          cur.p_value[i] = T2();
        }
        for(int i = s1 + 2; i <= cur.size; ++i) cur.chd_id[i] = 0;
        cur.size = s1 + 1;
        delete temp; 
        return ret_data(true, tmp_index, tmp_value, node_count);
      }
      else return res;
    }
    assert(0);
		return ret_data();
  }
public:
  void Insert(const T1 &x_index, const T2 &x_value){
    ret_data res = Insert_(root, x_index, x_value);
    if(res.splited == true){
      node_count = node_count + 1;
      is_leaf[node_count] = false;
      loc[node_count] = internal_loc; 
      internal_loc = internal_loc + 4096;
      int ptr = 0;
      char *temp = new char[4096]();
      Write(temp, ptr, 2);
      Write(temp, ptr, res.y_index);
      Write(temp, ptr, res.y_value);
      Write(temp, ptr, root);
      Write(temp, ptr, res.new_node_id);
      assert(ptr <= 4096);
      root = node_count;
      page new_splited(node_count, temp, this);
			delete temp;
    }
    return ;
  }
  void Find(const T1 &x_index){
    if(current_size == 0){
      std::cout << "null\n";
      return ;
    }
    sjtu::vector <T2> ans;
    int now = root;
    while(!is_leaf[now]){
      page cur(now, this);
      int leng = cur.size; int find_loc = 1;
      for(int i = 1; i <= leng - 1; ++i) 
				if(x_index > cur.p_index[i]) find_loc = i + 1;
				else break;
      now = cur.chd_id[find_loc];
    }
    while(true){
      bool flag = true;
      page cur(now, this);
      for(int i = 1; i <= cur.size; ++i)
        if(cur.p_index[i] == x_index) ans.push_back(cur.p_value[i]);
        else if(cur.p_index[i] > x_index){
          flag = false;
          break;
        }
      if(flag == false || rb[now] == 0) break;
      now = rb[now];
    }
    if(ans.size() == 0){
      std::cout << "null\n";
      return ;
    }
    //QuickSort<T2>::sort(ans, 0, ans.size() - 1, std::less<T2>());
    for(int i = 0; i < ans.size(); ++i){
      std::cout << ans[i];
      if(i < ans.size() - 1) std::cout << " ";
      else std::cout << "\n";
    }
    return ;
  }
  bool Delete_(int now, const T1 &x_index, const T2 &x_value){
    page cur(now, this);
    if(is_leaf[now]){
      for(int i = 1; i <= cur.size; ++i) 
        if(cur.p_index[i] == x_index && cur.p_value[i] == x_value){
				  for(int j = i; j <= cur.size - 1; ++j) cur.p_index[j] = cur.p_index[j + 1];
					for(int j = i; j <= cur.size - 1; ++j) cur.p_value[j] = cur.p_value[j + 1];
					cur.size = cur.size - 1;
					cur.modified = true;
					current_size = current_size - 1;
					break;
				} 
        else if(cur.p_index[i] > x_index || (cur.p_index[i] == x_index && cur.p_value[i] > x_value)) break;
      if(cur.size >= L / 2) return false;
      else return true;
    }
    else {
      int del_loc = 1;
      for(int i = 1; i <= cur.size - 1; ++i)
        if(x_index > cur.p_index[i] || (x_index == cur.p_index[i] && x_value >= cur.p_value[i])) del_loc = i + 1;
        else break;
      bool to_merge = Delete_(cur.chd_id[del_loc], x_index, x_value);
      if(to_merge == false || cur.size == 1) return false;
      page mid(cur.chd_id[del_loc], this);
      int flag = true;
      if(is_leaf[mid.node_id] == false){
        //try left
        if(del_loc > 1){
          page left(cur.chd_id[del_loc - 1], this);
          if(left.size + mid.size <= M){
            cur.modified = true;
            left.modified = true;
            mid.modified = true; // can be better(the space that "cur" occupied can be recycled.)
            int s1 = left.size, s2 = mid.size;
            mid.size = 0, left.size = s1 + s2;
            left.p_index[s1] = cur.p_index[del_loc - 1];
            left.p_value[s1] = cur.p_value[del_loc - 1];
            for(int i = 1; i <= s2 - 1; ++i){
              left.p_index[s1 + i] = mid.p_index[i];
              left.p_value[s1 + i] = mid.p_value[i];
              mid.p_index[i] = T1();
              mid.p_value[i] = T2();
            } 
            for(int i = 1; i <= s2; ++i){
              left.chd_id[s1 + i] = mid.chd_id[i];
              mid.chd_id[i] = 0;
            }
            for(int i = del_loc - 1; i <= cur.size - 1; ++i){
              cur.p_index[i] = cur.p_index[i + 1];
              cur.p_value[i] = cur.p_value[i + 1];
            }
            for(int i = del_loc; i <= cur.size; ++i) cur.chd_id[i] = cur.chd_id[i + 1];
            cur.size = cur.size - 1;
          }
          else {
            cur.modified = true;
            left.modified = true;
            mid.modified = true;
            int s1 = left.size, s2 = mid.size;
            mid.size = mid.size + 1, left.size = left.size - 1;
            for(int i = s2; i >= 2; --i){
              mid.p_index[i] = mid.p_index[i - 1];
              mid.p_value[i] = mid.p_value[i - 1];
            }
            for(int i = s2 + 1; i >= 2; --i) mid.chd_id[i] = mid.chd_id[i - 1];
            mid.p_index[1] = cur.p_index[del_loc - 1];
            mid.p_value[1] = cur.p_value[del_loc - 1];
            mid.chd_id[1] = left.chd_id[s1];
            cur.p_index[del_loc - 1] = left.p_index[s1 - 1];
            cur.p_value[del_loc - 1] = left.p_value[s1 - 1];
          }
        }
        else {
          page right(cur.chd_id[del_loc + 1], this);
          if(right.size + mid.size <= M){
            cur.modified = true;
            right.modified = true;
            mid.modified = true; // can be better(the space that "cur" occupied can be recycled.)
            int s1 = mid.size, s2 = right.size;
            mid.size = s1 + s2, right.size = 0;
            mid.p_index[s1] = cur.p_index[del_loc];
            mid.p_value[s1] = cur.p_value[del_loc];
            for(int i = 1; i <= s2 - 1; ++i){
              mid.p_index[s1 + i] = right.p_index[i];
              mid.p_value[s1 + i] = right.p_value[i];
              right.p_index[i] = T1();
              right.p_value[i] = T2();
            } 
            for(int i = 1; i <= s2; ++i){
              mid.chd_id[s1 + i] = right.chd_id[i];
              right.chd_id[i] = 0;
            }
            for(int i = del_loc; i <= cur.size - 1; ++i){
              cur.p_index[i] = cur.p_index[i + 1];
              cur.p_value[i] = cur.p_value[i + 1];
            }
            for(int i = del_loc + 1; i <= cur.size; ++i) cur.chd_id[i] = cur.chd_id[i + 1];
            cur.size = cur.size - 1;
          }
          else {
            cur.modified = true;
            right.modified = true;
            mid.modified = true;
            int s1 = right.size, s2 = mid.size;
            mid.size = mid.size + 1, right.size = right.size - 1;
            mid.p_index[s2] = cur.p_index[del_loc];
            mid.p_value[s2] = cur.p_value[del_loc];
            mid.chd_id[s2 + 1] = right.chd_id[1];
            cur.p_index[del_loc] = right.p_index[1];
            cur.p_value[del_loc] = right.p_value[1];
            for(int i = 1; i <= s1 - 2; ++i){
              right.p_index[i] = right.p_index[i + 1];
              right.p_value[i] = right.p_value[i + 1];
            }
            for(int i = 1; i <= s1 - 1; ++i) right.chd_id[i] = right.chd_id[i + 1];
          }
        }
      }
      else {
        if(del_loc > 1){
          page left(cur.chd_id[del_loc - 1], this);
          if(left.size + mid.size <= L){
            cur.modified = true;
            left.modified = true;
            mid.modified = true; // can be better(the space that "cur" occupied can be recycled.)
            rb[left.node_id] = rb[mid.node_id];
            if(rb[mid.node_id] != 0) lb[rb[mid.node_id]] = left.node_id; 
            int s1 = left.size, s2 = mid.size;
            mid.size = 0, left.size = s1 + s2;
            for(int i = 1; i <= s2; ++i){
              left.p_index[s1 + i] = mid.p_index[i];
              left.p_value[s1 + i] = mid.p_value[i];
              mid.p_index[i] = T1();
              mid.p_value[i] = T2();
            } 
            for(int i = del_loc - 1; i <= cur.size - 1; ++i){
              cur.p_index[i] = cur.p_index[i + 1];
              cur.p_value[i] = cur.p_value[i + 1];
            }
            for(int i = del_loc; i <= cur.size; ++i) cur.chd_id[i] = cur.chd_id[i + 1];
            cur.size = cur.size - 1;
          }
          else {
            cur.modified = true;
            left.modified = true;
            mid.modified = true;
            int s1 = left.size, s2 = mid.size;
            mid.size = mid.size + 1, left.size = left.size - 1;
            for(int i = s2 + 1; i >= 2; --i){
              mid.p_index[i] = mid.p_index[i - 1];
              mid.p_value[i] = mid.p_value[i - 1];
            }
            mid.p_index[1] = left.p_index[s1];
            mid.p_value[1] = left.p_value[s1];
            cur.p_index[del_loc - 1] = mid.p_index[1];
            cur.p_value[del_loc - 1] = mid.p_value[1];
          }
        }
        else {
          page right(cur.chd_id[del_loc + 1], this);
          if(right.size + mid.size <= L){
            cur.modified = true;
            right.modified = true;
            mid.modified = true; // can be better(the space that "cur" occupied can be recycled.)
            rb[mid.node_id] = rb[right.node_id];
            if(rb[right.node_id] != 0) lb[rb[right.node_id]] = mid.node_id;
            int s1 = mid.size, s2 = right.size;
            mid.size = s1 + s2, right.size = 0;
            for(int i = 1; i <= s2; ++i){
              mid.p_index[s1 + i] = right.p_index[i];
              mid.p_value[s1 + i] = right.p_value[i];
              right.p_index[i] = T1();
              right.p_value[i] = T2();
            } 
            for(int i = del_loc; i <= cur.size - 1; ++i){
              cur.p_index[i] = cur.p_index[i + 1];
              cur.p_value[i] = cur.p_value[i + 1];
            }
            for(int i = del_loc + 1; i <= cur.size; ++i) cur.chd_id[i] = cur.chd_id[i + 1];
            cur.size = cur.size - 1;
          }
          else {
            cur.modified = true;
            right.modified = true;
            mid.modified = true;
            int s1 = right.size, s2 = mid.size;
            mid.size = mid.size + 1, right.size = right.size - 1;
            mid.p_index[s2 + 1] = right.p_index[1];
            mid.p_value[s2 + 1] = right.p_value[1];
            cur.p_index[del_loc] = right.p_index[2];
            cur.p_value[del_loc] = right.p_value[2];
            for(int i = 1; i <= s1 - 1; ++i){
              right.p_index[i] = right.p_index[i + 1];
              right.p_value[i] = right.p_value[i + 1];
            }
          }
        }
      }
      if(cur.size >= M / 2) return false;
      else return true;
    }
    assert(0);
    return false;
  }
  void Delete(const T1 &x_index, const T2 &x_value){
    if(current_size == 0) return ;
    Delete_(root, x_index, x_value);
    // while(true){
    //   page cur(root, this);
    //   if(cur.size > 1 || is_leaf[cur.chd_id[1]]) break;
    //   root = cur.chd_id[1];
    // }
    return ;
  }
	ret_data print(int now){
		ret_data res;
		remosk printf("node_id = %d, ", now);
		remosk {
			if(is_leaf[now]) printf("leaf, ");
			else printf("internal, ");
		}
		char temp[4096];
		if(is_leaf[now]){
			leaf_file.open(leaf_file_name, std::ios::in | std::ios::binary);
			leaf_file.seekg(loc[now], std::ios::beg);
			leaf_file.read(temp, 4096);
			leaf_file.close();
			int size, ptr = 0; 
			Read(temp, ptr, size);
			T1 *p_index = new T1[size + 1];
			T2 *p_value = new T2[size + 1];
			remosk printf("size = %d, ", size);
			for(int i = 1; i <= size; ++i) Read(temp, ptr, p_index[i]);
			for(int i = 1; i <= size; ++i) Read(temp, ptr, p_value[i]);
			for(int i = 1; i <= size - 1; ++i)
				if(p_index[i] > p_index[i + 1]) assert(0);
				else if(p_index[i] == p_index[i + 1] && p_value[i] > p_value[i + 1]) assert(0);
			remosk for(int i = 1; i <= size; ++i) std::cout << "(" << p_index[i] << ", " << p_value[i] << "), ";
			remosk printf("\n");
			if(size >= 1) res = ret_data(true, p_index[1], p_value[1], 0);
			delete[] p_index;
			delete[] p_value;
		}
		else {
			internal_file.open(internal_file_name, std::ios::in | std::ios::binary);
			internal_file.seekg(loc[now], std::ios::beg);
			internal_file.read(temp, 4096);
			internal_file.close();
			int size, ptr = 0; 
			Read(temp, ptr, size);
			T1 *p_index = new T1[size];
			T2 *p_value = new T2[size];
			int *chd_id = new int[size + 1];
			remosk printf("size = %d, ", size);
			for(int i = 1; i <= size - 1; ++i) Read(temp, ptr, p_index[i]);
			for(int i = 1; i <= size - 1; ++i) Read(temp, ptr, p_value[i]);
			for(int i = 1; i <= size; ++i) Read(temp, ptr, chd_id[i]);
			if(size <= 0) assert(0);
			for(int i = 1; i <= size - 2; ++i) 
				if(p_index[i] > p_index[i + 1]) assert(0);
				else if(p_index[i] == p_index[i + 1] && p_value[i] > p_value[i + 1]) assert(0);
			remosk std::cout << chd_id[1] << ", "; 
			remosk {
				for(int i = 1; i <= size - 1; ++i){
					std::cout << "(" << p_index[i] << ", " << p_value[i] << "), ";
					std::cout << chd_id[i + 1] << ", ";
				}
			}
			remosk printf("\n");
			remosk for(int i = 1; i <= size; ++i){
				ret_data tmp = print(chd_id[i]);
				if(i >= 2 && (p_index[i - 1] > tmp.y_index || (p_index[i - 1] == tmp.y_index && p_value[i - 1] > tmp.y_value))) assert(0);
				if(i <= size - 1 && (p_index[i + 1] < tmp.y_index || (p_index[i + 1] == tmp.y_index && p_value[i + 1] <= tmp.y_value))) assert(0);
			}
			if(size >= 2) res = ret_data(true, p_index[1], p_value[1], 0);
			delete[] p_index;
			delete[] p_value;
			delete[] chd_id;
		}
		return res;
	}
	void print(){
		print(root);
		return ;
	}
	void check_rb(){
		int fik_count = 0;
		for(int i = 1; i <= node_count; ++i) if(is_leaf[i] && rb[i] == 0) ++fik_count;
		assert(fik_count == 1);
		return ;
	}
};
