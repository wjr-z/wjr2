cmake_minimum_required(VERSION 3.10)

project(wjr LANGUAGES CXX)

set(WJR_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(WJR_LIB_DIR ${WJR_INCLUDE_DIR}/wjr)

  if (MSVC)
    set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} /O2 /std:c++17 /arch:AVX2")
  else()
    set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O2 -std=c++17 -mavx2 -DNWJR_CPUINFO")
  endif() 

set(CMAKE_CXX_STANDARD 14)

add_executable(
  wjr 
  main.cpp
)

target_include_directories(wjr PUBLIC 
                           ${WJR_INCLUDE_DIR}
                           ) 

target_link_libraries(
  wjr
)