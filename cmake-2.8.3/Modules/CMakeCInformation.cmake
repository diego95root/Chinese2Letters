
#=============================================================================
# Copyright 2004-2009 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

# This file sets the basic flags for the C language in CMake.
# It also loads the available platform file for the system-compiler
# if it exists.
# It also loads a system - compiler - processor (or target hardware)
# specific file, which is mainly useful for crosscompiling and embedded systems.

# some compilers use different extensions (e.g. sdcc uses .rel)
# so set the extension here first so it can be overridden by the compiler specific file
IF(UNIX)
  SET(CMAKE_C_OUTPUT_EXTENSION .o)
ELSE(UNIX)
  SET(CMAKE_C_OUTPUT_EXTENSION .obj)
ENDIF(UNIX)

SET(_INCLUDED_FILE 0)

# Load compiler-specific information.
IF(CMAKE_C_COMPILER_ID)
  INCLUDE(Compiler/${CMAKE_C_COMPILER_ID}-C OPTIONAL)
ENDIF(CMAKE_C_COMPILER_ID)

SET(CMAKE_BASE_NAME)
GET_FILENAME_COMPONENT(CMAKE_BASE_NAME ${CMAKE_C_COMPILER} NAME_WE)
IF(CMAKE_COMPILER_IS_GNUCC)
  SET(CMAKE_BASE_NAME gcc)
ENDIF(CMAKE_COMPILER_IS_GNUCC)


# load a hardware specific file, mostly useful for embedded compilers
IF(CMAKE_SYSTEM_PROCESSOR)
  IF(CMAKE_C_COMPILER_ID)
    INCLUDE(Platform/${CMAKE_SYSTEM_NAME}-${CMAKE_C_COMPILER_ID}-C-${CMAKE_SYSTEM_PROCESSOR} OPTIONAL RESULT_VARIABLE _INCLUDED_FILE)
  ENDIF(CMAKE_C_COMPILER_ID)
  IF (NOT _INCLUDED_FILE)
    INCLUDE(Platform/${CMAKE_SYSTEM_NAME}-${CMAKE_BASE_NAME}-${CMAKE_SYSTEM_PROCESSOR} OPTIONAL)
  ENDIF (NOT _INCLUDED_FILE)
ENDIF(CMAKE_SYSTEM_PROCESSOR)


# load the system- and compiler specific files
IF(CMAKE_C_COMPILER_ID)
  INCLUDE(Platform/${CMAKE_SYSTEM_NAME}-${CMAKE_C_COMPILER_ID}-C
    OPTIONAL RESULT_VARIABLE _INCLUDED_FILE)
ENDIF(CMAKE_C_COMPILER_ID)
IF (NOT _INCLUDED_FILE)
  INCLUDE(Platform/${CMAKE_SYSTEM_NAME}-${CMAKE_BASE_NAME} 
    OPTIONAL RESULT_VARIABLE _INCLUDED_FILE)
ENDIF (NOT _INCLUDED_FILE)
# We specify the compiler information in the system file for some
# platforms, but this language may not have been enabled when the file
# was first included.  Include it again to get the language info.
# Remove this when all compiler info is removed from system files.
IF (NOT _INCLUDED_FILE)
  INCLUDE(Platform/${CMAKE_SYSTEM_NAME} OPTIONAL)
ENDIF (NOT _INCLUDED_FILE)


# This should be included before the _INIT variables are
# used to initialize the cache.  Since the rule variables 
# have if blocks on them, users can still define them here.
# But, it should still be after the platform file so changes can
# be made to those values.

IF(CMAKE_USER_MAKE_RULES_OVERRIDE)
   INCLUDE(${CMAKE_USER_MAKE_RULES_OVERRIDE})
ENDIF(CMAKE_USER_MAKE_RULES_OVERRIDE)

IF(CMAKE_USER_MAKE_RULES_OVERRIDE_C)
   INCLUDE(${CMAKE_USER_MAKE_RULES_OVERRIDE_C})
ENDIF(CMAKE_USER_MAKE_RULES_OVERRIDE_C)


# for most systems a module is the same as a shared library
# so unless the variable CMAKE_MODULE_EXISTS is set just
# copy the values from the LIBRARY variables
IF(NOT CMAKE_MODULE_EXISTS)
  SET(CMAKE_SHARED_MODULE_C_FLAGS ${CMAKE_SHARED_LIBRARY_C_FLAGS})
  SET(CMAKE_SHARED_MODULE_CREATE_C_FLAGS ${CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS})
ENDIF(NOT CMAKE_MODULE_EXISTS)

SET(CMAKE_C_FLAGS_INIT "$ENV{CFLAGS} ${CMAKE_C_FLAGS_INIT}")
# avoid just having a space as the initial value for the cache 
IF(CMAKE_C_FLAGS_INIT STREQUAL " ")
  SET(CMAKE_C_FLAGS_INIT)
ENDIF(CMAKE_C_FLAGS_INIT STREQUAL " ")
SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS_INIT}" CACHE STRING
     "Flags used by the compiler during all build types.")

