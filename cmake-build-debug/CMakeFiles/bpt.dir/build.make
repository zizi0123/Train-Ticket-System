# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/86180/Desktop/数据结构/大作业/train_ticket/bpt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/86180/Desktop/数据结构/大作业/train_ticket/bpt/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/bpt.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/bpt.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bpt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bpt.dir/flags.make

CMakeFiles/bpt.dir/bpt.cpp.o: CMakeFiles/bpt.dir/flags.make
CMakeFiles/bpt.dir/bpt.cpp.o: ../bpt.cpp
CMakeFiles/bpt.dir/bpt.cpp.o: CMakeFiles/bpt.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/86180/Desktop/数据结构/大作业/train_ticket/bpt/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bpt.dir/bpt.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bpt.dir/bpt.cpp.o -MF CMakeFiles/bpt.dir/bpt.cpp.o.d -o CMakeFiles/bpt.dir/bpt.cpp.o -c /mnt/c/Users/86180/Desktop/数据结构/大作业/train_ticket/bpt/bpt.cpp

CMakeFiles/bpt.dir/bpt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bpt.dir/bpt.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/86180/Desktop/数据结构/大作业/train_ticket/bpt/bpt.cpp > CMakeFiles/bpt.dir/bpt.cpp.i

CMakeFiles/bpt.dir/bpt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bpt.dir/bpt.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/86180/Desktop/数据结构/大作业/train_ticket/bpt/bpt.cpp -o CMakeFiles/bpt.dir/bpt.cpp.s

CMakeFiles/bpt.dir/main.cpp.o: CMakeFiles/bpt.dir/flags.make
CMakeFiles/bpt.dir/main.cpp.o: ../main.cpp
CMakeFiles/bpt.dir/main.cpp.o: CMakeFiles/bpt.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/86180/Desktop/数据结构/大作业/train_ticket/bpt/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/bpt.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bpt.dir/main.cpp.o -MF CMakeFiles/bpt.dir/main.cpp.o.d -o CMakeFiles/bpt.dir/main.cpp.o -c /mnt/c/Users/86180/Desktop/数据结构/大作业/train_ticket/bpt/main.cpp

CMakeFiles/bpt.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bpt.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/86180/Desktop/数据结构/大作业/train_ticket/bpt/main.cpp > CMakeFiles/bpt.dir/main.cpp.i

CMakeFiles/bpt.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bpt.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/86180/Desktop/数据结构/大作业/train_ticket/bpt/main.cpp -o CMakeFiles/bpt.dir/main.cpp.s

# Object files for target bpt
bpt_OBJECTS = \
"CMakeFiles/bpt.dir/bpt.cpp.o" \
"CMakeFiles/bpt.dir/main.cpp.o"

# External object files for target bpt
bpt_EXTERNAL_OBJECTS =

bpt: CMakeFiles/bpt.dir/bpt.cpp.o
bpt: CMakeFiles/bpt.dir/main.cpp.o
bpt: CMakeFiles/bpt.dir/build.make
bpt: CMakeFiles/bpt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/86180/Desktop/数据结构/大作业/train_ticket/bpt/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bpt"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bpt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bpt.dir/build: bpt
.PHONY : CMakeFiles/bpt.dir/build

CMakeFiles/bpt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bpt.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bpt.dir/clean

CMakeFiles/bpt.dir/depend:
	cd /mnt/c/Users/86180/Desktop/数据结构/大作业/train_ticket/bpt/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/86180/Desktop/数据结构/大作业/train_ticket/bpt /mnt/c/Users/86180/Desktop/数据结构/大作业/train_ticket/bpt /mnt/c/Users/86180/Desktop/数据结构/大作业/train_ticket/bpt/cmake-build-debug /mnt/c/Users/86180/Desktop/数据结构/大作业/train_ticket/bpt/cmake-build-debug /mnt/c/Users/86180/Desktop/数据结构/大作业/train_ticket/bpt/cmake-build-debug/CMakeFiles/bpt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bpt.dir/depend

