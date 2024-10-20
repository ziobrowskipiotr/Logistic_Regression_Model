# My Logistic Regression Project

This project implements logistic regression in C++ using SQLite for data storage and Google Test for unit testing.

## Table of Contents
1. [Project Structure](#project-structure)
2. [About the Dataset](#about-the-dataset)
3. [Setup Instructions](#setup-instructions)
   - [1. Create the `build` directory](#1-create-the-build-directory)
   - [2. Install required dependencies](#2-install-required-dependencies)
   - [3. Download external dependencies](#3-download-external-dependencies)
   - [4. Unpack downloaded files](#4-unpack-downloaded-files)
   - [5. Customize Gradient Descent Parameters](#5-customize-gradient-descent-parameters)
   - [6. Adding Custom Databases](#6-adding-custom-databases)
   - [7. Build the project](#7-build-the-project)
   - [8. Run the project](#8-run-the-project)
   - [9. Run the tests](#9-run-the-tests)
4. [Notes](#notes)

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
## About the Dataset

This dataset originates from 1988 and includes data from four sources: Cleveland, Hungary, Switzerland, and Long Beach V. Although the dataset contains 76 attributes in total, most research and experiments use a subset of 14 key attributes. 

The "target" attribute indicates the presence of heart disease, where 0 denotes no disease and 1 indicates the presence of disease.

### Key Attributes:

- `age`: Age of the patient
- `sex`: Gender (1 = male, 0 = female)
- `cp`: Chest pain type (4 types)
- `trestbps`: Resting blood pressure (in mm Hg)
- `chol`: Serum cholesterol level (in mg/dl)
- `fbs`: Fasting blood sugar > 120 mg/dl (1 = true; 0 = false)
- `restecg`: Resting electrocardiographic results (values 0, 1, 2)
- `thalach`: Maximum heart rate achieved
- `exang`: Exercise-induced angina (1 = yes; 0 = no)
- `oldpeak`: ST depression induced by exercise relative to rest
- `slope`: The slope of the peak exercise ST segment
- `ca`: Number of major vessels (0–3) colored by fluoroscopy
- `thal`: Thalassemia status (0 = normal, 1 = fixed defect, 2 = reversible defect)
- `target`: Diagnosis of heart disease (0 = no disease, 1 = disease)

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

### 5. Customize Gradient Descent Parameters

In this project, you can adjust the parameters for logistic regression, such as the learning rate (`alpha`) and the number of iterations, directly in the code.

#### Parameters

- `alpha`: Controls the learning rate of gradient descent.
- `iterations`: Determines the number of steps gradient descent will take.
- `k_folds`: Number of folds used in cross-validation.

You can modify these parameters in the `main.cpp` file directly. Below is a code fragment showing how `alpha` and `iterations` are set:

```cpp
int main() {
    // Settings for gradient descent
    double alpha = 0.000001;   // Learning rate
    int iterations = 1000000;  // Number of iterations
    int k_folds = 5;           // Number of folds for cross-validation
```

### 6. Adding Custom Databases

You can add custom SQLite databases for training or testing the logistic regression model. However, these databases **must have the exact same structure and format** as the provided `trening_data.sqlite` and `test_data.sqlite` files.

#### Requirements for Custom Databases:
- The database must include a table named `tablica`.
- The table must have the following columns in the correct order:
  - `age`, `sex`, `cp`, `trestbps`, `chol`, `fbs`, `restecg`, `thalach`, `exang`, `oldpeak`, `slope`, `ca`, `thal`, `target`.
- The data types and values for each column should follow the format provided in the original datasets:
  - `age`: integer
  - `sex`: integer (1 = male, 0 = female)
  - `cp`: integer (chest pain type)
  - and so on for all attributes.

#### Example:

If you have a new dataset and want to add it as `my_custom_data.sqlite`, ensure the structure matches exactly with the above schema. You can then initialize and use it in the code like this:

```cpp
DatabaseOperations db_train("database/my_custom_data.sqlite", &db1);
```

### 7. Build the project

Run the following commands from the `build` directory (which you created in step 1):

```bash
cmake ..
cmake --build .
```

### 8. Run the project

After building the project, you can run the main program by executing the following command inside the `root` directory:

```bash
./My_Logistic_Regression_Project
```

### 9. Run the tests

To run the unit tests, execute the following command inside the `root` directory:

```bash
./Tests_Project
```

## Notes

- The logs from failed database operations will be stored in both `logs.sqlite` (if possible) and `logs.txt`.
- Test databases (`empty_test.sqlite` and `valid_test.sqlite`) are included in the `test_db` folder for testing purposes.
