# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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
CMAKE_COMMAND = /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Bootstrap.cmk/cmake

# The command to remove a file.
RM = /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Bootstrap.cmk/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/root2u/Desktop/SDL_chinese/cmake-2.8.3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/root2u/Desktop/SDL_chinese/cmake-2.8.3

# Include any dependencies generated for this target.
include Utilities/cmcompress/CMakeFiles/cmcompress.dir/depend.make

# Include the progress variables for this target.
include Utilities/cmcompress/CMakeFiles/cmcompress.dir/progress.make

# Include the compile flags for this target's objects.
include Utilities/cmcompress/CMakeFiles/cmcompress.dir/flags.make

Utilities/cmcompress/CMakeFiles/cmcompress.dir/cmcompress.o: Utilities/cmcompress/CMakeFiles/cmcompress.dir/flags.make
Utilities/cmcompress/CMakeFiles/cmcompress.dir/cmcompress.o: Utilities/cmcompress/cmcompress.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/CMakeFiles $(CMAKE_PROGRESS_1)
	@echo "Building C object Utilities/cmcompress/CMakeFiles/cmcompress.dir/cmcompress.o"
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Utilities/cmcompress && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/cmcompress.dir/cmcompress.o   -c /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Utilities/cmcompress/cmcompress.c

Utilities/cmcompress/CMakeFiles/cmcompress.dir/cmcompress.i: cmake_force
	@echo "Preprocessing C source to CMakeFiles/cmcompress.dir/cmcompress.i"
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Utilities/cmcompress && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Utilities/cmcompress/cmcompress.c > CMakeFiles/cmcompress.dir/cmcompress.i

Utilities/cmcompress/CMakeFiles/cmcompress.dir/cmcompress.s: cmake_force
	@echo "Compiling C source to assembly CMakeFiles/cmcompress.dir/cmcompress.s"
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Utilities/cmcompress && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Utilities/cmcompress/cmcompress.c -o CMakeFiles/cmcompress.dir/cmcompress.s

Utilities/cmcompress/CMakeFiles/cmcompress.dir/cmcompress.o.requires:
.PHONY : Utilities/cmcompress/CMakeFiles/cmcompress.dir/cmcompress.o.requires

Utilities/cmcompress/CMakeFiles/cmcompress.dir/cmcompress.o.provides: Utilities/cmcompress/CMakeFiles/cmcompress.dir/cmcompress.o.requires
	$(MAKE) -f Utilities/cmcompress/CMakeFiles/cmcompress.dir/build.make Utilities/cmcompress/CMakeFiles/cmcompress.dir/cmcompress.o.provides.build
.PHONY : Utilities/cmcompress/CMakeFiles/cmcompress.dir/cmcompress.o.provides

Utilities/cmcompress/CMakeFiles/cmcompress.dir/cmcompress.o.provides.build: Utilities/cmcompress/CMakeFiles/cmcompress.dir/cmcompress.o
.PHONY : Utilities/cmcompress/CMakeFiles/cmcompress.dir/cmcompress.o.provides.build

# Object files for target cmcompress
cmcompress_OBJECTS = \
"CMakeFiles/cmcompress.dir/cmcompress.o"

# External object files for target cmcompress
cmcompress_EXTERNAL_OBJECTS =

Utilities/cmcompress/libcmcompress.a: Utilities/cmcompress/CMakeFiles/cmcompress.dir/cmcompress.o
Utilities/cmcompress/libcmcompress.a: Utilities/cmcompress/CMakeFiles/cmcompress.dir/build.make
Utilities/cmcompress/libcmcompress.a: Utilities/cmcompress/CMakeFiles/cmcompress.dir/link.txt
	@echo "Linking C static library libcmcompress.a"
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Utilities/cmcompress && $(CMAKE_COMMAND) -P CMakeFiles/cmcompress.dir/cmake_clean_target.cmake
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Utilities/cmcompress && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cmcompress.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Utilities/cmcompress/CMakeFiles/cmcompress.dir/build: Utilities/cmcompress/libcmcompress.a
.PHONY : Utilities/cmcompress/CMakeFiles/cmcompress.dir/build

Utilities/cmcompress/CMakeFiles/cmcompress.dir/requires: Utilities/cmcompress/CMakeFiles/cmcompress.dir/cmcompress.o.requires
.PHONY : Utilities/cmcompress/CMakeFiles/cmcompress.dir/requires

Utilities/cmcompress/CMakeFiles/cmcompress.dir/clean:
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Utilities/cmcompress && $(CMAKE_COMMAND) -P CMakeFiles/cmcompress.dir/cmake_clean.cmake
.PHONY : Utilities/cmcompress/CMakeFiles/cmcompress.dir/clean

Utilities/cmcompress/CMakeFiles/cmcompress.dir/depend:
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/root2u/Desktop/SDL_chinese/cmake-2.8.3 /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Utilities/cmcompress /home/root2u/Desktop/SDL_chinese/cmake-2.8.3 /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Utilities/cmcompress /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Utilities/cmcompress/CMakeFiles/cmcompress.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Utilities/cmcompress/CMakeFiles/cmcompress.dir/depend

