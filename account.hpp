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

class account_system{
  struct index_type{
    Char user_name;
    index_type(const std::string &user_name_): user_name(user_name_, 20){}
    index_type(const index_type &other): user_name(other.user_name){}
  };
  struct value_type{
    Char password, name, mailAddr;
    int privilege;
    value_type(const std::string &password_, const std::string &name_, const std::string &mailAddr_, int &privilege_):
    pass_word(pass_word_, 30), name(name_, 15), mailAddr(mailAddr_, 30), privilege(privilege_){}
    value_type(const value_type &other): password(other.password), name(other.name), mailAddr(other.mailAddr), privilege(other.privilege){}
  };
  class account{
    index_type index;
    value_type value;
    account() = deleted;
    account(const std::string &user_name_, const std::string &password_, const std::string &name_, const std::string &mailAddr_, int &privilege_);
    account(const account &other);
    account &operator=(const account &other);
    ~account();
  }
  BPT *logined, *existed;
  account_system();
};