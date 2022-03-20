project(StdPlus CXX)

file(GLOB_RECURSE SOURCE_FILES *.cpp *.hpp)

add_library(StdPlus STATIC ${SOURCE_FILES})
