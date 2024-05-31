#include "BPT.hpp"

template<class T1, class T2>
void BPT<T1, T2>::construct_from_empty(){
  internal_file.open(internal_file_name, std::ios::out | std::ios::binary);
  leaf_file.open(leaf_file_name, std::ios::out | std::ios::binary);
  ext_file.open(ext_file_name, std::ios::out | std::ios::binary);
  internal_file.close();
  leaf_file.close();
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
  delete[] temp;
  return ;
}

template<class T1, class T2>
void BPT<T1, T2>::clear(){
  for(int i = 1; i <= MAX_cache; ++i) delete cache[i];
  delete[] cache;
  delete[] cache_id;
  cache = new char*[MAX_cache + 5];
  for(int i = 1; i <= MAX_cache; ++i) cache[i] = nullptr;
  cache_id = new int[MAX_cache + 5];
  for(int i = 1; i <= MAX_cache; ++i) cache_id[i] = 0;

  internal_file.open(internal_file_name, std::ios::out | std::ios::binary);
  leaf_file.open(leaf_file_name, std::ios::out | std::ios::binary);
  ext_file.open(ext_file_name, std::ios::out | std::ios::binary);
  internal_file.close();
  leaf_file.close();
  ext_file.close();
  node_count = 0;
  current_size = 0;
  internal_loc = 0;
  leaf_loc = 0;
  delete[] loc;
  delete[] is_leaf;
  delete[] lb;
  delete[] rb;
  loc = new int[MAX_N + 5]();
  is_leaf = new bool[MAX_N + 5]();
  lb = new int[MAX_N + 5]();
  rb = new int[MAX_N + 5]();
  node_count = node_count + 1;
  root = node_count;
  is_leaf[node_count] = false;
  loc[node_count] = internal_loc; 
  internal_loc = internal_loc + 4096;
  char *temp = new char[4096]();
  int ptr = 0;
  Write(temp, ptr, 1);
  Write(temp, ptr, node_count + 1);
  page one_internal_node(node_count, temp, this);
  node_count = node_count + 1;
  is_leaf[node_count] = true;
  loc[node_count] = leaf_loc;
  leaf_loc = leaf_loc + 4096;
  memset(temp, 0, 4096);
  ptr = 0;
  Write(temp, ptr, 0);
  page one_leaf_node(node_count, temp, this);
  delete[] temp;
  return ;
}

template<class T1, class T2>
void BPT<T1, T2>::construct_from_last(){
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

template<class T1, class T2>
BPT<T1, T2>::BPT(const int &m, const int &l, const std::string &internal_file_name_, const std::string &leaf_file_name_, 
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

template<class T1, class T2>
BPT<T1, T2>::~BPT(){
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
      delete cache[i];
    }
  delete[] cache;
  delete[] cache_id;
  delete[] loc;
  delete[] is_leaf;
  delete[] lb;
  delete[] rb;
}

template<class T1, class T2>
BPT<T1, T2>::ret_data::ret_data(): splited(false){}

template<class T1, class T2>
BPT<T1, T2>::ret_data::ret_data(const bool &splited_, const T1 &y_index_, const int &new_node_id_): 
splited(splited_), y_index(y_index_), new_node_id(new_node_id_){}

template<class T1, class T2>
BPT<T1, T2>::ret_data::ret_data(const ret_data &other){
  splited = other.splited;
  y_index = other.y_index;
  new_node_id = other.new_node_id;
}

template<class T1, class T2>
int BPT<T1, T2>::in_cache(int node_id){
  for(int i = 1; i <= MAX_cache; ++i) if(cache[i] != nullptr && cache_id[i] == node_id) return i;
  return 0;
}

template<class T1, class T2>
void BPT<T1, T2>::Write_back(char *s, int node_id){
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

template<class T1, class T2>
BPT<T1, T2>::page::page(int node_id_, BPT *bpt_): bpt(bpt_), node_id(node_id_){
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
    p_value = nullptr;
    chd_id = new int[bpt->M + 5]();
    for(int i = 1; i <= size - 1; ++i) p_index[i].Read(s, ptr);
    for(int i = 1; i <= size; ++i) Read(s, ptr, chd_id[i]);
  }
  else{
    is_leaf = true;
    int ptr = 0;
    Read(s, ptr, size);
    p_index = new T1[bpt->L + 5]();
    p_value = new T2[bpt->L + 5]();
    chd_id = nullptr;
    for(int i = 1; i <= size; ++i) p_index[i].Read(s, ptr);
    for(int i = 1; i <= size; ++i) p_value[i].Read(s, ptr);
  }
}

template<class T1, class T2>
BPT<T1, T2>::page::page(int node_id_, char *node_s, BPT *bpt_){
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
    p_value = nullptr;
    chd_id = new int[bpt->M + 5]();
    for(int i = 1; i <= size - 1; ++i) p_index[i].Read(s, ptr);
    for(int i = 1; i <= size; ++i) Read(s, ptr, chd_id[i]);
  }
  else{
    is_leaf = true; 
    int ptr = 0;
    Read(s, ptr, size);
    p_index = new T1[bpt->L + 5]();
    p_value = new T2[bpt->L + 5]();
    chd_id = nullptr;
    for(int i = 1; i <= size; ++i) p_index[i].Read(s, ptr);
    for(int i = 1; i <= size; ++i) p_value[i].Read(s, ptr);
  }
}

