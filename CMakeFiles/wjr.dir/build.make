# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:/repos/wjr2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:/repos/wjr2

# Include any dependencies generated for this target.
include CMakeFiles/wjr.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/wjr.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/wjr.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wjr.dir/flags.make

CMakeFiles/wjr.dir/main.cpp.obj: CMakeFiles/wjr.dir/flags.make
CMakeFiles/wjr.dir/main.cpp.obj: CMakeFiles/wjr.dir/includes_CXX.rsp
CMakeFiles/wjr.dir/main.cpp.obj: main.cpp
CMakeFiles/wjr.dir/main.cpp.obj: CMakeFiles/wjr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/repos/wjr2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wjr.dir/main.cpp.obj"
	D:/mingw64/mingw64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/wjr.dir/main.cpp.obj -MF CMakeFiles/wjr.dir/main.cpp.obj.d -o CMakeFiles/wjr.dir/main.cpp.obj -c D:/repos/wjr2/main.cpp

CMakeFiles/wjr.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/wjr.dir/main.cpp.i"
	D:/mingw64/mingw64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/repos/wjr2/main.cpp > CMakeFiles/wjr.dir/main.cpp.i

CMakeFiles/wjr.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/wjr.dir/main.cpp.s"
	D:/mingw64/mingw64/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/repos/wjr2/main.cpp -o CMakeFiles/wjr.dir/main.cpp.s

# Object files for target wjr
wjr_OBJECTS = \
"CMakeFiles/wjr.dir/main.cpp.obj"

# External object files for target wjr
wjr_EXTERNAL_OBJECTS =

wjr.exe: CMakeFiles/wjr.dir/main.cpp.obj
wjr.exe: CMakeFiles/wjr.dir/build.make
wjr.exe: CMakeFiles/wjr.dir/linkLibs.rsp
wjr.exe: CMakeFiles/wjr.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:/repos/wjr2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable wjr.exe"
	"C:/Program Files/CMake/bin/cmake.exe" -E rm -f CMakeFiles/wjr.dir/objects.a
	D:/mingw64/mingw64/bin/ar.exe qc CMakeFiles/wjr.dir/objects.a @CMakeFiles/wjr.dir/objects1.rsp
	D:/mingw64/mingw64/bin/c++.exe  -O2 -std=c++17 -mavx2 -DNWJR_CPUINFO -O3 -DNDEBUG -Wl,--whole-archive CMakeFiles/wjr.dir/objects.a -Wl,--no-whole-archive -o wjr.exe -Wl,--out-implib,libwjr.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/wjr.dir/linkLibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/wjr.dir/build: wjr.exe
.PHONY : CMakeFiles/wjr.dir/build

CMakeFiles/wjr.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/wjr.dir/cmake_clean.cmake
.PHONY : CMakeFiles/wjr.dir/clean

CMakeFiles/wjr.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/repos/wjr2 D:/repos/wjr2 D:/repos/wjr2 D:/repos/wjr2 D:/repos/wjr2/CMakeFiles/wjr.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/wjr.dir/depend

