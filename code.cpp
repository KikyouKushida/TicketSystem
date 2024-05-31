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
  return str_to_num<int>(time_str.substr(1, time_str.size() - 2));
}

account_system Account_system(300, 300, 10000, 400);

char S[100005];

void read_line(sjtu::vector<std::string> &input){
  std::cin.getline(S, 100000);
  int len = strlen(S);
  assert(len < 100000);
  input.clear(); 
  for(int i = 0, j; i < len; i = j + 1){
    j = i;
    if(S[i] == ' ' || S[i] == '\n') continue;
    std::string tmp;
    while(j + 1 < len && S[j + 1] != ' ' && S[j + 1] != '\n') ++j;
    for(int o = i; o <= j; ++o) tmp += S[o];
    input.push_back(tmp);
  }
  return ;
}

void add_user(){
  sjtu::vector<std::string> input;
  read_line(input);
  Char *username, *name, *cur_username, *password, *mailAddr;
  int privilege;
  for(int i = 0; i < input.size(); i += 2){
    if(input[i] == "-c") cur_username = new Char(input[i + 1], 21);
    else if(input[i] == "-u") username = new Char(input[i + 1], 21);
    else if(input[i] == "-g") privilege = str_to_num<int>(input[i + 1]);
    else if(input[i] == "-p") password = new Char(input[i + 1], 31);
    else if(input[i] == "-m") mailAddr = new Char(input[i + 1], 31);
    else if(input[i] == "-n") name = new Char(input[i + 1], 16);
    else assert(0);
  }
  Account_system.Add_user(*cur_username, *username, *password, *name, *mailAddr, privilege);
  delete username;
  delete name;
  delete mailAddr;
  delete password;
  delete cur_username;
  return ;
}

void login(){
  sjtu::vector<std::string> input;
  read_line(input);
  Char *username = nullptr, *password = nullptr;
  for(int i = 0; i < input.size(); i += 2){
    if(input[i] == "-u") username = new Char(input[i + 1], 21);
    else if(input[i] == "-p") password = new Char(input[i + 1], 31);
    else assert(0);
  } 
  Account_system.Login(*username, *password);
  delete username;
  delete password;
  return ;
}

void logout(){
  sjtu::vector<std::string> input;
  read_line(input);
  Char *username = nullptr;
  for(int i = 0; i < input.size(); i += 2){
    if(input[i] == "-u") username = new Char(input[i + 1], 21);
    else assert(0);
  }
  Account_system.Logout(*username);
  delete username;
  return ;
}

void query_profile(){
  sjtu::vector<std::string> input;
  read_line(input);
  Char *username = nullptr, *cur_username = nullptr;
  for(int i = 0; i < input.size(); i += 2){
    if(input[i] == "-c") cur_username = new Char(input[i + 1], 21);
    else if(input[i] == "-u") username = new Char(input[i + 1], 21);
    else assert(0);
  }
  Account_system.Query_profile(*cur_username, *username);
  delete cur_username;
  delete username;
  return ;
}

void modify_profile(){
  sjtu::vector<std::string> input;
  read_line(input);
  Char *username = nullptr, *name = nullptr, *cur_username = nullptr, *password = nullptr, *mailAddr = nullptr;
  int privilege = -1;
  for(int i = 0; i < input.size(); i += 2){
    if(input[i] == "-c") cur_username = new Char(input[i + 1], 21);
    else if(input[i] == "-u") username = new Char(input[i + 1], 21);
    else if(input[i] == "-g") privilege = str_to_num<int>(input[i + 1]);
    else if(input[i] == "-p") password = new Char(input[i + 1], 31);
    else if(input[i] == "-m") mailAddr = new Char(input[i + 1], 31);
    else if(input[i] == "-n") name = new Char(input[i + 1], 16);
    else assert(0);
  }
  if(password == nullptr) password = new Char(30);
  if(name == nullptr) name = new Char(15);
  if(mailAddr == nullptr) mailAddr = new Char(30);
  assert(username != nullptr && cur_username != nullptr);
  Account_system.Modify_profile(*cur_username, *username, *password, *name, *mailAddr, privilege);
  delete username;
  delete name;
  delete mailAddr;
  delete password;
  delete cur_username;
  return ;
}

void exit(){
  Account_system.Clear_logined();
  std::cout << "bye\n";
  return ;
}

//#include <unistd.h>

int main(){
  freopen("../1.in", "r", stdin);
  freopen("../1.out", "w", stdout);
  std::string time_str, oper_str;
  int time;
  while(true){
    std::cin >> time_str;
    time = to_time(time_str);
    std::cin >> oper_str;
    std::cout << time_str << " ";
    if(oper_str == "add_user") add_user();
    else if(oper_str == "login") login();
    else if(oper_str == "logout") logout();
    else if(oper_str == "query_profile") query_profile();
    else if(oper_str == "modify_profile") modify_profile();
    else if(oper_str == "exit"){ exit(); break; }
    //sleep(0.2);
  }
  return 0;
}