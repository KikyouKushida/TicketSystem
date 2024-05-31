#include <cstring>
#include <string>
#include <iostream>
#include <memory>
#include <cstdio>
#include <fstream>
#include <functional>
#include <cassert>
#include <cstdlib>

#pragma once

#include "general.hpp"

#ifndef account_
#define account_

#include "BPT.hpp"


class account_system{
private:
  struct index_type{
    ull username;
    index_type(): username(0){}
    index_type(const ull &username_): username(username_){}
    index_type(const index_type &other): username(other.username){}
    friend bool operator<(const index_type &x, const index_type &y){
      return x.username < y.username;
    }
    friend bool operator==(const index_type &x, const index_type &y){
      return x.username == y.username;
    }
    friend bool operator!=(const index_type &x, const index_type &y){
      return x.username != y.username;
    }
    friend bool operator>(const index_type &x, const index_type &y){
      return x.username > y.username;
    }
    friend bool operator<=(const index_type &x, const index_type &y){
      return x.username <= y.username;
    }
    friend bool operator>=(const index_type &x, const index_type &y){
      return x.username >= y.username;
    }
    friend std::ostream& operator << (std::ostream &os, const index_type &y){
      os << y.username;
      return os;
    } 
    void Write(char *s, int &loc){
      s[loc] = static_cast<unsigned char>((username >> 56) & 0xFF);
      s[loc + 1] = static_cast<unsigned char>((username >> 48) & 0xFF);
      s[loc + 2] = static_cast<unsigned char>((username >> 40) & 0xFF);
      s[loc + 3] = static_cast<unsigned char>((username >> 32) & 0xFF);
      s[loc + 4] = static_cast<unsigned char>((username >> 24) & 0xFF);
      s[loc + 5] = static_cast<unsigned char>((username >> 16) & 0xFF);
      s[loc + 6] = static_cast<unsigned char>((username >> 8) & 0xFF);
      s[loc + 7] = static_cast<unsigned char>(username & 0xFF);
      loc = loc + 8;
      return ;
    }
    void Read(char *s, int &loc){
      username = (ull(static_cast<unsigned char>(s[loc])) << 56) |
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
  };
  struct value_type{
    int loc;
    value_type(): loc(-1){}
    value_type(const int &loc_): loc(loc_){}
    void Write(char *s, int &loc_){
      s[loc_] = static_cast<unsigned char>((loc >> 24) & 0xFF);
      s[loc_ + 1] = static_cast<unsigned char>((loc >> 16) & 0xFF);
      s[loc_ + 2] = static_cast<unsigned char>((loc >> 8) & 0xFF);
      s[loc_ + 3] = static_cast<unsigned char>(loc & 0xFF);
      loc_ = loc_ + 4;
      return ;
    }
    void Read(char *s, int &loc_){
      loc = (static_cast<unsigned char>(s[loc_]) << 24) |
          (static_cast<unsigned char>(s[loc_ + 1]) << 16) |
          (static_cast<unsigned char>(s[loc_ + 2]) << 8) |
          (static_cast<unsigned char>(s[loc_ + 3]) << 0);
      loc_ = loc_ + 4;
      return ;
    }
    friend std::ostream& operator << (std::ostream &os, const value_type &y){
      os << y.loc;
      return os;
    } 
  };
  struct account_data{
    Char *username, *password, *name, *mailAddr;
    int privilege;
    account_data() = delete;
    account_data(account_system *bel, int loc){
      bel->ordered_user_file.open("ordered_user_data.txt", std::ios::in | std::ios::binary);
      bel->ordered_user_file.seekg(loc, std::ios::beg);
      username = new Char(bel->ordered_user_file, 20);
      password = new Char(bel->ordered_user_file, 30);
      name = new Char(bel->ordered_user_file, 15);
      mailAddr = new Char(bel->ordered_user_file, 30);
      bel->ordered_user_file.read(reinterpret_cast<char*>(&privilege), sizeof(int));
      bel->ordered_user_file.close();
    }
    void show(){
      std::cout << *username << " " << *name << " " << *mailAddr << " " << privilege << "\n";
      return ;
    }
  };
  std::fstream ordered_user_file, other_file;
  BPT<index_type, value_type> *logined, *added;
  int user_count;
  const int length_per_user;
  int add_user(const Char &cur_username, const Char &x_username, const Char &x_password, const Char &x_name, const Char &x_mailAddr, const int &x_privilege);
  int login(const Char &x_username, const Char &x_password);
  int logout(const Char &x_username);
  int query_profile(const Char &cur_username, const Char &x_username);
  int modify_profile(const Char &cur_username, const Char &x_username, const Char &x_password, const Char &x_name, const Char &x_mailAddr, const int &x_privilege);
  bool have_logined(const Char &this_username);
  bool have_added(const Char &this_username);
public:
  account_system() = delete;
  account_system(const int &M, const int &L, const int &MAX_N, const int &MAX_cache);
  ~account_system();
  void Add_user(const Char &cur_username, const Char &x_username, const Char &x_password, const Char &x_name, const Char &x_mailAddr, const int &x_privilege);
  void Login(const Char &x_username, const Char &x_password);
  void Logout(const Char &x_username);
  void Query_profile(const Char &cur_username, const Char &x_username);
  void Modify_profile(const Char &cur_username, const Char &x_username, const Char &x_password, const Char &x_name, const Char &x_mailAddr, const int &x_privilege);
  void Clear_logined();
};

#endif