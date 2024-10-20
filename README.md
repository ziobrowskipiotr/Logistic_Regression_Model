# My Logistic Regression Project

This project implements logistic regression in C++ using SQLite for data storage and Google Test for unit testing.

## Table of Contents
1. [Project Structure](#project-structure)
2. [Setup Instructions](#setup-instructions)
   - [1. Create the `build` directory](#1-create-the-build-directory)
   - [2. Install required dependencies](#2-install-required-dependencies)
   - [3. Download external dependencies](#3-download-external-dependencies)
   - [4. Unpack downloaded files](#4-unpack-downloaded-files)
   - [5. Build the project](#5-build-the-project)
   - [6. Run the project](#6-run-the-project)
   - [7. Run the tests](#7-run-the-tests)
3. [Notes](#notes)

## Project Structure

```plaintext
.
├── database
│   ├── logs.sqlite              # SQLite database for logging
│   ├── logs.txt                 # Log file for fallback logging
│   ├── test_data.sqlite         # SQLite database for testing data
│   ├── trening_data.sqlite      # SQLite database for training data
├── libs                         # External libraries (e.g., SQLite)
├── src
│   ├── include
│   │   ├── DatabaseOperations.h # Header for database operations class
│   │   ├── Logger.h             # Header for Logger class
│   │   ├── LogisticRegression.h # Header for logistic regression class
│   ├── DatabaseOperations.cpp   # Implementation of database operations
│   ├── Logger.cpp               # Implementation of the Logger
│   ├── LogisticRegression.cpp   # Implementation of logistic regression
│   ├── main.cpp                 # Main program file
├── tests
│   ├── test_db
│   │   ├── empty_test.sqlite    # Empty SQLite database for tests
│   │   ├── valid_test.sqlite    # Valid SQLite database for tests
│   ├── test_DatabaseOperations.cpp # Unit tests for DatabaseOperations
│   ├── test_Logger.cpp          # Unit tests for Logger
│   ├── test_LogisticRegression.cpp # Unit tests for LogisticRegression
├── CMakeLists.txt               # CMake configuration file
├── My_Logistic_Regression_Project.exe # Main program executable
├── Tests_Project.exe            # Executable for tests
```
## Setup Instructions

### 1. Create the `build` directory

You need to create a `build` directory to store the compiled files.

```bash
mkdir build
cd build
```

### 2. Install required dependencies

Ensure you have the following dependencies installed on your system:

- **CMake** (minimum version 3.5.0)
- **C++17 compatible compiler** (e.g., GCC, Clang, MSVC)
- **Google Test** (this will be automatically fetched during the build process)
- **SQLite3** (if not installed, the project includes the required SQLite3 files in the `libs.zip`)

### 3. Download external dependencies

Go to the [Release Section](https://github.com/ziobrowskipiotr/del_libs/releases) to download:
- `database.zip` — contains necessary SQLite databases.
- `libs.zip` — contains external libraries (e.g., SQLite).

### 4. Unpack downloaded files

Unzip both `database.zip` and `libs.zip` in the root directory of the project. After unzipping, the structure should look like this:

```plaintext
.
├── database
│   ├── logs.sqlite
│   ├── logs.txt
│   ├── test_data.sqlite
│   ├── trening_data.sqlite
├── libs
│   └── sqlite-amalgamation-3460100
```
### 5. Build the project

Run the following commands from the `build` directory (which you created in step 1):

```bash
cmake ..
cmake --build .
```

### 6. Run the project

After building the project, you can run the main program by executing the following command inside the `root` directory:

```bash
./My_Logistic_Regression_Project
```

### 7. Run the tests

To run the unit tests, execute the following command inside the `root` directory:

```bash
./Tests_Project
```

## Notes

- The logs from failed database operations will be stored in both `logs.sqlite` (if possible) and `logs.txt`.
- Test databases (`empty_test.sqlite` and `valid_test.sqlite`) are included in the `test_db` folder for testing purposes.
