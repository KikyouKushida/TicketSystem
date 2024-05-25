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



class account_system{
  class account{
    Char *user_name, *password, *name, *mailAddr;
    int privilege;
    account(const std::string &user_name_, const std::string &password_, const std::string &name_, const std::string &mailAddr_, int &privilege_){
      user_name = Char(user_name_, 21);
      password = Char(password_, 31);
      name = Char(name_, 16);
      mailAddr = Char(mailAddr_, 31);
      privilege = privilege_;
    }
    ~account(){
      delete user_name;
      delete pass_word;
      delete name;
      delete mailAddr;
    }
  };
};