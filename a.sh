rm ./account_added_ext_data.txt
rm ./account_added_internal_data.txt
rm ./account_added_leaf_data.txt
rm ./account_logined_ext_data.txt
rm ./account_logined_internal_data.txt
rm ./account_logined_leaf_data.txt
rm ./ordered_user_data.txt
rm ./other_data.txt
rm ./CMakeCache.txt
export CXX=g++
cmake ..
make
./code