# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/user/exercism/cpp/anagram

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/exercism/cpp/anagram/build

# Include any dependencies generated for this target.
include CMakeFiles/anagram.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/anagram.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/anagram.dir/flags.make

CMakeFiles/anagram.dir/anagram_test.cpp.o: CMakeFiles/anagram.dir/flags.make
CMakeFiles/anagram.dir/anagram_test.cpp.o: ../anagram_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/exercism/cpp/anagram/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/anagram.dir/anagram_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/anagram.dir/anagram_test.cpp.o -c /home/user/exercism/cpp/anagram/anagram_test.cpp

CMakeFiles/anagram.dir/anagram_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/anagram.dir/anagram_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/exercism/cpp/anagram/anagram_test.cpp > CMakeFiles/anagram.dir/anagram_test.cpp.i

CMakeFiles/anagram.dir/anagram_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/anagram.dir/anagram_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/exercism/cpp/anagram/anagram_test.cpp -o CMakeFiles/anagram.dir/anagram_test.cpp.s

CMakeFiles/anagram.dir/anagram_test.cpp.o.requires:

.PHONY : CMakeFiles/anagram.dir/anagram_test.cpp.o.requires

CMakeFiles/anagram.dir/anagram_test.cpp.o.provides: CMakeFiles/anagram.dir/anagram_test.cpp.o.requires
	$(MAKE) -f CMakeFiles/anagram.dir/build.make CMakeFiles/anagram.dir/anagram_test.cpp.o.provides.build
.PHONY : CMakeFiles/anagram.dir/anagram_test.cpp.o.provides

CMakeFiles/anagram.dir/anagram_test.cpp.o.provides.build: CMakeFiles/anagram.dir/anagram_test.cpp.o


CMakeFiles/anagram.dir/anagram.cpp.o: CMakeFiles/anagram.dir/flags.make
CMakeFiles/anagram.dir/anagram.cpp.o: ../anagram.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/exercism/cpp/anagram/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/anagram.dir/anagram.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/anagram.dir/anagram.cpp.o -c /home/user/exercism/cpp/anagram/anagram.cpp

CMakeFiles/anagram.dir/anagram.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/anagram.dir/anagram.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/exercism/cpp/anagram/anagram.cpp > CMakeFiles/anagram.dir/anagram.cpp.i

CMakeFiles/anagram.dir/anagram.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/anagram.dir/anagram.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/exercism/cpp/anagram/anagram.cpp -o CMakeFiles/anagram.dir/anagram.cpp.s

CMakeFiles/anagram.dir/anagram.cpp.o.requires:

.PHONY : CMakeFiles/anagram.dir/anagram.cpp.o.requires

CMakeFiles/anagram.dir/anagram.cpp.o.provides: CMakeFiles/anagram.dir/anagram.cpp.o.requires
	$(MAKE) -f CMakeFiles/anagram.dir/build.make CMakeFiles/anagram.dir/anagram.cpp.o.provides.build
.PHONY : CMakeFiles/anagram.dir/anagram.cpp.o.provides

CMakeFiles/anagram.dir/anagram.cpp.o.provides.build: CMakeFiles/anagram.dir/anagram.cpp.o


# Object files for target anagram
anagram_OBJECTS = \
"CMakeFiles/anagram.dir/anagram_test.cpp.o" \
"CMakeFiles/anagram.dir/anagram.cpp.o"

# External object files for target anagram
anagram_EXTERNAL_OBJECTS =

anagram: CMakeFiles/anagram.dir/anagram_test.cpp.o
anagram: CMakeFiles/anagram.dir/anagram.cpp.o
anagram: CMakeFiles/anagram.dir/build.make
anagram: /usr/lib/libboost_unit_test_framework.a
anagram: /usr/lib/libboost_date_time.a
anagram: /usr/lib/libboost_regex.a
anagram: CMakeFiles/anagram.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/exercism/cpp/anagram/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable anagram"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/anagram.dir/link.txt --verbose=$(VERBOSE)
	./anagram

# Rule to build all files generated by this target.
CMakeFiles/anagram.dir/build: anagram

.PHONY : CMakeFiles/anagram.dir/build

CMakeFiles/anagram.dir/requires: CMakeFiles/anagram.dir/anagram_test.cpp.o.requires
CMakeFiles/anagram.dir/requires: CMakeFiles/anagram.dir/anagram.cpp.o.requires

.PHONY : CMakeFiles/anagram.dir/requires

CMakeFiles/anagram.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/anagram.dir/cmake_clean.cmake
.PHONY : CMakeFiles/anagram.dir/clean

CMakeFiles/anagram.dir/depend:
	cd /home/user/exercism/cpp/anagram/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/exercism/cpp/anagram /home/user/exercism/cpp/anagram /home/user/exercism/cpp/anagram/build /home/user/exercism/cpp/anagram/build /home/user/exercism/cpp/anagram/build/CMakeFiles/anagram.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/anagram.dir/depend
