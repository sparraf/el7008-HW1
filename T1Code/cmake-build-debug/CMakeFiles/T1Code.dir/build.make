# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /home/sparra/Desktop/clion-2018.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/sparra/Desktop/clion-2018.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sparra/Desktop/uchile/2018-2/Imagenes/Tarea1/T1Code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sparra/Desktop/uchile/2018-2/Imagenes/Tarea1/T1Code/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/T1Code.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/T1Code.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/T1Code.dir/flags.make

CMakeFiles/T1Code.dir/main.cpp.o: CMakeFiles/T1Code.dir/flags.make
CMakeFiles/T1Code.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sparra/Desktop/uchile/2018-2/Imagenes/Tarea1/T1Code/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/T1Code.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/T1Code.dir/main.cpp.o -c /home/sparra/Desktop/uchile/2018-2/Imagenes/Tarea1/T1Code/main.cpp

CMakeFiles/T1Code.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/T1Code.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sparra/Desktop/uchile/2018-2/Imagenes/Tarea1/T1Code/main.cpp > CMakeFiles/T1Code.dir/main.cpp.i

CMakeFiles/T1Code.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/T1Code.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sparra/Desktop/uchile/2018-2/Imagenes/Tarea1/T1Code/main.cpp -o CMakeFiles/T1Code.dir/main.cpp.s

CMakeFiles/T1Code.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/T1Code.dir/main.cpp.o.requires

CMakeFiles/T1Code.dir/main.cpp.o.provides: CMakeFiles/T1Code.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/T1Code.dir/build.make CMakeFiles/T1Code.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/T1Code.dir/main.cpp.o.provides

CMakeFiles/T1Code.dir/main.cpp.o.provides.build: CMakeFiles/T1Code.dir/main.cpp.o


# Object files for target T1Code
T1Code_OBJECTS = \
"CMakeFiles/T1Code.dir/main.cpp.o"

# External object files for target T1Code
T1Code_EXTERNAL_OBJECTS =

T1Code: CMakeFiles/T1Code.dir/main.cpp.o
T1Code: CMakeFiles/T1Code.dir/build.make
T1Code: CMakeFiles/T1Code.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sparra/Desktop/uchile/2018-2/Imagenes/Tarea1/T1Code/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable T1Code"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/T1Code.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/T1Code.dir/build: T1Code

.PHONY : CMakeFiles/T1Code.dir/build

CMakeFiles/T1Code.dir/requires: CMakeFiles/T1Code.dir/main.cpp.o.requires

.PHONY : CMakeFiles/T1Code.dir/requires

CMakeFiles/T1Code.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/T1Code.dir/cmake_clean.cmake
.PHONY : CMakeFiles/T1Code.dir/clean

CMakeFiles/T1Code.dir/depend:
	cd /home/sparra/Desktop/uchile/2018-2/Imagenes/Tarea1/T1Code/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sparra/Desktop/uchile/2018-2/Imagenes/Tarea1/T1Code /home/sparra/Desktop/uchile/2018-2/Imagenes/Tarea1/T1Code /home/sparra/Desktop/uchile/2018-2/Imagenes/Tarea1/T1Code/cmake-build-debug /home/sparra/Desktop/uchile/2018-2/Imagenes/Tarea1/T1Code/cmake-build-debug /home/sparra/Desktop/uchile/2018-2/Imagenes/Tarea1/T1Code/cmake-build-debug/CMakeFiles/T1Code.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/T1Code.dir/depend
