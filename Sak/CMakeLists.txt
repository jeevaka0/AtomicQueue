cmake_minimum_required(VERSION 3.5)

project(Sak CXX)

file(GLOB_RECURSE SOURCE_FILES *.cpp *.hpp)

add_executable(sak ${SOURCE_FILES})
target_link_libraries(sak StdPlus pthread z )
