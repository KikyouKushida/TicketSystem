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
private:
  struct index_type{
    ull username;
    index_type(): username(0){}
    index_type(const ull &username_): user_name(username_){}
    index_type(const index_type &other): user_name(other.username){}
  };
  struct value_type{
    int loc;
    value_type(): loc(-1){}
    value_type(int &loc_): loc(loc_){}
  };
  struct account_data{
    Char *username, *password, *name, *mailAddr;
    int privilege;
    account_data() = deleted;
    account_data(int loc){
      ordered_user_file.open("ordered_user_data.txt", std::ios::in | std::ios::binary);
      ordered_user_file.seekg(loc, std::ios::beg);
      user_name = new Char(ordered_user_data, 20);
      password = new Char(ordered_user_file, 30);
      name = new Char(ordered_user_file, 15);
      mailAddr = new Char(ordered_user_file, 30);
      ordered_user_file.read(reinterpret_cast<char*>(&privilege), sizeof(int));
      ordered_user_file.close();
    }
    void show(){
      std::cout << username << " " << name << " " << mailAddr << " " << privilege << "\n";
      return ;
    }
  }
  std::fstream ordered_user_file, other_file;
  BPT *logined, *added;
  int user_count;
  const int length_per_user;
  account_system() = deleted;
  account_system(const int &M, const int &L, const int &MAX_N, const int &MAX_cache);
  int add_user(const Char &cur_username, const Char &x_username, const Char &x_password, const Char &x_name, const Char &x_mailAddr, const int &x_privilege);
  int login(const Char &x_username, const Char &x_password);
  int logout(const Char &x_username);
  int query_profile(const Char &cur_username, const Char &x_username);
  int modify_profile(const Char *cur_username, const Char &x_username, const Char &x_password, const Char &x_name, const Char &x_mailAddr, const int &x_privilege);
  bool have_logined(const Char &this_username);
  bool have_added(const Char &this_username);
public:
  void Add_user(const Char &cur_username, const Char &x_username, const Char &x_password, const Char &x_name, const Char &x_mailAddr, const int &x_privilege);
  void Login(const Char &x_username, const Char &x_password);
  void Logout(const Char &x_username);
  void Query_profile(const Char &cur_username, const Char &x_username);
  void Modify_profile(const Char &cur_username, const Char &x_username, const Char &x_password, const Char &x_name, const Char &x_mailAddr, const int &x_privilege);
};