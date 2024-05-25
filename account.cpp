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

#endif

#include "account.hpp"

account_system::account(const std::string &user_name_, const std::string &password_, const std::string &name_, const std::string &mailAddr_, int &privilege_):
index(user_name_), value(password_, name_, mailAddr_, privilege_){}

account_system::~account(){}

account_system::account(const account &other): index(other.index), value(other.value){}

account_system::account& account_system::operator=(const account &other){
  if(this == &other);
  else {
    index = index_type(other.index);
    value = value_type(other.value);
  }
  return *this;
}

account_system::account_system(){
  logined = new BPT()
}
