cmake_minimum_required (VERSION 2.6)
project (Fluxer)

add_library(mesher SHARED mesher.cpp)

add_library(solver solver.cpp)

add_executable(fluxer fluxer.cpp)
target_link_libraries(fluxer solver mesher)