# Almost all CMake files should start with this
# You should always specify a range with the newest
# and oldest tested versions of CMake. This will ensure
# you pick up the best policies.
cmake_minimum_required(VERSION 3.1...3.27)

# Set c++ standard for project
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This is your project statement. You should always list languages;
# Listing the version is nice here since it sets lots of useful variables
project(
  ModernCMakeExample
  VERSION 1.0
  LANGUAGES CXX)

include_directories(public)
file(GLOB SOURCES "*.cpp" "public/*.cpp")

# include_directories(${CMAKE_SOURCE_DIR}/openssl)
# set(CMAKE_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/openssl)
find_package(Lua REQUIRED)
find_package(OpenSSL REQUIRED)
# If you set any CMAKE_ variables, that can go here.
# (But usually don't do this, except maybe for C++ standard)

# Find packages go here.

# You should usually split this into folders, but this is a simple example

# This is a "default" library, and will match the *** variable setting.
# Other common choices are STATIC, SHARED, and MODULE
# Including header files here helps IDEs but is not required.
# Output libname matches target name, with the usual extensions on your system
# add_library(libsnappy snappy.h)

# Link each target with other targets or add options, etc.

# Adding something we can run - Output name matches target name
add_executable(exe main.cpp)

# 链接Lua库到你的项目
target_link_libraries(exe ${LUA_LIBRARIES})
target_link_libraries(exe OpenSSL::Crypto)

# 包含Lua头文件目录
target_include_directories(exe PRIVATE ${LUA_INCLUDE_DIR})

# Make sure you link your targets with this command. It can also link libraries and
# even flags, so linking a target that does not exist will not give a configure-time error.
# target_link_libraries(exe ${CMAKE_SOURCE_DIR}/libsnappy.a)
# target_link_libraries(exe ${CMAKE_SOURCE_DIR}/libcrypto.a)
# target_link_libraries(exe ${CMAKE_SOURCE_DIR}/libssl.a)
