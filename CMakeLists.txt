cmake_minimum_required(VERSION 3.5)

project(MyCpp CXX)

#set(CMAKE_VERBOSE_MAKEFILE ON)

#set(CMAKE_AR gcc-ar)
#set(CMAKE_RANLIB gcc-ranlib)

#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../lib/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../bin/${CMAKE_BUILD_TYPE})

include_directories( /Source/libpcap )

add_compile_options(-Wall -Werror -Wno-multichar -Wconversion -Wsign-conversion)
add_compile_options(-std=c++17 -march=native -mprefetchwt1 -fmessage-length=0)
add_compile_options(-ggdb3)
add_compile_options(-march=native -fno-align-jumps -fno-align-loops)



if( ${CMAKE_BUILD_TYPE} EQUAL "Release" )
    add_compile_options(-O3)
    #add_compile_options(-flto)
    #set_property(GLOBAL PROPERTY INTERPROCEDURAL_OPTIMIZATION True)
endif()

add_subdirectory(StdPlus)
add_subdirectory(Sak)
