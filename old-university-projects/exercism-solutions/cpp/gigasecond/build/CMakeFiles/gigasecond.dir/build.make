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
CMAKE_SOURCE_DIR = /home/user/exercism/cpp/gigasecond

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/exercism/cpp/gigasecond/build

# Include any dependencies generated for this target.
include CMakeFiles/gigasecond.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gigasecond.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gigasecond.dir/flags.make

CMakeFiles/gigasecond.dir/gigasecond_test.cpp.o: CMakeFiles/gigasecond.dir/flags.make
CMakeFiles/gigasecond.dir/gigasecond_test.cpp.o: ../gigasecond_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/exercism/cpp/gigasecond/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gigasecond.dir/gigasecond_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gigasecond.dir/gigasecond_test.cpp.o -c /home/user/exercism/cpp/gigasecond/gigasecond_test.cpp

CMakeFiles/gigasecond.dir/gigasecond_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gigasecond.dir/gigasecond_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/exercism/cpp/gigasecond/gigasecond_test.cpp > CMakeFiles/gigasecond.dir/gigasecond_test.cpp.i

CMakeFiles/gigasecond.dir/gigasecond_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gigasecond.dir/gigasecond_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/exercism/cpp/gigasecond/gigasecond_test.cpp -o CMakeFiles/gigasecond.dir/gigasecond_test.cpp.s

CMakeFiles/gigasecond.dir/gigasecond_test.cpp.o.requires:

.PHONY : CMakeFiles/gigasecond.dir/gigasecond_test.cpp.o.requires

CMakeFiles/gigasecond.dir/gigasecond_test.cpp.o.provides: CMakeFiles/gigasecond.dir/gigasecond_test.cpp.o.requires
	$(MAKE) -f CMakeFiles/gigasecond.dir/build.make CMakeFiles/gigasecond.dir/gigasecond_test.cpp.o.provides.build
.PHONY : CMakeFiles/gigasecond.dir/gigasecond_test.cpp.o.provides

CMakeFiles/gigasecond.dir/gigasecond_test.cpp.o.provides.build: CMakeFiles/gigasecond.dir/gigasecond_test.cpp.o


CMakeFiles/gigasecond.dir/gigasecond.cpp.o: CMakeFiles/gigasecond.dir/flags.make
CMakeFiles/gigasecond.dir/gigasecond.cpp.o: ../gigasecond.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/exercism/cpp/gigasecond/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/gigasecond.dir/gigasecond.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gigasecond.dir/gigasecond.cpp.o -c /home/user/exercism/cpp/gigasecond/gigasecond.cpp

CMakeFiles/gigasecond.dir/gigasecond.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gigasecond.dir/gigasecond.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/exercism/cpp/gigasecond/gigasecond.cpp > CMakeFiles/gigasecond.dir/gigasecond.cpp.i

CMakeFiles/gigasecond.dir/gigasecond.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gigasecond.dir/gigasecond.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/exercism/cpp/gigasecond/gigasecond.cpp -o CMakeFiles/gigasecond.dir/gigasecond.cpp.s

CMakeFiles/gigasecond.dir/gigasecond.cpp.o.requires:

.PHONY : CMakeFiles/gigasecond.dir/gigasecond.cpp.o.requires

CMakeFiles/gigasecond.dir/gigasecond.cpp.o.provides: CMakeFiles/gigasecond.dir/gigasecond.cpp.o.requires
	$(MAKE) -f CMakeFiles/gigasecond.dir/build.make CMakeFiles/gigasecond.dir/gigasecond.cpp.o.provides.build
.PHONY : CMakeFiles/gigasecond.dir/gigasecond.cpp.o.provides

CMakeFiles/gigasecond.dir/gigasecond.cpp.o.provides.build: CMakeFiles/gigasecond.dir/gigasecond.cpp.o


# Object files for target gigasecond
gigasecond_OBJECTS = \
"CMakeFiles/gigasecond.dir/gigasecond_test.cpp.o" \
"CMakeFiles/gigasecond.dir/gigasecond.cpp.o"

# External object files for target gigasecond
gigasecond_EXTERNAL_OBJECTS =

gigasecond: CMakeFiles/gigasecond.dir/gigasecond_test.cpp.o
gigasecond: CMakeFiles/gigasecond.dir/gigasecond.cpp.o
gigasecond: CMakeFiles/gigasecond.dir/build.make
gigasecond: /usr/lib/libboost_unit_test_framework.a
gigasecond: /usr/lib/libboost_date_time.a
gigasecond: /usr/lib/libboost_regex.a
gigasecond: CMakeFiles/gigasecond.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/exercism/cpp/gigasecond/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable gigasecond"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gigasecond.dir/link.txt --verbose=$(VERBOSE)
	./gigasecond

# Rule to build all files generated by this target.
CMakeFiles/gigasecond.dir/build: gigasecond

.PHONY : CMakeFiles/gigasecond.dir/build

CMakeFiles/gigasecond.dir/requires: CMakeFiles/gigasecond.dir/gigasecond_test.cpp.o.requires
CMakeFiles/gigasecond.dir/requires: CMakeFiles/gigasecond.dir/gigasecond.cpp.o.requires

.PHONY : CMakeFiles/gigasecond.dir/requires

CMakeFiles/gigasecond.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gigasecond.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gigasecond.dir/clean

CMakeFiles/gigasecond.dir/depend:
	cd /home/user/exercism/cpp/gigasecond/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/exercism/cpp/gigasecond /home/user/exercism/cpp/gigasecond /home/user/exercism/cpp/gigasecond/build /home/user/exercism/cpp/gigasecond/build /home/user/exercism/cpp/gigasecond/build/CMakeFiles/gigasecond.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gigasecond.dir/depend

