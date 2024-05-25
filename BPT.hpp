#ifndef Inc
#define Inc

#include <string>
#include <iostream>
#include <memory>
#include <cstdio>
#include <fstream>
#include <functional>
#include <cassert>
#include <cstdlib>

#endif

const bool Printing = false;
#define remosk if(Printing == true)

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
	void construct_from_empty();
	void construct_from_last();
  BPT(const int &m, const int &l, const std::string &internal_file_name_, const std::string &leaf_file_name_, 
	const std::string &ext_file_name_, const int &MAX_N_, const int &MAX_cache_);
  ~BPT();
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
    ret_data();
    ret_data(const bool &splited_, const T1 &y_index_, const T2 &y_value_, const int &new_node_id_);
    ret_data(const ret_data &other);
  };
  struct find_data{
    T1 y_index;
    T2 y_value;
    bool flag;
    find_data();
    find_data(const T1 &y_index_, const T2 &y_value_);
  };
  int in_cache(int node_id);
  void Write_back(char *s, int node_id);
  struct page{
    bool is_leaf, modified;
    int node_id, size;
    char *s;
    BPT *bpt;
    T1 *p_index; 
    T2 *p_value;
    int *chd_id;
    page(int node_id_, BPT *bpt_);
    page(int node_id_, char *node_s, BPT *bpt_);
    ~page();
  };
  ret_data Insert_(int now, const T1 &x_index, const T2 &x_value);
public:
  void Insert(const T1 &x_index, const T2 &x_value);
  void Find(const T1 &x_index);
  bool Delete_(int now, const T1 &x_index, const T2 &x_value);
  void Delete(const T1 &x_index, const T2 &x_value);
	ret_data print(int now);
	void print();
	void check_rb();
};
