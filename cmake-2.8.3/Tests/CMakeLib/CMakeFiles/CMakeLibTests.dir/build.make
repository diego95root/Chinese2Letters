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
include Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/depend.make

# Include the progress variables for this target.
include Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/progress.make

# Include the compile flags for this target's objects.
include Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/flags.make

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/CMakeLibTests.o: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/flags.make
Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/CMakeLibTests.o: Tests/CMakeLib/CMakeLibTests.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/CMakeFiles $(CMAKE_PROGRESS_1)
	@echo "Building CXX object Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/CMakeLibTests.o"
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/CMakeLibTests.dir/CMakeLibTests.o -c /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib/CMakeLibTests.cxx

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/CMakeLibTests.i: cmake_force
	@echo "Preprocessing CXX source to CMakeFiles/CMakeLibTests.dir/CMakeLibTests.i"
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib/CMakeLibTests.cxx > CMakeFiles/CMakeLibTests.dir/CMakeLibTests.i

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/CMakeLibTests.s: cmake_force
	@echo "Compiling CXX source to assembly CMakeFiles/CMakeLibTests.dir/CMakeLibTests.s"
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib/CMakeLibTests.cxx -o CMakeFiles/CMakeLibTests.dir/CMakeLibTests.s

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/CMakeLibTests.o.requires:
.PHONY : Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/CMakeLibTests.o.requires

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/CMakeLibTests.o.provides: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/CMakeLibTests.o.requires
	$(MAKE) -f Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/build.make Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/CMakeLibTests.o.provides.build
.PHONY : Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/CMakeLibTests.o.provides

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/CMakeLibTests.o.provides.build: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/CMakeLibTests.o
.PHONY : Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/CMakeLibTests.o.provides.build

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testUTF8.o: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/flags.make
Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testUTF8.o: Tests/CMakeLib/testUTF8.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/CMakeFiles $(CMAKE_PROGRESS_2)
	@echo "Building CXX object Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testUTF8.o"
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/CMakeLibTests.dir/testUTF8.o -c /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib/testUTF8.cxx

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testUTF8.i: cmake_force
	@echo "Preprocessing CXX source to CMakeFiles/CMakeLibTests.dir/testUTF8.i"
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib/testUTF8.cxx > CMakeFiles/CMakeLibTests.dir/testUTF8.i

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testUTF8.s: cmake_force
	@echo "Compiling CXX source to assembly CMakeFiles/CMakeLibTests.dir/testUTF8.s"
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib/testUTF8.cxx -o CMakeFiles/CMakeLibTests.dir/testUTF8.s

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testUTF8.o.requires:
.PHONY : Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testUTF8.o.requires

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testUTF8.o.provides: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testUTF8.o.requires
	$(MAKE) -f Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/build.make Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testUTF8.o.provides.build
.PHONY : Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testUTF8.o.provides

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testUTF8.o.provides.build: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testUTF8.o
.PHONY : Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testUTF8.o.provides.build

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLParser.o: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/flags.make
Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLParser.o: Tests/CMakeLib/testXMLParser.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/CMakeFiles $(CMAKE_PROGRESS_3)
	@echo "Building CXX object Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLParser.o"
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/CMakeLibTests.dir/testXMLParser.o -c /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib/testXMLParser.cxx

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLParser.i: cmake_force
	@echo "Preprocessing CXX source to CMakeFiles/CMakeLibTests.dir/testXMLParser.i"
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib/testXMLParser.cxx > CMakeFiles/CMakeLibTests.dir/testXMLParser.i

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLParser.s: cmake_force
	@echo "Compiling CXX source to assembly CMakeFiles/CMakeLibTests.dir/testXMLParser.s"
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib/testXMLParser.cxx -o CMakeFiles/CMakeLibTests.dir/testXMLParser.s

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLParser.o.requires:
.PHONY : Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLParser.o.requires

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLParser.o.provides: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLParser.o.requires
	$(MAKE) -f Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/build.make Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLParser.o.provides.build
