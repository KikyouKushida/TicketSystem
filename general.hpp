#ifndef Inc
#define Inc

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <filesystem>
#include "BPT.hpp"
#include <cassert>
#include <functional>
#include <memory>

#endif



int strlen(char *s){
  for(int i = 0;; ++i) if(s[i] == '\0') return i;
}

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