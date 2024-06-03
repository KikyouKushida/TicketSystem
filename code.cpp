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
#include "ticket.hpp"

template<class T>
T str_to_num(const std::string &str){
  T res = 0;
  for(int i = 0; i < str.size(); ++i){
    res *= 10;
    res += str[i] - '0';
  }
  return res;
}

template<class T>
sjtu::vector<T> numlist_to_num(const std::string &str, const int &required_length){
  sjtu::vector<T> res;
  for(int i = 0, j; i < str.size(); i = j + 1){
    j = i;
    if(!isdigit(str[i])) continue;
    while(j + 1 < str.size() && isdigit(str[j + 1])) ++j;
    res.push_back(str_to_num<T>(str.substr(i, j - i + 1)));
  }
  assert(res.size() == required_length);
  return res;
}

template<class T>
sjtu::vector<T> numlist_to_num(const std::string &str){
  sjtu::vector<T> res;
  for(int i = 0, j; i < str.size(); i = j + 1){
    j = i;
    if(!isdigit(str[i])) continue;
    while(j + 1 < str.size() && isdigit(str[j + 1])) ++j;
    res.push_back(str_to_num<T>(str.substr(i, j - i + 1)));
  }
  return res;
}

sjtu::vector<Char> zhlist_to_zh(const std::string &str, const int &required_length){
  sjtu::vector<Char> res;
  for(int i = 0, j; i < str.size(); i = j + 1){
    j = i;
    if(str[i] == '|') continue;
    while(j + 1 < str.size() && str[j + 1] != '|') ++j;
    res.push_back(Char(str.substr(i, j - i + 1), 31));
  }
  assert(res.size() == required_length);
  return res;
}

sjtu::vector<Char> zhlist_to_zh(const std::string &str){
  sjtu::vector<Char> res;
  for(int i = 0, j; i < str.size(); i = j + 1){
    j = i;
    if(str[i] == '|') continue;
    while(j + 1 < str.size() && str[j + 1] != '|') ++j;
    res.push_back(Char(str.substr(i, j - i + 1), 31));
  }
  return res;
}

int to_time(const std::string &time_str){
  return str_to_num<int>(time_str.substr(1, time_str.size() - 2));
}

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

void add_train(){
  sjtu::vector<std::string> input;
  read_line(input);
  Char *train_id;
  int stationNum, seatNum;
  char type;
  sjtu::vector<int> prices, stopoverTimes, travelTimes, TMP;
  sjtu::vector<Char> stations;
  Date *saleDate_from, *saleDate_to;
  sjtu::vector<Date> saleDate;
  Moment *startTime;
  for(int i = 0; i < input.size(); i += 2){
    if(input[i] == "-i") train_id = new Char(input[i + 1], 21);
    else if(input[i] == "-n") stationNum = str_to_num<int> (input[i + 1]);
    else if(input[i] == "-m") seatNum = str_to_num<int> (input[i + 1]);
    else if(input[i] == "-s") stations = zhlist_to_zh(input[i + 1]);
    else if(input[i] == "-p") prices = numlist_to_num<int> (input[i + 1]);
    else if(input[i] == "-x") {
      TMP = numlist_to_num<int> (input[i + 1]);
      startTime = new Moment(TMP[0], TMP[1]);
    }
    else if(input[i] == "-t") travelTimes = numlist_to_num<int> (input[i + 1]);
    else if(input[i] == "-o") stopoverTimes = numlist_to_num<int> (input[i + 1]);
    else if(input[i] == "-d") {
      TMP = numlist_to_num<int> (input[i + 1]);
      saleDate_from = new Date(TMP[0], TMP[1]);
      saleDate_to = new Date(TMP[2], TMP[3]);
      saleDate.push_back(*saleDate_from);
      saleDate.push_back(*saleDate_to);
    }
    else if(input[i] == "-y") type = input[i + 1][0];
    else assert(0);
  }
  Train_system.Add_train(*train_id, stationNum, seatNum, stations, prices, *startTime, travelTimes, stopoverTimes, saleDate, type);
  delete train_id;
  delete saleDate_from;
  delete saleDate_to;
  delete startTime;
  return ;
}

