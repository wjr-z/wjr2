cmake_minimum_required(VERSION 3.10)

project(wjr LANGUAGES CXX)

set(WJR_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../include)
set(WJR_LIB_DIR ${WJR_INCLUDE_DIR}/wjr)
set(WJR_SIMD_DIR ${WJR_LIB_DIR}/simd)
set(WJR_ASM_DIR ${WJR_LIB_DIR}/asm)
set(WJR_ALGO_DIR ${WJR_LIB_DIR}/algo)

  if (MSVC)
    set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} /O2 /std:c++17 /arch:mavx2")
  else()
    set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O2 -std=c++17 -mavx2 -DNWJR_CPUINFO")
  endif() 

file(GLOB_RECURSE WJR_SRCS ${WJR_LIB_DIR}/*.cpp)

add_executable(wjr 
                ${PROJECT_SOURCE_DIR}/src/unit_vector.cpp 
                ${PROJECT_SOURCE_DIR}/src/unit_algo.cpp
				${WJR_SRCS}
)

target_include_directories(wjr PUBLIC 
                           ${WJR_INCLUDE_DIR}
                           ${WJR_SIMD_DIR}
                           ${WJR_ASM_DIR}
                           ${WJR_ALGO_DIR}
                           ) 

target_link_libraries(
  wjr
  main.cpp
)