cmake_minimum_required(VERSION 3.15)
project(sem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS -pthread)
add_executable(sem src/main.cpp src/CMap.h src/CTile.h src/CApplication.h src/CTower.h src/CUnit.h src/CGame.h src/CApplication.cpp src/CGame.cpp src/CMap.cpp src/CTile.cpp src/CTower.cpp src/CUnit.cpp src/CTowerArcher.cpp src/CTowerArcher.h src/CTowerBombarda.cpp src/CTowerBombarda.h src/CTowerCaesar.cpp src/CTowerCaesar.h)