# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/sutymate/JetBrains/CLion/CLion-2020.1.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/sutymate/JetBrains/CLion/CLion-2020.1.1/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sutymate/Progtest/PA2/sem

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sutymate/Progtest/PA2/sem/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/sem.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sem.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sem.dir/flags.make

CMakeFiles/sem.dir/src/main.cpp.o: CMakeFiles/sem.dir/flags.make
CMakeFiles/sem.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sutymate/Progtest/PA2/sem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sem.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sem.dir/src/main.cpp.o -c /home/sutymate/Progtest/PA2/sem/src/main.cpp

CMakeFiles/sem.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sem.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sutymate/Progtest/PA2/sem/src/main.cpp > CMakeFiles/sem.dir/src/main.cpp.i

CMakeFiles/sem.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sem.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sutymate/Progtest/PA2/sem/src/main.cpp -o CMakeFiles/sem.dir/src/main.cpp.s

CMakeFiles/sem.dir/src/CApplication.cpp.o: CMakeFiles/sem.dir/flags.make
CMakeFiles/sem.dir/src/CApplication.cpp.o: ../src/CApplication.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sutymate/Progtest/PA2/sem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sem.dir/src/CApplication.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sem.dir/src/CApplication.cpp.o -c /home/sutymate/Progtest/PA2/sem/src/CApplication.cpp

CMakeFiles/sem.dir/src/CApplication.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sem.dir/src/CApplication.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sutymate/Progtest/PA2/sem/src/CApplication.cpp > CMakeFiles/sem.dir/src/CApplication.cpp.i

CMakeFiles/sem.dir/src/CApplication.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sem.dir/src/CApplication.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sutymate/Progtest/PA2/sem/src/CApplication.cpp -o CMakeFiles/sem.dir/src/CApplication.cpp.s

CMakeFiles/sem.dir/src/CGame.cpp.o: CMakeFiles/sem.dir/flags.make
CMakeFiles/sem.dir/src/CGame.cpp.o: ../src/CGame.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sutymate/Progtest/PA2/sem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/sem.dir/src/CGame.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sem.dir/src/CGame.cpp.o -c /home/sutymate/Progtest/PA2/sem/src/CGame.cpp

CMakeFiles/sem.dir/src/CGame.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sem.dir/src/CGame.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sutymate/Progtest/PA2/sem/src/CGame.cpp > CMakeFiles/sem.dir/src/CGame.cpp.i

CMakeFiles/sem.dir/src/CGame.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sem.dir/src/CGame.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sutymate/Progtest/PA2/sem/src/CGame.cpp -o CMakeFiles/sem.dir/src/CGame.cpp.s

CMakeFiles/sem.dir/src/CMap.cpp.o: CMakeFiles/sem.dir/flags.make
CMakeFiles/sem.dir/src/CMap.cpp.o: ../src/CMap.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sutymate/Progtest/PA2/sem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/sem.dir/src/CMap.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sem.dir/src/CMap.cpp.o -c /home/sutymate/Progtest/PA2/sem/src/CMap.cpp

CMakeFiles/sem.dir/src/CMap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sem.dir/src/CMap.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sutymate/Progtest/PA2/sem/src/CMap.cpp > CMakeFiles/sem.dir/src/CMap.cpp.i

CMakeFiles/sem.dir/src/CMap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sem.dir/src/CMap.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sutymate/Progtest/PA2/sem/src/CMap.cpp -o CMakeFiles/sem.dir/src/CMap.cpp.s

CMakeFiles/sem.dir/src/CTile.cpp.o: CMakeFiles/sem.dir/flags.make
CMakeFiles/sem.dir/src/CTile.cpp.o: ../src/CTile.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sutymate/Progtest/PA2/sem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/sem.dir/src/CTile.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sem.dir/src/CTile.cpp.o -c /home/sutymate/Progtest/PA2/sem/src/CTile.cpp

CMakeFiles/sem.dir/src/CTile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sem.dir/src/CTile.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sutymate/Progtest/PA2/sem/src/CTile.cpp > CMakeFiles/sem.dir/src/CTile.cpp.i

CMakeFiles/sem.dir/src/CTile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sem.dir/src/CTile.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sutymate/Progtest/PA2/sem/src/CTile.cpp -o CMakeFiles/sem.dir/src/CTile.cpp.s

CMakeFiles/sem.dir/src/CTower.cpp.o: CMakeFiles/sem.dir/flags.make
CMakeFiles/sem.dir/src/CTower.cpp.o: ../src/CTower.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sutymate/Progtest/PA2/sem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/sem.dir/src/CTower.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sem.dir/src/CTower.cpp.o -c /home/sutymate/Progtest/PA2/sem/src/CTower.cpp

CMakeFiles/sem.dir/src/CTower.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sem.dir/src/CTower.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sutymate/Progtest/PA2/sem/src/CTower.cpp > CMakeFiles/sem.dir/src/CTower.cpp.i

CMakeFiles/sem.dir/src/CTower.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sem.dir/src/CTower.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sutymate/Progtest/PA2/sem/src/CTower.cpp -o CMakeFiles/sem.dir/src/CTower.cpp.s

CMakeFiles/sem.dir/src/CUnit.cpp.o: CMakeFiles/sem.dir/flags.make
CMakeFiles/sem.dir/src/CUnit.cpp.o: ../src/CUnit.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sutymate/Progtest/PA2/sem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/sem.dir/src/CUnit.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sem.dir/src/CUnit.cpp.o -c /home/sutymate/Progtest/PA2/sem/src/CUnit.cpp

CMakeFiles/sem.dir/src/CUnit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sem.dir/src/CUnit.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sutymate/Progtest/PA2/sem/src/CUnit.cpp > CMakeFiles/sem.dir/src/CUnit.cpp.i

