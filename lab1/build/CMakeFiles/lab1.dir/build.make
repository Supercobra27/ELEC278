# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Owner\Downloads\lab1\lab1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Owner\Downloads\lab1\build

# Include any dependencies generated for this target.
include CMakeFiles/lab1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lab1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lab1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab1.dir/flags.make

CMakeFiles/lab1.dir/rpssim.c.obj: CMakeFiles/lab1.dir/flags.make
CMakeFiles/lab1.dir/rpssim.c.obj: C:/Users/Owner/Downloads/lab1/lab1/rpssim.c
CMakeFiles/lab1.dir/rpssim.c.obj: CMakeFiles/lab1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Owner\Downloads\lab1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/lab1.dir/rpssim.c.obj"
	C:\Users\Owner\Downloads\mingw64-13.1.0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/lab1.dir/rpssim.c.obj -MF CMakeFiles\lab1.dir\rpssim.c.obj.d -o CMakeFiles\lab1.dir\rpssim.c.obj -c C:\Users\Owner\Downloads\lab1\lab1\rpssim.c

CMakeFiles/lab1.dir/rpssim.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/lab1.dir/rpssim.c.i"
	C:\Users\Owner\Downloads\mingw64-13.1.0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Owner\Downloads\lab1\lab1\rpssim.c > CMakeFiles\lab1.dir\rpssim.c.i

CMakeFiles/lab1.dir/rpssim.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/lab1.dir/rpssim.c.s"
	C:\Users\Owner\Downloads\mingw64-13.1.0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Owner\Downloads\lab1\lab1\rpssim.c -o CMakeFiles\lab1.dir\rpssim.c.s

# Object files for target lab1
lab1_OBJECTS = \
"CMakeFiles/lab1.dir/rpssim.c.obj"

# External object files for target lab1
lab1_EXTERNAL_OBJECTS =

lab1.exe: CMakeFiles/lab1.dir/rpssim.c.obj
lab1.exe: CMakeFiles/lab1.dir/build.make
lab1.exe: CMakeFiles/lab1.dir/linkLibs.rsp
lab1.exe: CMakeFiles/lab1.dir/objects1.rsp
lab1.exe: CMakeFiles/lab1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\Owner\Downloads\lab1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable lab1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\lab1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab1.dir/build: lab1.exe
.PHONY : CMakeFiles/lab1.dir/build

CMakeFiles/lab1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\lab1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/lab1.dir/clean

CMakeFiles/lab1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Owner\Downloads\lab1\lab1 C:\Users\Owner\Downloads\lab1\lab1 C:\Users\Owner\Downloads\lab1\build C:\Users\Owner\Downloads\lab1\build C:\Users\Owner\Downloads\lab1\build\CMakeFiles\lab1.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/lab1.dir/depend

