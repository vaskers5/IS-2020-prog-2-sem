# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\79514\Desktop\IS-2020-prog-2-sem\IS-2020-prog-2-sem\homework4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\79514\Desktop\IS-2020-prog-2-sem\IS-2020-prog-2-sem\homework4\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/homework4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/homework4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/homework4.dir/flags.make

CMakeFiles/homework4.dir/main.cpp.obj: CMakeFiles/homework4.dir/flags.make
CMakeFiles/homework4.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\79514\Desktop\IS-2020-prog-2-sem\IS-2020-prog-2-sem\homework4\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/homework4.dir/main.cpp.obj"
	C:\MinGW\gcc\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\homework4.dir\main.cpp.obj -c C:\Users\79514\Desktop\IS-2020-prog-2-sem\IS-2020-prog-2-sem\homework4\main.cpp

CMakeFiles/homework4.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/homework4.dir/main.cpp.i"
	C:\MinGW\gcc\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\79514\Desktop\IS-2020-prog-2-sem\IS-2020-prog-2-sem\homework4\main.cpp > CMakeFiles\homework4.dir\main.cpp.i

CMakeFiles/homework4.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/homework4.dir/main.cpp.s"
	C:\MinGW\gcc\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\79514\Desktop\IS-2020-prog-2-sem\IS-2020-prog-2-sem\homework4\main.cpp -o CMakeFiles\homework4.dir\main.cpp.s

CMakeFiles/homework4.dir/predicate.cpp.obj: CMakeFiles/homework4.dir/flags.make
CMakeFiles/homework4.dir/predicate.cpp.obj: ../predicate.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\79514\Desktop\IS-2020-prog-2-sem\IS-2020-prog-2-sem\homework4\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/homework4.dir/predicate.cpp.obj"
	C:\MinGW\gcc\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\homework4.dir\predicate.cpp.obj -c C:\Users\79514\Desktop\IS-2020-prog-2-sem\IS-2020-prog-2-sem\homework4\predicate.cpp

CMakeFiles/homework4.dir/predicate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/homework4.dir/predicate.cpp.i"
	C:\MinGW\gcc\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\79514\Desktop\IS-2020-prog-2-sem\IS-2020-prog-2-sem\homework4\predicate.cpp > CMakeFiles\homework4.dir\predicate.cpp.i

CMakeFiles/homework4.dir/predicate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/homework4.dir/predicate.cpp.s"
	C:\MinGW\gcc\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\79514\Desktop\IS-2020-prog-2-sem\IS-2020-prog-2-sem\homework4\predicate.cpp -o CMakeFiles\homework4.dir\predicate.cpp.s

# Object files for target homework4
homework4_OBJECTS = \
"CMakeFiles/homework4.dir/main.cpp.obj" \
"CMakeFiles/homework4.dir/predicate.cpp.obj"

# External object files for target homework4
homework4_EXTERNAL_OBJECTS =

homework4.exe: CMakeFiles/homework4.dir/main.cpp.obj
homework4.exe: CMakeFiles/homework4.dir/predicate.cpp.obj
homework4.exe: CMakeFiles/homework4.dir/build.make
homework4.exe: CMakeFiles/homework4.dir/linklibs.rsp
homework4.exe: CMakeFiles/homework4.dir/objects1.rsp
homework4.exe: CMakeFiles/homework4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\79514\Desktop\IS-2020-prog-2-sem\IS-2020-prog-2-sem\homework4\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable homework4.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\homework4.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/homework4.dir/build: homework4.exe

.PHONY : CMakeFiles/homework4.dir/build

CMakeFiles/homework4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\homework4.dir\cmake_clean.cmake
.PHONY : CMakeFiles/homework4.dir/clean

CMakeFiles/homework4.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\79514\Desktop\IS-2020-prog-2-sem\IS-2020-prog-2-sem\homework4 C:\Users\79514\Desktop\IS-2020-prog-2-sem\IS-2020-prog-2-sem\homework4 C:\Users\79514\Desktop\IS-2020-prog-2-sem\IS-2020-prog-2-sem\homework4\cmake-build-debug C:\Users\79514\Desktop\IS-2020-prog-2-sem\IS-2020-prog-2-sem\homework4\cmake-build-debug C:\Users\79514\Desktop\IS-2020-prog-2-sem\IS-2020-prog-2-sem\homework4\cmake-build-debug\CMakeFiles\homework4.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/homework4.dir/depend
