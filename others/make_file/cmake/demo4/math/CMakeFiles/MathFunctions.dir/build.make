# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mysoftware_backup/others/make_file/cmake/demo4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mysoftware_backup/others/make_file/cmake/demo4

# Include any dependencies generated for this target.
include math/CMakeFiles/MathFunctions.dir/depend.make

# Include the progress variables for this target.
include math/CMakeFiles/MathFunctions.dir/progress.make

# Include the compile flags for this target's objects.
include math/CMakeFiles/MathFunctions.dir/flags.make

math/CMakeFiles/MathFunctions.dir/MathFunctions.c.o: math/CMakeFiles/MathFunctions.dir/flags.make
math/CMakeFiles/MathFunctions.dir/MathFunctions.c.o: math/MathFunctions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mysoftware_backup/others/make_file/cmake/demo4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object math/CMakeFiles/MathFunctions.dir/MathFunctions.c.o"
	cd /mysoftware_backup/others/make_file/cmake/demo4/math && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MathFunctions.dir/MathFunctions.c.o   -c /mysoftware_backup/others/make_file/cmake/demo4/math/MathFunctions.c

math/CMakeFiles/MathFunctions.dir/MathFunctions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MathFunctions.dir/MathFunctions.c.i"
	cd /mysoftware_backup/others/make_file/cmake/demo4/math && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mysoftware_backup/others/make_file/cmake/demo4/math/MathFunctions.c > CMakeFiles/MathFunctions.dir/MathFunctions.c.i

math/CMakeFiles/MathFunctions.dir/MathFunctions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MathFunctions.dir/MathFunctions.c.s"
	cd /mysoftware_backup/others/make_file/cmake/demo4/math && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mysoftware_backup/others/make_file/cmake/demo4/math/MathFunctions.c -o CMakeFiles/MathFunctions.dir/MathFunctions.c.s

math/CMakeFiles/MathFunctions.dir/MathFunctions.c.o.requires:

.PHONY : math/CMakeFiles/MathFunctions.dir/MathFunctions.c.o.requires

math/CMakeFiles/MathFunctions.dir/MathFunctions.c.o.provides: math/CMakeFiles/MathFunctions.dir/MathFunctions.c.o.requires
	$(MAKE) -f math/CMakeFiles/MathFunctions.dir/build.make math/CMakeFiles/MathFunctions.dir/MathFunctions.c.o.provides.build
.PHONY : math/CMakeFiles/MathFunctions.dir/MathFunctions.c.o.provides

math/CMakeFiles/MathFunctions.dir/MathFunctions.c.o.provides.build: math/CMakeFiles/MathFunctions.dir/MathFunctions.c.o


# Object files for target MathFunctions
MathFunctions_OBJECTS = \
"CMakeFiles/MathFunctions.dir/MathFunctions.c.o"

# External object files for target MathFunctions
MathFunctions_EXTERNAL_OBJECTS =

math/libMathFunctions.a: math/CMakeFiles/MathFunctions.dir/MathFunctions.c.o
math/libMathFunctions.a: math/CMakeFiles/MathFunctions.dir/build.make
math/libMathFunctions.a: math/CMakeFiles/MathFunctions.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mysoftware_backup/others/make_file/cmake/demo4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libMathFunctions.a"
	cd /mysoftware_backup/others/make_file/cmake/demo4/math && $(CMAKE_COMMAND) -P CMakeFiles/MathFunctions.dir/cmake_clean_target.cmake
	cd /mysoftware_backup/others/make_file/cmake/demo4/math && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MathFunctions.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
math/CMakeFiles/MathFunctions.dir/build: math/libMathFunctions.a

.PHONY : math/CMakeFiles/MathFunctions.dir/build

math/CMakeFiles/MathFunctions.dir/requires: math/CMakeFiles/MathFunctions.dir/MathFunctions.c.o.requires

.PHONY : math/CMakeFiles/MathFunctions.dir/requires

math/CMakeFiles/MathFunctions.dir/clean:
	cd /mysoftware_backup/others/make_file/cmake/demo4/math && $(CMAKE_COMMAND) -P CMakeFiles/MathFunctions.dir/cmake_clean.cmake
.PHONY : math/CMakeFiles/MathFunctions.dir/clean

math/CMakeFiles/MathFunctions.dir/depend:
	cd /mysoftware_backup/others/make_file/cmake/demo4 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mysoftware_backup/others/make_file/cmake/demo4 /mysoftware_backup/others/make_file/cmake/demo4/math /mysoftware_backup/others/make_file/cmake/demo4 /mysoftware_backup/others/make_file/cmake/demo4/math /mysoftware_backup/others/make_file/cmake/demo4/math/CMakeFiles/MathFunctions.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : math/CMakeFiles/MathFunctions.dir/depend

