#include "ticket.hpp"

train_system::train_system(const int &M, const int &L, const int &MAX_N, const int &MAX_cache){
  released = new BPT<index_type, value_type>(M, L, "train_logined_internal_data.txt", "train_logined_leaf_data.txt", "train_logined_ext_data.txt", MAX_N, MAX_cache);
  added = new BPT<index_type, value_type>(M, L, "train_added_internal_data.txt", "train_added_leaf_data.txt", "train_added_ext_data.txt", MAX_N, MAX_cache);
  train_other_file.open("train_other_data.txt", std::ios::in | std::ios::binary);
  if(!train_other_file){
    train_other_file.close();
    train_other_file.open("train_other_data.txt", std::ios::out | std::ios::binary);
    train_other_file.close();
    train_count = 0;
    current_ordered_file_pointer = 0;
    ordered_train_file.open("ordered_train_data.txt", std::ios::out | std::ios::binary);
    ordered_train_file.close();
  }
  else {
    train_other_file.seekg(0, std::ios::beg);
    train_other_file.read(reinterpret_cast<char *>(&train_count), sizeof(int));
    train_other_file.read(reinterpret_cast<char *>(&current_ordered_file_pointer), sizeof(int));
    train_other_file.close();
  }
}

train_system::~train_system(){
  delete added;
  delete released;
  train_other_file.open(train_other_file_name, std::ios::out | std::ios::binary);
  train_other_file.seekp(0, std::ios::beg);
  train_other_file.write(reinterpret_cast<char*>(&train_count), sizeof(int));
  train_other_file.write(reinterpret_cast<char *>(&current_ordered_file_pointer), sizeof(int));
  train_other_file.close();
}

bool train_system::have_released(const Char &this_train_id){
  value_type tmp_loc = released->find(index_type(this_train_id.my_hash()));
  if(tmp_loc.loc == -1) return false;
  return true;
}

bool train_system::have_added(const Char &this_train_id){
  value_type tmp_loc = added->find(index_type(this_train_id.my_hash()));
  if(tmp_loc.loc == -1) return false;
  return true;
}

void train_system::Add_train(
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
){
  int res = add_train(train_id, stationNum, seatNum, stations, prices, startTime, travelTimes, stopoverTimes, saleDate, type);
  std::cout << res << "\n";
  return ;
}

int train_system::add_train(
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
){
  if(have_added(train_id)) return -1;
  train_data tmp(train_id, stationNum, seatNum, stations, prices, startTime, travelTimes, stopoverTimes, saleDate, type);
  int size = tmp.get_size();
  added->Insert(index_type(train_id.my_hash()), value_type(current_ordered_file_pointer));
  train_count += 1;
  current_ordered_file_pointer += size;
  return 0;
}

void train_system::Release_train(const Char &train_id){
  int res = release_train(train_id);
  std::cout << res << "\n";
  return ;
}

int train_system::release_train(const Char &train_id){
  if(have_added(train_id) == false || have_released(train_id) == true) return -1;
  value_type cur_loc = added->find(index_type(train_id.my_hash()));
  released->Insert(index_type(train_id.my_hash()), cur_loc);
  return 0;
}

void train_system::Delete_train(const Char &train_id){
  int res = delete_train(train_id);
  std::cout << res << "\n";
  return ;
}

int train_system::delete_train(const Char &train_id){
  if(have_added(train_id) == false || have_released(train_id) == true) return -1;
  added->Delete(index_type(train_id.my_hash()));
  return 0;
}

void train_system::Query_train(const Char &train_id, const Date &date){
  int res = query_train(train_id, date);
  if(res == -1) std::cout << res << "\n";
  return ;
}

int train_system::query_train(const Char &train_id, const Date &date){
  if(have_added(train_id) == false) return -1;
  value_type cur_loc = added->find(index_type(train_id.my_hash()));
  train_data tmp(this, cur_loc.loc);
  if(*(tmp.saleDate_from) > date || *(tmp.saleDate_to) < date) return -1;
  std::cout << train_id << " " << tmp.type << "\n";
  Time now_time(date, *(tmp.startTime));
  int now_price = 0;
  for(int i = 0; i < tmp.stationNum; ++i){
    std::cout << *(tmp.stations[i]) << " ";
    if(i == 0) std::cout << "xx-xx xx:xx -> " << now_time << " ";
    else {
      now_time += tmp.travelTimes[i - 1];
      std::cout << now_time << " -> ";
      if(i == tmp.stationNum - 1) std::cout << "xx-xx : xx:xx ";
      else {
        now_time += tmp.stopoverTimes[i - 1];
        std::cout << now_time << " ";
      }
    }
    if(i == 0) std::cout << "0 ";
    else {
      now_price += tmp.prices[i - 1];
      std::cout << now_price << " ";
    } 
    if(i == tmp.stationNum - 1) std::cout << "x\n";
    else std::cout << tmp.seatNum << "\n";
  }
  return 0;
}

void train_system::add_train_with_station(const train_data &tmp){
  
}

void train_system::delete_train_with_station(const train_data &tmp){

}