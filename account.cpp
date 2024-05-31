#include "account.hpp"

account_system::account_system(const int &M, const int &L, const int &MAX_N, const int &MAX_cache): length_per_user(103){
  logined = new BPT<index_type, value_type>(M, L, "account_logined_internal_data.txt", "account_logined_leaf_data.txt", "account_logined_ext_data.txt", MAX_N, MAX_cache);
  added = new BPT<index_type, value_type>(M, L, "account_added_internal_data.txt", "account_added_leaf_data.txt", "account_added_ext_data.txt", MAX_N, MAX_cache);
  other_file.open("other_data.txt", std::ios::in | std::ios::binary);
  if(!other_file){
    other_file.close();
    other_file.open("other_data.txt", std::ios::out | std::ios::binary);
    other_file.close();
    user_count = 0;
    ordered_user_file.open("ordered_user_data.txt", std::ios::out | std::ios::binary);
    ordered_user_file.close();
  }
  else {
    other_file.seekg(0, std::ios::beg);
    other_file.read(reinterpret_cast<char *>(&user_count), sizeof(int));
    other_file.close();
  }
}

account_system::~account_system(){
  other_file.open("other_data.txt", std::ios::out | std::ios::binary);
  other_file.seekp(0, std::ios::beg);
  other_file.write(reinterpret_cast<char *>(&user_count), sizeof(int));
  other_file.close();
}

bool account_system::have_logined(const Char &this_username){
  value_type tmp_loc = logined->find(index_type(this_username.my_hash()));
  if(tmp_loc.loc == -1) return false;
  return true;
}

bool account_system::have_added(const Char &this_username){
  value_type tmp_loc = added->find(index_type(this_username.my_hash()));
  if(tmp_loc.loc == -1) return false;
  return true;
}

void account_system::Add_user(const Char &cur_username, const Char &x_username, const Char &x_password, const Char &x_name, const Char &x_mailAddr, const int &x_privilege){
  int res = add_user(cur_username, x_username, x_password, x_name, x_mailAddr, x_privilege);
  std::cout << res << "\n";
  return ;
}

int account_system::add_user(const Char &cur_username, const Char &x_username, const Char &x_password, const Char &x_name, const Char &x_mailAddr, const int &x_privilege){
  if(user_count == 0){
    ordered_user_file.open("ordered_user_data.txt", std::ios::in | std::ios::out | std::ios::binary);
    ordered_user_file.seekp(user_count * length_per_user);
    x_username.write(ordered_user_file);
    x_password.write(ordered_user_file);
    x_name.write(ordered_user_file);
    x_mailAddr.write(ordered_user_file);
    int temp_privilege = 10;
    ordered_user_file.write(reinterpret_cast<const char*>(&temp_privilege), sizeof(int));
    ordered_user_file.close();
    added->Insert(index_type(x_username.my_hash()), value_type(user_count * length_per_user));
    user_count += 1;
    return 0;
  }
  if(have_logined(cur_username) == false) return -1;
  if(have_added(x_username) == true) return -1;
  value_type cur_loc = logined->find(index_type(cur_username.my_hash()));
  account_data cur_data(this, cur_loc.loc);
  if(cur_data.privilege <= x_privilege) return -1;
  ordered_user_file.open("ordered_user_data.txt", std::ios::in | std::ios::out | std::ios::binary);
  ordered_user_file.seekp(user_count * length_per_user);
  x_username.write(ordered_user_file);
  x_password.write(ordered_user_file);
  x_name.write(ordered_user_file);
  x_mailAddr.write(ordered_user_file);
  ordered_user_file.write(reinterpret_cast<const char*>(&x_privilege), sizeof(int));
  ordered_user_file.close();
  added->Insert(index_type(x_username.my_hash()), value_type(user_count * length_per_user));
  user_count += 1;
  return 0;
}

void account_system::Query_profile(const Char &cur_username, const Char &x_username){
  int res = query_profile(cur_username, x_username);
  if(res == -1) std::cout << res << "\n";
  return ;
}

int account_system::query_profile(const Char &cur_username, const Char &x_username){
  if(have_logined(cur_username) == false || have_added(x_username) == false) return -1;
  if(cur_username != x_username){
    value_type cur_loc = added->find(index_type(cur_username.my_hash())), x_loc = added->find(index_type(x_username.my_hash()));
    account_data cur_data(this, cur_loc.loc), x_data(this, x_loc.loc);
    if(cur_data.privilege <= x_data.privilege) return -1;
    x_data.show(); 
    return 0;
  }
  else {
    value_type cur_loc = added->find(index_type(cur_username.my_hash()));
    account_data cur_data(this, cur_loc.loc);
    cur_data.show();
    return 0;
  }
  assert(0);
  return 0;
}

