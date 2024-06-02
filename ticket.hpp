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
  Moment(const Moment &other): hour(other.hour), minute(other.minute){}
  Moment() = delete;
  friend std::ostream& operator << (std::ostream &os, const Moment &y){
    os << y.hour << ":" << y.minute;
    return os;
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
    train_data() = delete;
    train_data(train_system *bel, int loc){
      bel->ordered_train_file.open(bel->ordered_train_file_name, std::ios::in | std::ios::binary);
      bel->ordered_train_file.seekg(loc, std::ios::beg);
      train_id = new Char(bel->ordered_train_file, 31);
      bel->ordered_train_file.read(reinterpret_cast<char*>(&stationNum), sizeof(int));
      bel->ordered_train_file.read(reinterpret_cast<char*>(&seatNum), sizeof(int));
      stations = new Char*[stationNum];
      for(int i = 0; i < stationNum; ++i) stations[i] = new Char(bel->ordered_train_file, 31);
      int tmp_int;
      prices = new int[stationNum];
      stopoverTimes = new int[stationNum];
      travelTimes = new int[stationNum];
      for(int i = 0; i < stationNum - 1; ++i) bel->ordered_train_file.read(reinterpret_cast<char*>(&prices[i]), sizeof(int));
      for(int i = 0; i < stationNum - 2; ++i) bel->ordered_train_file.read(reinterpret_cast<char*>(&stopoverTimes[i]), sizeof(int));
      for(int i = 0; i < stationNum - 1; ++i) bel->ordered_train_file.read(reinterpret_cast<char*>(&travelTimes[i]), sizeof(int));
      startTime = new Moment(bel->ordered_train_file);
      saleDate_from = new Date(bel->ordered_train_file);
      saleDate_to = new Date(bel->ordered_train_file);
      bel->ordered_train_file.close();
    }
  };
  const std::string ordered_train_file_name;
  std::fstream ordered_train_file;
  BPT<index_type, value_type> *added, *released;

};


#endif