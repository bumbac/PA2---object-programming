cmake_minimum_required(VERSION 3.15)
project(sem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS -pthread)
add_executable(sem src/main.cpp src/CMap.hpp src/CTile.hpp src/CApplication.hpp src/CTower.hpp src/CUnit.hpp src/CGame.hpp src/CApplication.cpp src/CGame.cpp src/CMap.cpp src/CTile.cpp src/CTower.cpp src/CUnit.cpp src/CTowerArcher.cpp src/CTowerArcher.hpp src/CTowerBombarda.cpp src/CTowerBombarda.hpp src/CTowerCaesar.cpp src/CTowerCaesar.hpp)