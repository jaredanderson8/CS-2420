# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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

# Suppress display of executed commands.
$$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/jaredbrian/Desktop/school stuff/5th Semester/CS 2420/Assingment 4"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/jaredbrian/Desktop/school stuff/5th Semester/CS 2420/Assingment 4/build"

# Include any dependencies generated for this target.
include CMakeFiles/cs2420.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cs2420.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cs2420.dir/flags.make

CMakeFiles/cs2420.dir/main.cpp.o: CMakeFiles/cs2420.dir/flags.make
CMakeFiles/cs2420.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/jaredbrian/Desktop/school stuff/5th Semester/CS 2420/Assingment 4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cs2420.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cs2420.dir/main.cpp.o -c "/home/jaredbrian/Desktop/school stuff/5th Semester/CS 2420/Assingment 4/main.cpp"

CMakeFiles/cs2420.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cs2420.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/jaredbrian/Desktop/school stuff/5th Semester/CS 2420/Assingment 4/main.cpp" > CMakeFiles/cs2420.dir/main.cpp.i

CMakeFiles/cs2420.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cs2420.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/jaredbrian/Desktop/school stuff/5th Semester/CS 2420/Assingment 4/main.cpp" -o CMakeFiles/cs2420.dir/main.cpp.s

# Object files for target cs2420
cs2420_OBJECTS = \
"CMakeFiles/cs2420.dir/main.cpp.o"

# External object files for target cs2420
cs2420_EXTERNAL_OBJECTS =

cs2420: CMakeFiles/cs2420.dir/main.cpp.o
cs2420: CMakeFiles/cs2420.dir/build.make
cs2420: CMakeFiles/cs2420.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/jaredbrian/Desktop/school stuff/5th Semester/CS 2420/Assingment 4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cs2420"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cs2420.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cs2420.dir/build: cs2420

.PHONY : CMakeFiles/cs2420.dir/build

CMakeFiles/cs2420.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cs2420.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cs2420.dir/clean

CMakeFiles/cs2420.dir/depend:
	cd "/home/jaredbrian/Desktop/school stuff/5th Semester/CS 2420/Assingment 4/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/jaredbrian/Desktop/school stuff/5th Semester/CS 2420/Assingment 4" "/home/jaredbrian/Desktop/school stuff/5th Semester/CS 2420/Assingment 4" "/home/jaredbrian/Desktop/school stuff/5th Semester/CS 2420/Assingment 4/build" "/home/jaredbrian/Desktop/school stuff/5th Semester/CS 2420/Assingment 4/build" "/home/jaredbrian/Desktop/school stuff/5th Semester/CS 2420/Assingment 4/build/CMakeFiles/cs2420.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/cs2420.dir/depend

