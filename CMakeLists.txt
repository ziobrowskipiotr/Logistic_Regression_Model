# PROJECT CONFIGURATION

cmake_minimum_required(VERSION 3.5.0)
project(My_Logistic_Regression_Project VERSION 0.1.0 LANGUAGES C CXX)

# Enable C++17 support
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory to the search path for headers
include_directories(${CMAKE_SOURCE_DIR}/src/include)

# Source files
set(SOURCES src/main.cpp src/LogisticRegression.cpp src/DatabaseOperations.cpp src/Logger.cpp libs/sqlite-amalgamation-3460100/sqlite3.c)

# Create the executable file
add_executable(My_Logistic_Regression_Project ${SOURCES})

# Add include directory for sqlite3.h
target_include_directories(My_Logistic_Regression_Project PRIVATE ${CMAKE_SOURCE_DIR}/libs/sqlite-amalgamation-3460100)

# Copy the executable file to the parent directory after build
add_custom_command(TARGET My_Logistic_Regression_Project
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:My_Logistic_Regression_Project> ../
)

# Packaging the project
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# ---------------------------------------------------------------
# TESTS CONFIGURATION

# Enable testing
enable_testing()

# Fetch Google Test without needing a system installation
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# Fetch and add Google Test
FetchContent_MakeAvailable(googletest)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add test source files
set(TEST_SOURCES tests/test_DatabaseOperations.cpp tests/test_Logger.cpp tests/test_LogisticRegression.cpp src/LogisticRegression.cpp src/DatabaseOperations.cpp src/Logger.cpp libs/sqlite-amalgamation-3460100/sqlite3.c)

# Create the executable for tests
add_executable(Tests_Project ${TEST_SOURCES})

# Add include directory for tests
target_include_directories(Tests_Project PRIVATE ${CMAKE_SOURCE_DIR}/libs/sqlite-amalgamation-3460100)

# Link the test executable with libraries
target_link_libraries(Tests_Project PRIVATE gtest gtest_main)

# Add tests to the project
add_test(NAME Tests_Project COMMAND Tests_Project)

# Copy the test executable to the parent directory after build
add_custom_command(TARGET Tests_Project
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Tests_Project> ../
)