void account_system::Login(const Char &cur_username, const Char &cur_password){
  int res = login(cur_username, cur_password);
  std::cout << res << "\n";
  return ;
}

int account_system::login(const Char &cur_username, const Char &cur_password){
  if(have_logined(cur_username) == true || have_added(cur_username) == false){
    std::cout << "error 1\n";
    return -1;
  }
  value_type cur_loc = added->find(index_type(cur_username.my_hash()));
  account_data cur_data(this, cur_loc.loc);
  if(cur_password != *(cur_data.password)){
    std::cout << "error 2\n";
    return -1;
  }
  logined->Insert(index_type(cur_username.my_hash()), value_type(cur_loc.loc));
  return 0;
}

void account_system::Logout(const Char &cur_username){
  int res = logout(cur_username);
  std::cout << res << "\n";
  return ;
}

int account_system::logout(const Char &cur_username){
  if(have_logined(cur_username) == false) return -1;
  logined->Delete(index_type(cur_username.my_hash()));
  return 0;
}

void account_system::Modify_profile(const Char &cur_username, const Char &x_username, const Char &x_password, const Char &x_name, const Char &x_mailAddr, const int &x_privilege){
  int res = modify_profile(cur_username, x_username, x_password, x_name, x_mailAddr, x_privilege);
  if(res == -1) std::cout << res << "\n";
  return ;
}

int account_system::modify_profile(const Char &cur_username, const Char &x_username, const Char &x_password, const Char &x_name, const Char &x_mailAddr, const int &x_privilege){
  if(have_logined(cur_username) == false || have_added(x_username) == false) return -1;
  if(cur_username != x_username){
    //std::cout << "step 1\n";
    value_type cur_loc = added->find(index_type(cur_username.my_hash())), x_loc = added->find(index_type(x_username.my_hash()));
    //std::cout << "step 2\n";
    account_data cur_data(this, cur_loc.loc), x_data(this, x_loc.loc);
   // std::cout << "step 3\n";
    if(cur_data.privilege <= x_data.privilege || x_privilege >= cur_data.privilege) return -1;
    //if(x_data.password == nullptr || x_data.name == nullptr || x_data.mailAddr == nullptr) std::cout << "fick 1\n";
    if(x_password.len != 0) *(x_data.password) = x_password;
    if(x_name.len != 0) *(x_data.name) = x_name;
    if(x_mailAddr.len != 0) *(x_data.mailAddr) = x_mailAddr;
    if(x_privilege != -1) x_data.privilege = x_privilege;
    x_data.show();
    ordered_user_file.open("ordered_user_data.txt", std::ios::in | std::ios::out | std::ios::binary);
    ordered_user_file.seekp(x_loc.loc);
    x_data.username->write(ordered_user_file);
    x_data.password->write(ordered_user_file);
    x_data.name->write(ordered_user_file);
    x_data.mailAddr->write(ordered_user_file);
    ordered_user_file.write(reinterpret_cast<char*>(&x_data.privilege), sizeof(int));
    ordered_user_file.close();
    //x_data.show(); 
    return 0;
  }
  else {
    value_type cur_loc = added->find(index_type(cur_username.my_hash()));
    account_data x_data(this, cur_loc.loc);
    if(x_data.privilege <= x_privilege) return -1;
    if(x_password.len != 0) *(x_data.password) = x_password;
    if(x_name.len != 0) *(x_data.name) = x_name;
    if(x_mailAddr.len != 0) *(x_data.mailAddr) = x_mailAddr;
    if(x_privilege != -1) x_data.privilege = x_privilege;
    ordered_user_file.open("ordered_user_data.txt", std::ios::in | std::ios::out | std::ios::binary);
    ordered_user_file.seekp(cur_loc.loc);
    x_data.username->write(ordered_user_file);
    x_data.password->write(ordered_user_file);
    x_data.name->write(ordered_user_file);
    x_data.mailAddr->write(ordered_user_file);
    ordered_user_file.write(reinterpret_cast<char*>(&x_data.privilege), sizeof(int));
    ordered_user_file.close();
    x_data.show(); 
    return 0;
  }
  assert(0);
  return 0;
}

void account_system::Clear_logined(){
  logined->clear();
  return ;
}








