# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/omersiton/CLionProjects/ex2-omer_siton

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/omersiton/CLionProjects/ex2-omer_siton/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ex2_omer_siton.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/ex2_omer_siton.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ex2_omer_siton.dir/flags.make

CMakeFiles/ex2_omer_siton.dir/ex2.c.o: CMakeFiles/ex2_omer_siton.dir/flags.make
CMakeFiles/ex2_omer_siton.dir/ex2.c.o: ../ex2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/omersiton/CLionProjects/ex2-omer_siton/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ex2_omer_siton.dir/ex2.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ex2_omer_siton.dir/ex2.c.o -c /Users/omersiton/CLionProjects/ex2-omer_siton/ex2.c

CMakeFiles/ex2_omer_siton.dir/ex2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex2_omer_siton.dir/ex2.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/omersiton/CLionProjects/ex2-omer_siton/ex2.c > CMakeFiles/ex2_omer_siton.dir/ex2.c.i

CMakeFiles/ex2_omer_siton.dir/ex2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex2_omer_siton.dir/ex2.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/omersiton/CLionProjects/ex2-omer_siton/ex2.c -o CMakeFiles/ex2_omer_siton.dir/ex2.c.s

CMakeFiles/ex2_omer_siton.dir/test_ex2.c.o: CMakeFiles/ex2_omer_siton.dir/flags.make
CMakeFiles/ex2_omer_siton.dir/test_ex2.c.o: ../test_ex2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/omersiton/CLionProjects/ex2-omer_siton/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ex2_omer_siton.dir/test_ex2.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ex2_omer_siton.dir/test_ex2.c.o -c /Users/omersiton/CLionProjects/ex2-omer_siton/test_ex2.c

CMakeFiles/ex2_omer_siton.dir/test_ex2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex2_omer_siton.dir/test_ex2.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/omersiton/CLionProjects/ex2-omer_siton/test_ex2.c > CMakeFiles/ex2_omer_siton.dir/test_ex2.c.i

CMakeFiles/ex2_omer_siton.dir/test_ex2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex2_omer_siton.dir/test_ex2.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/omersiton/CLionProjects/ex2-omer_siton/test_ex2.c -o CMakeFiles/ex2_omer_siton.dir/test_ex2.c.s

# Object files for target ex2_omer_siton
ex2_omer_siton_OBJECTS = \
"CMakeFiles/ex2_omer_siton.dir/ex2.c.o" \
"CMakeFiles/ex2_omer_siton.dir/test_ex2.c.o"

# External object files for target ex2_omer_siton
ex2_omer_siton_EXTERNAL_OBJECTS =

ex2_omer_siton: CMakeFiles/ex2_omer_siton.dir/ex2.c.o
ex2_omer_siton: CMakeFiles/ex2_omer_siton.dir/test_ex2.c.o
ex2_omer_siton: CMakeFiles/ex2_omer_siton.dir/build.make
ex2_omer_siton: CMakeFiles/ex2_omer_siton.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/omersiton/CLionProjects/ex2-omer_siton/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable ex2_omer_siton"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex2_omer_siton.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ex2_omer_siton.dir/build: ex2_omer_siton
.PHONY : CMakeFiles/ex2_omer_siton.dir/build

CMakeFiles/ex2_omer_siton.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ex2_omer_siton.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ex2_omer_siton.dir/clean

CMakeFiles/ex2_omer_siton.dir/depend:
	cd /Users/omersiton/CLionProjects/ex2-omer_siton/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/omersiton/CLionProjects/ex2-omer_siton /Users/omersiton/CLionProjects/ex2-omer_siton /Users/omersiton/CLionProjects/ex2-omer_siton/cmake-build-debug /Users/omersiton/CLionProjects/ex2-omer_siton/cmake-build-debug /Users/omersiton/CLionProjects/ex2-omer_siton/cmake-build-debug/CMakeFiles/ex2_omer_siton.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ex2_omer_siton.dir/depend

