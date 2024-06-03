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

#ifndef ticket_
#define ticket_

#include "BPT.hpp"

const int day_per_month[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct Date{
  int month, day;
  Date(const int &month_, const int &day_){
    month = month_;
    day = day_;
  }
  Date(std::fstream &this_file){
    this_file.read(reinterpret_cast<char*>(&month), sizeof(int));
    this_file.read(reinterpret_cast<char*>(&day), sizeof(int));
  }
  void write(std::fstream &this_file){
    this_file.write(reinterpret_cast<char*>(&month), sizeof(int));
    this_file.write(reinterpret_cast<char*>(&day), sizeof(int));
    return ;
  }
  Date(const Date &other): month(other.month), day(other.day){}
  Date() = delete;
  friend Date operator+(const Date &now, const int &dday){
    Date other(now);
    other.day += dday;
    while(other.day > day_per_month[other.month]){
      if(other.month == 12) assert(0);
      other.day -= day_per_month[other.month];
      other.month += 1;
    }
    return other;
  }
  friend std::ostream& operator << (std::ostream &os, const Date &y){
    os << y.month << "-" << y.day;
    return os;
  } 
  friend bool operator<(const Date &a, const Date &b){
    if(a.month < b.month) return true;
    if(a.month == b.month || a.day < b.day) return true;
    return false;
  }
  friend bool operator==(const Date &a, const Date &b){
    if(a.month == b.month && a.day == b.day) return true;
    return false;
  }
  friend bool operator<=(const Date &a, const Date &b){
    if(a.month < b.month) return true;
    if(a.month == b.month || a.day <= b.day) return true;
    return false;
  }
  friend bool operator>(const Date &a, const Date &b){
    return b < a;
  }
  friend bool operator>=(const Date &a, const Date &b){
    return b <= a;
  }
  friend int operator-(const Date &a, const Date &b){
    int ans = 0;
    Date c = b;
    while(a.month != c.month){
      ans += day_per_month[c.month] - c.day + 1;
      c.month += 1;
      c.day = 1;
    }
    return ans + a.day - c.day;
  }
};

struct Moment{
  int hour, minute;
  Moment(const int &hour_, const int &minute_){
    hour = hour_;
    minute = minute_;
  }
  Moment(std::fstream &this_file){
    this_file.read(reinterpret_cast<char*>(&hour), sizeof(int));
    this_file.read(reinterpret_cast<char*>(&minute), sizeof(int));
  }
  void write(std::fstream &this_file){
    this_file.write(reinterpret_cast<char*>(&hour), sizeof(int));
    this_file.write(reinterpret_cast<char*>(&minute), sizeof(int));
    return ;
  }
  Moment(const Moment &other): hour(other.hour), minute(other.minute){}
  Moment() = delete;
  friend std::ostream& operator << (std::ostream &os, const Moment &y){
    os << y.hour << ":" << y.minute;
    return os;
  }
  friend bool operator<(const Moment &a, const Moment &b){
    if(a.hour < b.hour) return true;
    if(a.hour == b.hour || a.minute < b.minute) return true;
    return false;
  }
  friend bool operator==(const Moment &a, const Moment &b){
    if(a.hour == b.hour && a.minute == b.minute) return true;
    return false;
  }
  friend bool operator<=(const Moment &a, const Moment &b){
    if(a.hour < b.hour) return true;
    if(a.hour == b.hour || a.minute <= b.minute) return true;
    return false;
  }
  friend bool operator>(const Moment &a, const Moment &b){
    return b < a;
  }
  friend bool operator>=(const Moment &a, const Moment &b){
    return b <= a;
  }
};

struct Time{
  Date date;
  Moment moment;
  Time(const Date &date_, const Moment &moment_): date(date_), moment(moment_){}
  Time(const Time &other): date(other.date), moment(other.moment){}
  friend Time operator+(const Time &now, const int &dminute){
    Time ans = now;
    ans.moment.minute += dminute;
    ans.moment.hour += ans.moment.minute / 60;
    ans.moment.minute %= 60;
    ans.date.day += ans.moment.hour / 24;
    ans.moment.hour %= 24;
    while(ans.date.day > day_per_month[ans.date.month]){
      if(ans.date.month == 12) assert(0);
      ans.date.day -= day_per_month[ans.date.month];
      ans.date.month += 1;
    }
  }
  Time operator+=(const int &dminute){
    Time ans = (*this) + dminute;
    date = ans.date;
    moment = ans.moment;
    return *this;
  }
  friend std::ostream& operator << (std::ostream &os, const Time &y){
    os << y.date << " " << y.moment;
    return os;
  }
};

class train_system{
private:
  struct index_type{
    ull train_id;
    index_type(): train_id(0){}
    index_type(const ull &train_id_): train_id(train_id_){}
    index_type(const index_type &other): train_id(other.train_id){}
    friend bool operator<(const index_type &x, const index_type &y){
      return x.train_id < y.train_id;
    }
    friend bool operator==(const index_type &x, const index_type &y){
      return x.train_id == y.train_id;
    }
    friend bool operator!=(const index_type &x, const index_type &y){
      return x.train_id != y.train_id;
    }
    friend bool operator>(const index_type &x, const index_type &y){
      return x.train_id > y.train_id;
    }
    friend bool operator<=(const index_type &x, const index_type &y){
      return x.train_id <= y.train_id;
    }
    friend bool operator>=(const index_type &x, const index_type &y){
      return x.train_id >= y.train_id;
    }
    friend std::ostream& operator << (std::ostream &os, const index_type &y){
      os << y.train_id;
      return os;
    } 
    void Write(char *s, int &loc){
      s[loc] = static_cast<unsigned char>((train_id >> 56) & 0xFF);
      s[loc + 1] = static_cast<unsigned char>((train_id >> 48) & 0xFF);
      s[loc + 2] = static_cast<unsigned char>((train_id >> 40) & 0xFF);
      s[loc + 3] = static_cast<unsigned char>((train_id >> 32) & 0xFF);
      s[loc + 4] = static_cast<unsigned char>((train_id >> 24) & 0xFF);
      s[loc + 5] = static_cast<unsigned char>((train_id >> 16) & 0xFF);
      s[loc + 6] = static_cast<unsigned char>((train_id >> 8) & 0xFF);
      s[loc + 7] = static_cast<unsigned char>(train_id & 0xFF);
      loc = loc + 8;
      return ;
    }
    void Read(char *s, int &loc){
      train_id = (ull(static_cast<unsigned char>(s[loc])) << 56) |
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
  struct index_type2{
    ull station, train_id;
    index_type2(const ull &station_, const ull &train_id_): station(station_), train_id(train_id_){}
    index_type2(const index_type2 &other): station(other.station), train_id(other.train_id){}
    ull first(){
      return station;
    }
    void Write(char *s, int &loc){
      s[loc] = static_cast<unsigned char>((station >> 56) & 0xFF);
      s[loc + 1] = static_cast<unsigned char>((station >> 48) & 0xFF);
      s[loc + 2] = static_cast<unsigned char>((station >> 40) & 0xFF);
      s[loc + 3] = static_cast<unsigned char>((station >> 32) & 0xFF);
      s[loc + 4] = static_cast<unsigned char>((station >> 24) & 0xFF);
      s[loc + 5] = static_cast<unsigned char>((station >> 16) & 0xFF);
      s[loc + 6] = static_cast<unsigned char>((station >> 8) & 0xFF);
      s[loc + 7] = static_cast<unsigned char>(station & 0xFF);
      loc = loc + 8;
      s[loc] = static_cast<unsigned char>((train_id >> 56) & 0xFF);
      s[loc + 1] = static_cast<unsigned char>((train_id >> 48) & 0xFF);
      s[loc + 2] = static_cast<unsigned char>((train_id >> 40) & 0xFF);
      s[loc + 3] = static_cast<unsigned char>((train_id >> 32) & 0xFF);
      s[loc + 4] = static_cast<unsigned char>((train_id >> 24) & 0xFF);
      s[loc + 5] = static_cast<unsigned char>((train_id >> 16) & 0xFF);
      s[loc + 6] = static_cast<unsigned char>((train_id >> 8) & 0xFF);
      s[loc + 7] = static_cast<unsigned char>(train_id & 0xFF);
      loc = loc + 8; 
    }
    void Read(char *s, int &loc){
      station = (ull(static_cast<unsigned char>(s[loc])) << 56) |
          (ull(static_cast<unsigned char>(s[loc + 1])) << 48) |
          (ull(static_cast<unsigned char>(s[loc + 2])) << 40) |
          (ull(static_cast<unsigned char>(s[loc + 3])) << 32) |
          (ull(static_cast<unsigned char>(s[loc + 4])) << 24) |
          (ull(static_cast<unsigned char>(s[loc + 5])) << 16) |
          (ull(static_cast<unsigned char>(s[loc + 6])) << 8) |
          (ull(static_cast<unsigned char>(s[loc + 7])) << 0);
      loc = loc + 8;
      train_id = (ull(static_cast<unsigned char>(s[loc])) << 56) |
          (ull(static_cast<unsigned char>(s[loc + 1])) << 48) |
          (ull(static_cast<unsigned char>(s[loc + 2])) << 40) |
          (ull(static_cast<unsigned char>(s[loc + 3])) << 32) |
          (ull(static_cast<unsigned char>(s[loc + 4])) << 24) |
          (ull(static_cast<unsigned char>(s[loc + 5])) << 16) |
          (ull(static_cast<unsigned char>(s[loc + 6])) << 8) |
          (ull(static_cast<unsigned char>(s[loc + 7])) << 0);
      loc = loc + 8;
    }
    friend bool operator<(const index_type2 &a, const index_type2 &b){
      if(a.station < b.station) return true;
      if(a.station == b.station && a.train_id < b.train_id) return true;
      return false;
    }
    friend bool operator<=(const index_type2 &a, const index_type2 &b){
      if(a.station < b.station) return true;
      if(a.station == b.station && a.train_id <= b.train_id) return true;
      return false;
    } 
    friend bool operator>(const index_type2 &a, const index_type2 &b){
      return b < a;
    }
    friend bool operator>=(const index_type2 &a, const index_type2 &b){
      return b <= a;
    } 
    friend bool operator==(const index_type2 &a, const index_type2 &b){
      return a.station == b.station && a.train_id == b.train_id;
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
  struct train_data{
    Char *train_id;
    int stationNum, seatNum;
    Char** stations;
    int *prices, *stopoverTimes, *travelTimes;
    Date *saleDate_from, *saleDate_to;
    Moment *startTime;
    char type;
    train_data() = delete;
    train_data(
      const Char &train_id_, 
      const int &stationNum_, 
      const int &seatNum_, 
      sjtu::vector<Char> &stations_, 
      sjtu::vector<int> &prices_, 
      const Moment &startTime_, 
      sjtu::vector<int> &travelTimes_, 
      sjtu::vector<int> &stopoverTimes_, 
      sjtu::vector<Date> &saleDate_, 
      const char &type_
    ){
      train_id = new Char(train_id_);
      stationNum = stationNum_;
      seatNum = seatNum_;
      stations = new Char*[stations_.size()];
      for(int i = 0; i < stations_.size(); ++i) stations[i] = new Char(stations_[i]);
      prices = new int[prices_.size()];
      for(int i = 0; i < prices_.size(); ++i) prices[i] = prices_[i];
      startTime = new Moment(startTime_);
      travelTimes = new int[travelTimes_.size()];
      for(int i = 0; i < travelTimes_.size(); ++i) travelTimes[i] = travelTimes_[i];
      stopoverTimes = new int[stopoverTimes_.size()];
      for(int i = 0; i < stopoverTimes_.size(); ++i) stopoverTimes[i] = stopoverTimes_[i];
      saleDate_from = new Date(saleDate_[0]);
      saleDate_to = new Date(saleDate_[1]);
      type = type_;
    }
    train_data(train_system *bel, int loc){
      bel->ordered_train_file.open(bel->ordered_train_file_name, std::ios::in | std::ios::binary);
      bel->ordered_train_file.seekg(loc, std::ios::beg);
      train_id = new Char(bel->ordered_train_file, 31);
      bel->ordered_train_file.read(reinterpret_cast<char*>(&stationNum), sizeof(int));
      bel->ordered_train_file.read(reinterpret_cast<char*>(&seatNum), sizeof(int));
      stations = new Char*[stationNum];
      for(int i = 0; i < stationNum; ++i) stations[i] = new Char(bel->ordered_train_file, 31);
      prices = new int[stationNum];
      stopoverTimes = new int[stationNum];
      travelTimes = new int[stationNum];
      for(int i = 0; i < stationNum - 1; ++i) bel->ordered_train_file.read(reinterpret_cast<char*>(&prices[i]), sizeof(int));
      for(int i = 0; i < stationNum - 2; ++i) bel->ordered_train_file.read(reinterpret_cast<char*>(&stopoverTimes[i]), sizeof(int));
      for(int i = 0; i < stationNum - 1; ++i) bel->ordered_train_file.read(reinterpret_cast<char*>(&travelTimes[i]), sizeof(int));
      startTime = new Moment(bel->ordered_train_file);
      saleDate_from = new Date(bel->ordered_train_file);
      saleDate_to = new Date(bel->ordered_train_file);
      bel->ordered_train_file.read(&type, sizeof(char));
      bel->ordered_train_file.close();
    }
    void write(train_system *bel, int loc){
      bel->ordered_train_file.open(bel->ordered_train_file_name, std::ios::in | std::ios::out | std::ios::binary);
      bel->ordered_train_file.seekp(loc, std::ios::beg);
      train_id->write(bel->ordered_train_file);
      bel->ordered_train_file.write(reinterpret_cast<char*>(&stationNum), sizeof(int));
      bel->ordered_train_file.write(reinterpret_cast<char*>(&seatNum), sizeof(int));
      for(int i = 0; i < stationNum; ++i) stations[i]->write(bel->ordered_train_file);
      for(int i = 0; i < stationNum - 1; ++i) bel->ordered_train_file.write(reinterpret_cast<char*>(&prices[i]), sizeof(int));
      for(int i = 0; i < stationNum - 2; ++i) bel->ordered_train_file.write(reinterpret_cast<char*>(&stopoverTimes[i]), sizeof(int));
      for(int i = 0; i < stationNum - 1; ++i) bel->ordered_train_file.write(reinterpret_cast<char*>(&travelTimes[i]), sizeof(int));
      startTime->write(bel->ordered_train_file);
      saleDate_from->write(bel->ordered_train_file);
      saleDate_to->write(bel->ordered_train_file);
      bel->ordered_train_file.write(&type, sizeof(char));
      bel->ordered_train_file.close();
    }
    int get_size(){
      int n = stationNum;
      return 30 + 4 + 4 + n * 30 + (n - 1) * 4 + 8 + (n - 1) * 4 + (n - 2) * 4 + 16 + 1; 
    }
    ~train_data(){
      delete train_id;
      for(int i = 0; i < stationNum; ++i) delete stations[i];
      delete[] stations;
      delete[] prices;
      delete[] stopoverTimes;
      delete[] travelTimes;
      delete startTime;
      delete saleDate_from;
    }
  };
  struct Empty{
    Empty(){}
    void write(char *s, int *loc_){}
  }empty;
  struct QT{
    Time *leavingTime, *arrivingTime;
    Char *train_id;
    int price, seat, ttime;
    QT(const Time &leavingTime_, const Time &arrivingTime_, const Char &train_id_, const int &price_, const int &seat_, const int &ttime_){
      leavingTime = new Time(leavingTime_);
      arrivingTime = new Time(arrivingTime_);
      train_id = new Char(train_id_);
      price = price_;
      seat = seat_;
      ttime = ttime_;
    }
  };
  const std::string ordered_train_file_name, train_other_file_name;
  std::fstream ordered_train_file, train_other_file;
  BPT<index_type, value_type> *added, *released;
  BPT<index_type2, Empty> *train_with_station;
  int train_count, current_ordered_file_pointer;
  bool have_released(const Char &train_id);
  bool have_added(const Char &train_id);
  int add_train(
    const Char &train_id, 
    const int &stationNum, 
    const int &seatNum, 
    sjtu::vector<Char> &stations, 
    sjtu::vector<int> &prices, 
    const Moment &startTime, 
    sjtu::vector<int> &travelTimes, 
    sjtu::vector<int> &stopoverTimes, 
    sjtu::vector<Date> &saleDate, 
    const char &type
  );
  int release_train(const Char &train_id);
  int delete_train(const Char &train_id);
  int query_train(const Char &train_id, const Date &date);
  void add_train_with_station(const train_data &tmp);
  void delete_train_with_station(const train_data &tmp);
  int query_ticket(const Char &station_from, const Char &station_to, const Date &date, const std::string &sort_parameter);
public:
  train_system() = delete;
  train_system(const int &M, const int &L, const int &MAX_N, const int &MAX_cache);
  ~train_system();
  void Add_train(
    const Char &train_id, 
    const int &stationNum, 
    const int &seatNum, 
    sjtu::vector<Char> &stations, 
    sjtu::vector<int> &prices, 
    const Moment &startTime, 
    sjtu::vector<int> &travelTimes, 
    sjtu::vector<int> &stopoverTimes, 
    sjtu::vector<Date> &saleDate, 
    const char &type
  );
  void Release_train(const Char &train_id);
  void Delete_train(const Char &train_id);
  void Query_train(const Char &train_id, const Date &date);
  void Query_ticket(const Char &station_from, const Char &station_to, const Date &date, const std::string &sort_parameter);
  void Query_transfer(const Char &station_from, const Char &station_to, const Date &date, const std::string &sort_parameter);
};


#endif