cmake_minimum_required(VERSION 3.0)  # 你所需的 CMake 版本

project(code)  # 你的项目名称

# 添加可执行文件并链接源文件
add_executable(code code.cpp account.cpp)

# 如果有其他的依赖库，你也可以在这里添加链接
# target_link_libraries(your_executable_name ${OTHER_LIBRARIES})