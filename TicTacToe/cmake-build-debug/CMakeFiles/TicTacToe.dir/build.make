# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /cygdrive/c/Users/dam/.CLion2019.3/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/dam/.CLion2019.3/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TicTacToe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TicTacToe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TicTacToe.dir/flags.make

CMakeFiles/TicTacToe.dir/main.c.o: CMakeFiles/TicTacToe.dir/flags.make
CMakeFiles/TicTacToe.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TicTacToe.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TicTacToe.dir/main.c.o   -c /cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/main.c

CMakeFiles/TicTacToe.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TicTacToe.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/main.c > CMakeFiles/TicTacToe.dir/main.c.i

CMakeFiles/TicTacToe.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TicTacToe.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/main.c -o CMakeFiles/TicTacToe.dir/main.c.s

CMakeFiles/TicTacToe.dir/Feldausgabe.c.o: CMakeFiles/TicTacToe.dir/flags.make
CMakeFiles/TicTacToe.dir/Feldausgabe.c.o: ../Feldausgabe.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/TicTacToe.dir/Feldausgabe.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TicTacToe.dir/Feldausgabe.c.o   -c /cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/Feldausgabe.c

CMakeFiles/TicTacToe.dir/Feldausgabe.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TicTacToe.dir/Feldausgabe.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/Feldausgabe.c > CMakeFiles/TicTacToe.dir/Feldausgabe.c.i

CMakeFiles/TicTacToe.dir/Feldausgabe.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TicTacToe.dir/Feldausgabe.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/Feldausgabe.c -o CMakeFiles/TicTacToe.dir/Feldausgabe.c.s

CMakeFiles/TicTacToe.dir/Logik.c.o: CMakeFiles/TicTacToe.dir/flags.make
CMakeFiles/TicTacToe.dir/Logik.c.o: ../Logik.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/TicTacToe.dir/Logik.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TicTacToe.dir/Logik.c.o   -c /cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/Logik.c

CMakeFiles/TicTacToe.dir/Logik.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TicTacToe.dir/Logik.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/Logik.c > CMakeFiles/TicTacToe.dir/Logik.c.i

CMakeFiles/TicTacToe.dir/Logik.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TicTacToe.dir/Logik.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/Logik.c -o CMakeFiles/TicTacToe.dir/Logik.c.s

CMakeFiles/TicTacToe.dir/ComputerLogic.c.o: CMakeFiles/TicTacToe.dir/flags.make
CMakeFiles/TicTacToe.dir/ComputerLogic.c.o: ../ComputerLogic.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/TicTacToe.dir/ComputerLogic.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TicTacToe.dir/ComputerLogic.c.o   -c /cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/ComputerLogic.c

CMakeFiles/TicTacToe.dir/ComputerLogic.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TicTacToe.dir/ComputerLogic.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/ComputerLogic.c > CMakeFiles/TicTacToe.dir/ComputerLogic.c.i

CMakeFiles/TicTacToe.dir/ComputerLogic.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TicTacToe.dir/ComputerLogic.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/ComputerLogic.c -o CMakeFiles/TicTacToe.dir/ComputerLogic.c.s

# Object files for target TicTacToe
TicTacToe_OBJECTS = \
"CMakeFiles/TicTacToe.dir/main.c.o" \
"CMakeFiles/TicTacToe.dir/Feldausgabe.c.o" \
"CMakeFiles/TicTacToe.dir/Logik.c.o" \
"CMakeFiles/TicTacToe.dir/ComputerLogic.c.o"

# External object files for target TicTacToe
TicTacToe_EXTERNAL_OBJECTS =

TicTacToe.exe: CMakeFiles/TicTacToe.dir/main.c.o
TicTacToe.exe: CMakeFiles/TicTacToe.dir/Feldausgabe.c.o
TicTacToe.exe: CMakeFiles/TicTacToe.dir/Logik.c.o
TicTacToe.exe: CMakeFiles/TicTacToe.dir/ComputerLogic.c.o
TicTacToe.exe: CMakeFiles/TicTacToe.dir/build.make
TicTacToe.exe: CMakeFiles/TicTacToe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable TicTacToe.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TicTacToe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TicTacToe.dir/build: TicTacToe.exe

.PHONY : CMakeFiles/TicTacToe.dir/build

CMakeFiles/TicTacToe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TicTacToe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TicTacToe.dir/clean

CMakeFiles/TicTacToe.dir/depend:
	cd /cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe /cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe /cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/cmake-build-debug /cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/cmake-build-debug /cygdrive/c/Users/dam/Documents/GitHub/TicTacToe_Network/TicTacToe/cmake-build-debug/CMakeFiles/TicTacToe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TicTacToe.dir/depend
