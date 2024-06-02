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

#ifndef ticket_
#define ticker_

#include "BPT.hpp"

const int day_per_month[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct Time{
  int month, day;
  int hour, minute;
  Time() = delete;
  Time(const int &month_, const int &day_, const int &hour_, const int &minute_){
    month = month_;
    day = day_;
    hour = hour_;
    minute = minute_;
  }
  Time(const Time &other){
    month = other.month;
    day = other.day;
    hour = other.hour;
    minute = other.minute;
  }
  friend Time operator+(const Time &now, const int &dminute){
    Time other(now);
    other.minute += dminute;
    other.hour += other.minute / 60;
    other.minute %= 60;
    other.day += other.hour / 24;
    other.hour %= 24;
    while(other.day > day_per_month[other.month]){
      if(other.month == 12) assert(0);
      other.day -= day_per_month[other.month];
      other.month += 1;
    }
    return other;
  }
};

class train_system{
  struct index_type{

  };
  struct value_type{
    
  };
  BPT<index_type, value_type> *added, *released;

};


#endif