IF(NOT CMAKE_NOT_USING_CONFIG_FLAGS)
# default build type is none
  IF(NOT CMAKE_NO_BUILD_TYPE)
    SET (CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_INIT} CACHE STRING 
      "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
  ENDIF(NOT CMAKE_NO_BUILD_TYPE)
  SET (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG_INIT}" CACHE STRING
    "Flags used by the compiler during debug builds.")
  SET (CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL_INIT}" CACHE STRING
    "Flags used by the compiler during release minsize builds.")
  SET (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE_INIT}" CACHE STRING
    "Flags used by the compiler during release builds (/MD /Ob1 /Oi /Ot /Oy /Gs will produce slightly less optimized but smaller files).")
  SET (CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO_INIT}" CACHE STRING
    "Flags used by the compiler during Release with Debug Info builds.")
ENDIF(NOT CMAKE_NOT_USING_CONFIG_FLAGS)

IF(CMAKE_C_STANDARD_LIBRARIES_INIT)
  SET(CMAKE_C_STANDARD_LIBRARIES "${CMAKE_C_STANDARD_LIBRARIES_INIT}"
    CACHE STRING "Libraries linked by defalut with all C applications.")
  MARK_AS_ADVANCED(CMAKE_C_STANDARD_LIBRARIES)
ENDIF(CMAKE_C_STANDARD_LIBRARIES_INIT)

INCLUDE(CMakeCommonLanguageInclude)

# now define the following rule variables

# CMAKE_C_CREATE_SHARED_LIBRARY
# CMAKE_C_CREATE_SHARED_MODULE
# CMAKE_C_COMPILE_OBJECT
# CMAKE_C_LINK_EXECUTABLE

# variables supplied by the generator at use time
# <TARGET>
# <TARGET_BASE> the target without the suffix
# <OBJECTS>
# <OBJECT>
# <LINK_LIBRARIES>
# <FLAGS>
# <LINK_FLAGS>

# C compiler information
# <CMAKE_C_COMPILER>  
# <CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS>
# <CMAKE_SHARED_MODULE_CREATE_C_FLAGS>
# <CMAKE_C_LINK_FLAGS>

# Static library tools
# <CMAKE_AR> 
# <CMAKE_RANLIB>


# create a C shared library
IF(NOT CMAKE_C_CREATE_SHARED_LIBRARY)
  SET(CMAKE_C_CREATE_SHARED_LIBRARY
      "<CMAKE_C_COMPILER> <CMAKE_SHARED_LIBRARY_C_FLAGS> <LANGUAGE_COMPILE_FLAGS> <LINK_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS> <CMAKE_SHARED_LIBRARY_SONAME_C_FLAG><TARGET_SONAME> -o <TARGET> <OBJECTS> <LINK_LIBRARIES>")
ENDIF(NOT CMAKE_C_CREATE_SHARED_LIBRARY)

# create a C shared module just copy the shared library rule
IF(NOT CMAKE_C_CREATE_SHARED_MODULE)
  SET(CMAKE_C_CREATE_SHARED_MODULE ${CMAKE_C_CREATE_SHARED_LIBRARY})
ENDIF(NOT CMAKE_C_CREATE_SHARED_MODULE)

# Create a static archive incrementally for large object file counts.
# If CMAKE_C_CREATE_STATIC_LIBRARY is set it will override these.
SET(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> cr <TARGET> <LINK_FLAGS> <OBJECTS>")
SET(CMAKE_C_ARCHIVE_APPEND "<CMAKE_AR> r  <TARGET> <LINK_FLAGS> <OBJECTS>")
SET(CMAKE_C_ARCHIVE_FINISH "<CMAKE_RANLIB> <TARGET>")

# compile a C file into an object file
IF(NOT CMAKE_C_COMPILE_OBJECT)
  SET(CMAKE_C_COMPILE_OBJECT
    "<CMAKE_C_COMPILER> <DEFINES> <FLAGS> -o <OBJECT>   -c <SOURCE>")
ENDIF(NOT CMAKE_C_COMPILE_OBJECT)

IF(NOT CMAKE_C_LINK_EXECUTABLE)
  SET(CMAKE_C_LINK_EXECUTABLE
    "<CMAKE_C_COMPILER> <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")
ENDIF(NOT CMAKE_C_LINK_EXECUTABLE)

IF(NOT CMAKE_EXECUTABLE_RUNTIME_C_FLAG)
  SET(CMAKE_EXECUTABLE_RUNTIME_C_FLAG ${CMAKE_SHARED_LIBRARY_RUNTIME_C_FLAG})
ENDIF(NOT CMAKE_EXECUTABLE_RUNTIME_C_FLAG)

IF(NOT CMAKE_EXECUTABLE_RUNTIME_C_FLAG_SEP)
  SET(CMAKE_EXECUTABLE_RUNTIME_C_FLAG_SEP ${CMAKE_SHARED_LIBRARY_RUNTIME_C_FLAG_SEP})
ENDIF(NOT CMAKE_EXECUTABLE_RUNTIME_C_FLAG_SEP)

IF(NOT CMAKE_EXECUTABLE_RPATH_LINK_C_FLAG)
  SET(CMAKE_EXECUTABLE_RPATH_LINK_C_FLAG ${CMAKE_SHARED_LIBRARY_RPATH_LINK_C_FLAG})
ENDIF(NOT CMAKE_EXECUTABLE_RPATH_LINK_C_FLAG)

MARK_AS_ADVANCED(
CMAKE_C_FLAGS
CMAKE_C_FLAGS_DEBUG
CMAKE_C_FLAGS_MINSIZEREL
CMAKE_C_FLAGS_RELEASE
CMAKE_C_FLAGS_RELWITHDEBINFO
)
SET(CMAKE_C_INFORMATION_LOADED 1)


