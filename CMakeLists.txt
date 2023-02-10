cmake_minimum_required(VERSION 3.19)
project(WillHashTable)

set(CMAKE_CXX_STANDARD 14)

add_executable(WillHashTable const_iterator.h iterator.h hash.h Hash_Table_Chain.h Person.h Person.cpp Test_Person.cpp)