template<class T1, class T2>
BPT<T1, T2>::page::~page(){
  int where = bpt->in_cache(node_id);
  if(modified == true){
    if(is_leaf == false){
      int ptr = 0;
      memset(s, 0, 4096);
      Write(s, ptr, size);
      for(int i = 1; i <= size - 1; ++i) p_index[i].Write(s, ptr);
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
      for(int i = 1; i <= size; ++i) p_index[i].Write(s, ptr);
      for(int i = 1; i <= size; ++i) p_value[i].Write(s, ptr);
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
  if(p_value == nullptr);
  else delete[] p_value;
  if(chd_id == nullptr);
  else delete[] chd_id;
}

template<class T1, class T2>
typename BPT<T1, T2>::ret_data BPT<T1, T2>::Insert_(int now, const T1 &x_index, const T2 &x_value){
  page cur(now, this); 
  if(is_leaf[now] == true){
    cur.modified = true;
    int l = 0, r = cur.size;
    while(l < r){
      int mid = l + r + 1 >> 1;
      if(mid == 0 || x_index >= cur.p_index[mid]) l = mid;
      else r = mid - 1;
    }
    if(l > 0 && x_index == cur.p_index[l]){
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
    for(int i = 1; i <= s2; ++i) cur.p_index[s1 + i].Write(temp, ptr);
    for(int i = 1; i <= s2; ++i) cur.p_value[s1 + i].Write(temp, ptr);
    assert(ptr <= 4096);
    page new_splited(node_count, temp, this);
    for(int i = 1; i <= s2; ++i){
      cur.p_index[s1 + i] = T1();
      cur.p_value[s1 + i] = T2();
    }
    cur.size = s1;
    delete[] temp; 
    return ret_data(true, new_splited.p_index[1], node_count);
  }
  else {
    int l = 1, r = cur.size;
    while(l < r){
      int mid = l + r + 1 >> 1;
      if(mid == 1 || x_index >= cur.p_index[mid - 1]) l = mid;
      else r = mid - 1;
    }
    int ins_loc = l;
    ret_data res = Insert_(cur.chd_id[ins_loc], x_index, x_value);
    if(res.splited == true){
      cur.modified = true;
      for(int i = cur.size; i > ins_loc; --i) cur.p_index[i] = cur.p_index[i - 1];
      for(int i = cur.size + 1; i > ins_loc + 1; --i) cur.chd_id[i] = cur.chd_id[i - 1];
      cur.p_index[ins_loc] = res.y_index;
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
      for(int i = 1; i <= s2; ++i) cur.p_index[s1 + 1 + i].Write(temp, ptr);
      for(int i = 1; i <= s2 + 1; ++i) Write(temp, ptr, cur.chd_id[s1 + 1 + i]);
      assert(ptr <= 4096);
      page new_splited(node_count, temp, this);
      T1 tmp_index = cur.p_index[s1 + 1];
      for(int i = s1 + 1; i <= cur.size - 1; ++i){
        cur.p_index[i] = T1();
      }
      for(int i = s1 + 2; i <= cur.size; ++i) cur.chd_id[i] = 0;
      cur.size = s1 + 1;
      delete[] temp; 
      return ret_data(true, tmp_index, node_count);
    }
    else return res;
  }
  assert(0);
  return ret_data();
}

template<class T1, class T2>
void BPT<T1, T2>::Insert(const T1 &x_index, const T2 &x_value){
  ret_data res = Insert_(root, x_index, x_value);
  if(res.splited == true){
    node_count = node_count + 1;
    is_leaf[node_count] = false;
    loc[node_count] = internal_loc; 
    internal_loc = internal_loc + 4096;
    int ptr = 0;
    char *temp = new char[4096]();
    Write(temp, ptr, 2);
    res.y_index.Write(temp, ptr);
    Write(temp, ptr, root);
    Write(temp, ptr, res.new_node_id);
    assert(ptr <= 4096);
    root = node_count;
    page new_splited(node_count, temp, this);
    delete[] temp;
  }
  return ;
}

template<class T1, class T2>
bool BPT<T1, T2>::Delete_(int now, const T1 &x_index){
  page cur(now, this);
  if(is_leaf[now]){
    for(int i = 1; i <= cur.size; ++i) 
      if(cur.p_index[i] == x_index){
        for(int j = i; j <= cur.size - 1; ++j) cur.p_index[j] = cur.p_index[j + 1];
        for(int j = i; j <= cur.size - 1; ++j) cur.p_value[j] = cur.p_value[j + 1];
        cur.size = cur.size - 1;
        cur.modified = true;
        current_size = current_size - 1;
        break;
      } 
      else if(cur.p_index[i] > x_index) break;
    if(cur.size >= L / 2) return false;
    else return true;
  }
  else {
    int del_loc = 1;
    for(int i = 1; i <= cur.size - 1; ++i)
      if(x_index >= cur.p_index[i]) del_loc = i + 1;
      else break;
    bool to_merge = Delete_(cur.chd_id[del_loc], x_index);
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
          for(int i = 1; i <= s2 - 1; ++i){
            left.p_index[s1 + i] = mid.p_index[i];
            mid.p_index[i] = T1();
          } 
          for(int i = 1; i <= s2; ++i){
            left.chd_id[s1 + i] = mid.chd_id[i];
            mid.chd_id[i] = 0;
          }
          for(int i = del_loc - 1; i <= cur.size - 1; ++i){
            cur.p_index[i] = cur.p_index[i + 1];
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
          }
          for(int i = s2 + 1; i >= 2; --i) mid.chd_id[i] = mid.chd_id[i - 1];
          mid.p_index[1] = cur.p_index[del_loc - 1];
          mid.chd_id[1] = left.chd_id[s1];
          cur.p_index[del_loc - 1] = left.p_index[s1 - 1];
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
          for(int i = 1; i <= s2 - 1; ++i){
            mid.p_index[s1 + i] = right.p_index[i];
            right.p_index[i] = T1();
          } 
          for(int i = 1; i <= s2; ++i){
            mid.chd_id[s1 + i] = right.chd_id[i];
            right.chd_id[i] = 0;
          }
          for(int i = del_loc; i <= cur.size - 1; ++i){
            cur.p_index[i] = cur.p_index[i + 1];
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
          mid.chd_id[s2 + 1] = right.chd_id[1];
          cur.p_index[del_loc] = right.p_index[1];
          for(int i = 1; i <= s1 - 2; ++i){
            right.p_index[i] = right.p_index[i + 1];
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

template<class T1, class T2>
void BPT<T1, T2>::Delete(const T1 &x_index){
  if(current_size == 0) return ;
  Delete_(root, x_index);
  return ;
}

template<class T1, class T2>
typename BPT<T1, T2>::ret_data BPT<T1, T2>::print(int now){
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
    for(int i = 1; i <= size; ++i) p_index[i].Read(temp, ptr);
    for(int i = 1; i <= size; ++i) p_value[i].Read(temp, ptr);
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
    for(int i = 1; i <= size - 1; ++i) p_index[i].Read(temp, ptr);
    for(int i = 1; i <= size - 1; ++i) p_value[i].Read(temp, ptr);
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
    if(size >= 2) res = ret_data(true, p_index[1], 0);
    delete[] p_index;
    delete[] p_value;
    delete[] chd_id;
  }
  return res;
}

template<class T1, class T2>
void BPT<T1, T2>::print(){
  print(root);
  return ;
}

template<class T1, class T2>
void BPT<T1, T2>::check_rb(){
  int fik_count = 0;
  for(int i = 1; i <= node_count; ++i) if(is_leaf[i] && rb[i] == 0) ++fik_count;
  assert(fik_count == 1);
  return ;
}

template<class T1, class T2>
T2 BPT<T1, T2>::find(const T1 &x_index){
  if(current_size == 0) return T2(); 
  int now = root;
  while(!is_leaf[now]){
    page cur(now, this);
    int leng = cur.size; int find_loc = 1;
    for(int i = 1; i <= leng - 1; ++i) 
      if(x_index >= cur.p_index[i]) find_loc = i + 1;
      else break;
    now = cur.chd_id[find_loc];
  }
  bool flag = true;
  page cur(now, this);
  for(int i = 1; i <= cur.size; ++i)
    if(cur.p_index[i] == x_index) 
      return cur.p_value[i]; 
    else if(cur.p_index[i] > x_index) 
      break;
  return T2();
}

template<class T1, class T2>
bool BPT<T1, T2>::is_scratch(){
  return node_count == 0;
}