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
include Source/CMakeFiles/cmake.dir/depend.make

# Include the progress variables for this target.
include Source/CMakeFiles/cmake.dir/progress.make

# Include the compile flags for this target's objects.
include Source/CMakeFiles/cmake.dir/flags.make

Source/CMakeFiles/cmake.dir/cmakemain.o: Source/CMakeFiles/cmake.dir/flags.make
Source/CMakeFiles/cmake.dir/cmakemain.o: Source/cmakemain.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/CMakeFiles $(CMAKE_PROGRESS_1)
	@echo "Building CXX object Source/CMakeFiles/cmake.dir/cmakemain.o"
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Source && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cmake.dir/cmakemain.o -c /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Source/cmakemain.cxx

Source/CMakeFiles/cmake.dir/cmakemain.i: cmake_force
	@echo "Preprocessing CXX source to CMakeFiles/cmake.dir/cmakemain.i"
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Source && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Source/cmakemain.cxx > CMakeFiles/cmake.dir/cmakemain.i

Source/CMakeFiles/cmake.dir/cmakemain.s: cmake_force
	@echo "Compiling CXX source to assembly CMakeFiles/cmake.dir/cmakemain.s"
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Source && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Source/cmakemain.cxx -o CMakeFiles/cmake.dir/cmakemain.s

Source/CMakeFiles/cmake.dir/cmakemain.o.requires:
.PHONY : Source/CMakeFiles/cmake.dir/cmakemain.o.requires

Source/CMakeFiles/cmake.dir/cmakemain.o.provides: Source/CMakeFiles/cmake.dir/cmakemain.o.requires
	$(MAKE) -f Source/CMakeFiles/cmake.dir/build.make Source/CMakeFiles/cmake.dir/cmakemain.o.provides.build
.PHONY : Source/CMakeFiles/cmake.dir/cmakemain.o.provides

Source/CMakeFiles/cmake.dir/cmakemain.o.provides.build: Source/CMakeFiles/cmake.dir/cmakemain.o
.PHONY : Source/CMakeFiles/cmake.dir/cmakemain.o.provides.build

# Object files for target cmake
cmake_OBJECTS = \
"CMakeFiles/cmake.dir/cmakemain.o"

# External object files for target cmake
cmake_EXTERNAL_OBJECTS =

bin/cmake: Source/CMakeFiles/cmake.dir/cmakemain.o
bin/cmake: Source/libCMakeLib.a
bin/cmake: Source/kwsys/libcmsys.a
bin/cmake: Utilities/cmexpat/libcmexpat.a
bin/cmake: Utilities/cmlibarchive/libarchive/libcmlibarchive.a
bin/cmake: Utilities/cmbzip2/libcmbzip2.a
bin/cmake: Utilities/cmcompress/libcmcompress.a
bin/cmake: Utilities/cmcurl/libcmcurl.a
bin/cmake: Utilities/cmzlib/libcmzlib.a
bin/cmake: Source/CMakeFiles/cmake.dir/build.make
bin/cmake: Source/CMakeFiles/cmake.dir/link.txt
	@echo "Linking CXX executable ../bin/cmake"
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Source && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cmake.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Source/CMakeFiles/cmake.dir/build: bin/cmake
.PHONY : Source/CMakeFiles/cmake.dir/build

Source/CMakeFiles/cmake.dir/requires: Source/CMakeFiles/cmake.dir/cmakemain.o.requires
.PHONY : Source/CMakeFiles/cmake.dir/requires

Source/CMakeFiles/cmake.dir/clean:
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Source && $(CMAKE_COMMAND) -P CMakeFiles/cmake.dir/cmake_clean.cmake
.PHONY : Source/CMakeFiles/cmake.dir/clean

Source/CMakeFiles/cmake.dir/depend:
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/root2u/Desktop/SDL_chinese/cmake-2.8.3 /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Source /home/root2u/Desktop/SDL_chinese/cmake-2.8.3 /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Source /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Source/CMakeFiles/cmake.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Source/CMakeFiles/cmake.dir/depend

