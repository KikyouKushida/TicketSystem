#include <cstring>
#include <string>
#include <iostream>
#include <memory>
#include <cstdio>
#include <fstream>
#include <functional>
#include <cassert>
#include <cstdlib>

#include "general.hpp"
#include "BPT.hpp"
#include "account.hpp"

template<class T>
T str_to_num(const std::string &str){
  T res = 0;
  for(int i = 0; i < str.size(); ++i){
    res *= 10;
    res += str[i] - '0';
  }
  return res;
}

int to_time(const std::string &time_str){
  return str_to_num(time_str.substr(1, time_str.size() - 2));
}

int main(){
  account_system Account_system(320, 320, 10000, 400);
  std::string time_str, oper_str;
  int time;
  while(true){
    std::cin >> time_str;
    time = to_time(time_str);
    std::cin >> oper_str;
    if(oper_str == "")
  }
  return 0;
}