CMakeFiles/sem.dir/src/CUnit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sem.dir/src/CUnit.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sutymate/Progtest/PA2/sem/src/CUnit.cpp -o CMakeFiles/sem.dir/src/CUnit.cpp.s

CMakeFiles/sem.dir/src/CTowerArcher.cpp.o: CMakeFiles/sem.dir/flags.make
CMakeFiles/sem.dir/src/CTowerArcher.cpp.o: ../src/CTowerArcher.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sutymate/Progtest/PA2/sem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/sem.dir/src/CTowerArcher.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sem.dir/src/CTowerArcher.cpp.o -c /home/sutymate/Progtest/PA2/sem/src/CTowerArcher.cpp

CMakeFiles/sem.dir/src/CTowerArcher.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sem.dir/src/CTowerArcher.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sutymate/Progtest/PA2/sem/src/CTowerArcher.cpp > CMakeFiles/sem.dir/src/CTowerArcher.cpp.i

CMakeFiles/sem.dir/src/CTowerArcher.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sem.dir/src/CTowerArcher.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sutymate/Progtest/PA2/sem/src/CTowerArcher.cpp -o CMakeFiles/sem.dir/src/CTowerArcher.cpp.s

CMakeFiles/sem.dir/src/CTowerBombarda.cpp.o: CMakeFiles/sem.dir/flags.make
CMakeFiles/sem.dir/src/CTowerBombarda.cpp.o: ../src/CTowerBombarda.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sutymate/Progtest/PA2/sem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/sem.dir/src/CTowerBombarda.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sem.dir/src/CTowerBombarda.cpp.o -c /home/sutymate/Progtest/PA2/sem/src/CTowerBombarda.cpp

CMakeFiles/sem.dir/src/CTowerBombarda.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sem.dir/src/CTowerBombarda.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sutymate/Progtest/PA2/sem/src/CTowerBombarda.cpp > CMakeFiles/sem.dir/src/CTowerBombarda.cpp.i

CMakeFiles/sem.dir/src/CTowerBombarda.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sem.dir/src/CTowerBombarda.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sutymate/Progtest/PA2/sem/src/CTowerBombarda.cpp -o CMakeFiles/sem.dir/src/CTowerBombarda.cpp.s

CMakeFiles/sem.dir/src/CTowerCaesar.cpp.o: CMakeFiles/sem.dir/flags.make
CMakeFiles/sem.dir/src/CTowerCaesar.cpp.o: ../src/CTowerCaesar.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sutymate/Progtest/PA2/sem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/sem.dir/src/CTowerCaesar.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sem.dir/src/CTowerCaesar.cpp.o -c /home/sutymate/Progtest/PA2/sem/src/CTowerCaesar.cpp

CMakeFiles/sem.dir/src/CTowerCaesar.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sem.dir/src/CTowerCaesar.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sutymate/Progtest/PA2/sem/src/CTowerCaesar.cpp > CMakeFiles/sem.dir/src/CTowerCaesar.cpp.i

CMakeFiles/sem.dir/src/CTowerCaesar.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sem.dir/src/CTowerCaesar.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sutymate/Progtest/PA2/sem/src/CTowerCaesar.cpp -o CMakeFiles/sem.dir/src/CTowerCaesar.cpp.s

# Object files for target sem
sem_OBJECTS = \
"CMakeFiles/sem.dir/src/main.cpp.o" \
"CMakeFiles/sem.dir/src/CApplication.cpp.o" \
"CMakeFiles/sem.dir/src/CGame.cpp.o" \
"CMakeFiles/sem.dir/src/CMap.cpp.o" \
"CMakeFiles/sem.dir/src/CTile.cpp.o" \
"CMakeFiles/sem.dir/src/CTower.cpp.o" \
"CMakeFiles/sem.dir/src/CUnit.cpp.o" \
"CMakeFiles/sem.dir/src/CTowerArcher.cpp.o" \
"CMakeFiles/sem.dir/src/CTowerBombarda.cpp.o" \
"CMakeFiles/sem.dir/src/CTowerCaesar.cpp.o"

# External object files for target sem
sem_EXTERNAL_OBJECTS =

sem: CMakeFiles/sem.dir/src/main.cpp.o
sem: CMakeFiles/sem.dir/src/CApplication.cpp.o
sem: CMakeFiles/sem.dir/src/CGame.cpp.o
sem: CMakeFiles/sem.dir/src/CMap.cpp.o
sem: CMakeFiles/sem.dir/src/CTile.cpp.o
sem: CMakeFiles/sem.dir/src/CTower.cpp.o
sem: CMakeFiles/sem.dir/src/CUnit.cpp.o
sem: CMakeFiles/sem.dir/src/CTowerArcher.cpp.o
sem: CMakeFiles/sem.dir/src/CTowerBombarda.cpp.o
sem: CMakeFiles/sem.dir/src/CTowerCaesar.cpp.o
sem: CMakeFiles/sem.dir/build.make
sem: CMakeFiles/sem.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sutymate/Progtest/PA2/sem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable sem"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sem.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sem.dir/build: sem

.PHONY : CMakeFiles/sem.dir/build

CMakeFiles/sem.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sem.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sem.dir/clean

CMakeFiles/sem.dir/depend:
	cd /home/sutymate/Progtest/PA2/sem/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sutymate/Progtest/PA2/sem /home/sutymate/Progtest/PA2/sem /home/sutymate/Progtest/PA2/sem/cmake-build-debug /home/sutymate/Progtest/PA2/sem/cmake-build-debug /home/sutymate/Progtest/PA2/sem/cmake-build-debug/CMakeFiles/sem.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sem.dir/depend

