cmake_minimum_required(VERSION 3.23)
project(Project1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project1 main.cpp BookList.cpp BookList.h MemberList.cpp MemberList.h RatingsList.cpp RatingsList.h)
