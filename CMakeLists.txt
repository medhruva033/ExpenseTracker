cmake_minimum_required(VERSION 3.16)

project(ExpenseTracker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(expense_tracker
    src/main.cpp
    src/Transaction.cpp
    src/ExpenseTracker.cpp
    src/Utils.cpp
)

target_include_directories(expense_tracker PRIVATE include)

if(MSVC)
    target_compile_options(expense_tracker PRIVATE /W4)
else()
    target_compile_options(expense_tracker PRIVATE -Wall -Wextra -Wpedantic)
endif()