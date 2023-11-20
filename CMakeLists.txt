cmake_minimum_required(VERSION 3.14)
PROJECT(calendarGen)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -pedantic -Werror)

add_executable(${PROJECT_NAME} src/main.cpp src/calendar.cpp src/calendar.h)