void delete_train(){
  sjtu::vector<std::string> input;
  read_line(input);
  Char *train_id;
  for(int i = 0; i < input.size(); i += 2){
    if(input[i] == "-i") train_id = new Char(input[i + 1], 21);
    else assert(0);
  }
  Train_system.Delete_train(*train_id);
  delete train_id;
  return ;
}

void release_train(){
  sjtu::vector<std::string> input;
  read_line(input);
  Char *train_id;
  for(int i = 0; i < input.size(); i += 2){
    if(input[i] == "-i") train_id = new Char(input[i + 1], 21);
    else assert(0);
  }
  Train_system.Release_train(*train_id);
  delete train_id;
  return ;
}

void query_train(){
  sjtu::vector<std::string> input;
  read_line(input);
  Char *train_id;
  Date *date;
  sjtu::vector<int> TMP;
  for(int i = 0; i < input.size(); i += 2){
    if(input[i] == "-i") train_id = new Char(input[i + 1], 21);
    else if(input[i] == "-d"){
      TMP = numlist_to_num<int> (input[i + 1]);
      date = new Date(TMP[0], TMP[1]);
    }
    else assert(0);
  }
  Train_system.Query_train(*train_id, *date);
  delete train_id;
  delete date;
  return ;
}

void query_ticket(){
  sjtu::vector<std::string> input;
  read_line(input);
  Char *station_from, *station_to;
  Date *date;
  std::string sort_parameter;
  sjtu::vector<int> TMP;
  for(int i = 0; i < input.size(); i += 2){
    if(input[i] == "-s") station_from = new Char(input[i + 1], 31);
    else if(input[i] == "-t") station_to = new Char(input[i + 1], 31);
    else if(input[i] == "-d"){
      TMP = numlist_to_num<int> (input[i + 1]);
      date = new Date(TMP[0], TMP[1]);
    }
    else if(input[i] == "-p") sort_parameter = input[i + 1];
  }
  Train_system.Query_ticket(*station_from, *station_to, *date, sort_parameter);
  delete station_from;
  delete station_to;
  delete date;
  return ;
}

void query_transfer(){
  sjtu::vector<std::string> input;
  read_line(input);
  Char *station_from, *station_to;
  Date *date;
  std::string sort_parameter;
  sjtu::vector<int> TMP;
  for(int i = 0; i < input.size(); i += 2){
    if(input[i] == "-s") station_from = new Char(input[i + 1], 31);
    else if(input[i] == "-t") station_to = new Char(input[i + 1], 31);
    else if(input[i] == "-d"){
      TMP = numlist_to_num<int> (input[i + 1]);
      date = new Date(TMP[0], TMP[1]);
    }
    else if(input[i] == "-p") sort_parameter = input[i + 1];
  }
  Train_system.Query_transfer(*station_from, *station_to, *date, sort_parameter);
  delete station_from;
  delete station_to;
  delete date;
  return ;
}

void buy_ticket(){

}

void refund_ticket(){

}

void clean(){

}

void query_order(){

}

//#include <unistd.h>

account_system Account_system(300, 300, 10000, 400);
train_system Train_system(300, 300, 10000, 400); // to be modified

int main(){
  //freopen("../1.in", "r", stdin);
  //freopen("../1.out", "w", stdout);
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
    else if(oper_str == "add_train") add_train();
    else if(oper_str == "release_train") release_train();
    else if(oper_str == "delete_train") delete_train();
    else if(oper_str == "query_train") query_train();
    else if(oper_str == "query_ticket") query_ticket();
    else if(oper_str == "query_transfer") query_transfer();
    else if(oper_str == "buy_ticket") buy_ticket();
    else if(oper_str == "refund_ticket") refund_ticket();
    else if(oper_str == "query_order") query_order();
    else if(oper_str == "clean") clean();
    else if(oper_str == "exit"){ exit(); break; }
    //sleep(0.2);
  }
  return 0;
}