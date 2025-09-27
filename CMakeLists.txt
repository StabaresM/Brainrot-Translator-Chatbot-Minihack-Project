cmake_minimum_required(VERSION 3.13)
project(myproject LANGUAGES CXX)

# Make sure you use at least C++17 since liboai requires it
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add liboai as a subdirectory
# Adjust the path if your layout is different
add_subdirectory(liboai/liboai)

# Your executable
add_executable(myapp main.cpp)

# Link against liboai (the inner project creates a target called "oai")
target_link_libraries(myapp PRIVATE oai)
