cmake_minimum_required(VERSION 3.4.1)

add_library( native-lib SHARED
             native-lib.h
             native-lib.cpp
             CRenderer.h
             CRenderer.cpp
             CHashMap.h
             CHashMap.cpp
             CApplication.h
             CApplication.cpp)

find_library(log-lib log)

target_link_libraries( native-lib ${log-lib} )