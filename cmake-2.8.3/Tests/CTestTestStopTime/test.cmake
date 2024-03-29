CMAKE_MINIMUM_REQUIRED(VERSION 2.1)

# Settings:
SET(CTEST_DASHBOARD_ROOT                "/home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CTestTest")
SET(CTEST_SITE                          "parrot")
SET(CTEST_BUILD_NAME                    "CTestTest-Linux-g++-StopTime")

SET(CTEST_SOURCE_DIRECTORY              "/home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CTestTestStopTime")
SET(CTEST_BINARY_DIRECTORY              "/home/root2u/Desktop/SDL_chinese/cmake-2.8.3/Tests/CTestTestStopTime")
SET(CTEST_CVS_COMMAND                   "CVSCOMMAND-NOTFOUND")
SET(CTEST_CMAKE_GENERATOR               "Unix Makefiles")
SET(CTEST_BUILD_CONFIGURATION           "$ENV{CMAKE_CONFIG_TYPE}")
SET(CTEST_MEMORYCHECK_COMMAND           "/usr/bin/valgrind")
SET(CTEST_MEMORYCHECK_SUPPRESSIONS_FILE "")
SET(CTEST_MEMORYCHECK_COMMAND_OPTIONS   "")
SET(CTEST_COVERAGE_COMMAND              "/usr/bin/gcov")
SET(CTEST_NOTES_FILES                   "${CTEST_SCRIPT_DIRECTORY}/${CTEST_SCRIPT_NAME}")

#CTEST_EMPTY_BINARY_DIRECTORY(${CTEST_BINARY_DIRECTORY})

INCLUDE("${CTEST_BINARY_DIRECTORY}/GetDate.cmake")

CTEST_START(Experimental)
CTEST_CONFIGURE(BUILD "${CTEST_BINARY_DIRECTORY}" RETURN_VALUE res)
CTEST_BUILD(BUILD "${CTEST_BINARY_DIRECTORY}" RETURN_VALUE res)

GET_DATE()
message("curr time: ${${GD_PREFIX}HOUR}:${${GD_PREFIX}MINUTE}:${${GD_PREFIX}SECOND}")
ADD_SECONDS(15)
message("stop time: ${new_hr}:${new_min}:${new_sec}")

CTEST_TEST(BUILD "${CTEST_BINARY_DIRECTORY}" RETURN_VALUE res STOP_TIME "${new_hr}:${new_min}:${new_sec}")

#CTEST_SUBMIT()