.PHONY : Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLParser.o.provides

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLParser.o.provides.build: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLParser.o
.PHONY : Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLParser.o.provides.build

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLSafe.o: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/flags.make
Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLSafe.o: Tests/CMakeLib/testXMLSafe.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/CMakeFiles $(CMAKE_PROGRESS_4)
	@echo "Building CXX object Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLSafe.o"
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/CMakeLibTests.dir/testXMLSafe.o -c /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib/testXMLSafe.cxx

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLSafe.i: cmake_force
	@echo "Preprocessing CXX source to CMakeFiles/CMakeLibTests.dir/testXMLSafe.i"
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib/testXMLSafe.cxx > CMakeFiles/CMakeLibTests.dir/testXMLSafe.i

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLSafe.s: cmake_force
	@echo "Compiling CXX source to assembly CMakeFiles/CMakeLibTests.dir/testXMLSafe.s"
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib/testXMLSafe.cxx -o CMakeFiles/CMakeLibTests.dir/testXMLSafe.s

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLSafe.o.requires:
.PHONY : Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLSafe.o.requires

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLSafe.o.provides: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLSafe.o.requires
	$(MAKE) -f Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/build.make Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLSafe.o.provides.build
.PHONY : Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLSafe.o.provides

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLSafe.o.provides.build: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLSafe.o
.PHONY : Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLSafe.o.provides.build

# Object files for target CMakeLibTests
CMakeLibTests_OBJECTS = \
"CMakeFiles/CMakeLibTests.dir/CMakeLibTests.o" \
"CMakeFiles/CMakeLibTests.dir/testUTF8.o" \
"CMakeFiles/CMakeLibTests.dir/testXMLParser.o" \
"CMakeFiles/CMakeLibTests.dir/testXMLSafe.o"

# External object files for target CMakeLibTests
CMakeLibTests_EXTERNAL_OBJECTS =

Tests/CMakeLib/CMakeLibTests: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/CMakeLibTests.o
Tests/CMakeLib/CMakeLibTests: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testUTF8.o
Tests/CMakeLib/CMakeLibTests: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLParser.o
Tests/CMakeLib/CMakeLibTests: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLSafe.o
Tests/CMakeLib/CMakeLibTests: Source/libCMakeLib.a
Tests/CMakeLib/CMakeLibTests: Source/kwsys/libcmsys.a
Tests/CMakeLib/CMakeLibTests: Utilities/cmexpat/libcmexpat.a
Tests/CMakeLib/CMakeLibTests: Utilities/cmlibarchive/libarchive/libcmlibarchive.a
Tests/CMakeLib/CMakeLibTests: Utilities/cmbzip2/libcmbzip2.a
Tests/CMakeLib/CMakeLibTests: Utilities/cmcompress/libcmcompress.a
Tests/CMakeLib/CMakeLibTests: Utilities/cmcurl/libcmcurl.a
Tests/CMakeLib/CMakeLibTests: Utilities/cmzlib/libcmzlib.a
Tests/CMakeLib/CMakeLibTests: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/build.make
Tests/CMakeLib/CMakeLibTests: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/link.txt
	@echo "Linking CXX executable CMakeLibTests"
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CMakeLibTests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/build: Tests/CMakeLib/CMakeLibTests
.PHONY : Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/build

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/requires: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/CMakeLibTests.o.requires
Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/requires: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testUTF8.o.requires
Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/requires: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLParser.o.requires
Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/requires: Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/testXMLSafe.o.requires
.PHONY : Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/requires

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/clean:
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib && $(CMAKE_COMMAND) -P CMakeFiles/CMakeLibTests.dir/cmake_clean.cmake
.PHONY : Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/clean

Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/depend:
	cd /home/root2u/Desktop/SDL_chinese/cmake-2.8.3 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/root2u/Desktop/SDL_chinese/cmake-2.8.3 /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib /home/root2u/Desktop/SDL_chinese/cmake-2.8.3 /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib /home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Tests/CMakeLib/CMakeFiles/CMakeLibTests.dir/depend

