cmake_minimum_required(VERSION 3.4.1)

add_library( native-lib SHARED
             defines.h
             native-lib.h
             native-lib.cpp
             CRenderer.h
             CRenderer.cpp
             CHashMap.h
             CHashMap.cpp
             CApplication.h
             CApplication.cpp)

find_library(log-lib log)

target_link_libraries( native-lib GLESv2 ${log-lib} )