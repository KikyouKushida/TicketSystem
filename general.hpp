#ifndef Inc
#define Inc

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <filesystem>
#include <cassert>
#include <functional>
#include <memory>
#include "BPT.hpp"

#endif

int strlen(char *s){
  for(int i = 0;; ++i) if(s[i] == '\0') return i;
}

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

class Char{
public:
  char *s;
  int len, max_size;
public:
  Char(int &max_size_){
    s = new char[max_size]();
    len = 0;
    max_size = max_size_;
  }
  Char(char *ss, int &max_size_){
    max_size = max_size_;
    s = new char[max_size]();
    len = strlen(ss);
    for(int i = 0; i < max_size; ++i) s[i] = 0;
    for(int i = 0; i < len; ++i) s[i] = ss[i];
  }
  Char(const Char &other){
    max_size = max_size_;
    s = new char[max_size]();
    len = other.len;
    for(int i = 0; i < max_size; ++i) s[i] = 0;
    for(int i = 0; i < len; ++i) s[i] = other.s[i];
  }
	Char(const std::string &other, int &max_size_){
    max_size = max_size_;
		s = new char[max_size]();
		len = other.size();
		for(int i = 0; i < max_size; ++i) s[i] = 0;
		for(int i = 0; i < len; ++i) s[i] = other[i];
	}
  Char& operator=(const Char &other){
    if(this == (&other)) return *this;
    delete[] s;
    max_size = other.max_size;
    s = new char[max_size]();
    len = other.len;
    for(int i = 0; i < max_size; ++i) s[i] = 0;
    for(int i = 0; i < len; ++i) s[i] = other.s[i];
    return *this;
  }
  ~Char(){
    delete[] s;
  }
  int size() const{
    return len;
  }
  char& operator[](const int &loc) const{
    return s[loc];
  }
  friend bool operator<(const Char &a, const Char &b){
    int la = a.size(), lb = b.size();
    for(int i = 0; i < min(la, lb); ++i) 
			if(a[i] < b[i]) return true;
			else if(a[i] > b[i]) return false;
		return la < lb ? true : false;
  }
  friend bool operator>(const Char &a, const Char &b){
    return b < a;
  }
  friend bool operator==(const Char &a, const Char &b){
    if(a.size() != b.size()) return false;
    for(int i = 0; i < a.size(); ++i) if(a[i] != b[i]) return false;
    return true;
  }
  friend bool operator!=(const Char &a, const Char &b){
    return !(a == b);
  }
	friend std::ostream& operator << (std::ostream &os, Char &y){
    for(int i = 0; i < y.len; ++i) os << y[i];
    return os;
  } 
  ull hash(){
    ull res = 0;
    for(int i = 0; i < len; ++i) res *= 197, res += s[i] - 'a' + 5;
    return res;
  }
};

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

template<typename T>
class QuickSort {
public:
  static void swap(T &a, T &b){
    T c = a;
    a = b;
    b = c;
  }
  static void sort(sjtu::vector<T> &vec, int left, int right, std::function<bool(const T&, const T&)> cmp) {
    if(left < right) {
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