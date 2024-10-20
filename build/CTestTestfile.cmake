# CMake generated Testfile for 
# Source directory: C:/Users/piete/Desktop/My_Logistic_Regression_Project
# Build directory: C:/Users/piete/Desktop/My_Logistic_Regression_Project/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(Tests_Project "C:/Users/piete/Desktop/My_Logistic_Regression_Project/build/Debug/Tests_Project.exe")
  set_tests_properties(Tests_Project PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/piete/Desktop/My_Logistic_Regression_Project/CMakeLists.txt;66;add_test;C:/Users/piete/Desktop/My_Logistic_Regression_Project/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(Tests_Project "C:/Users/piete/Desktop/My_Logistic_Regression_Project/build/Release/Tests_Project.exe")
  set_tests_properties(Tests_Project PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/piete/Desktop/My_Logistic_Regression_Project/CMakeLists.txt;66;add_test;C:/Users/piete/Desktop/My_Logistic_Regression_Project/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(Tests_Project "C:/Users/piete/Desktop/My_Logistic_Regression_Project/build/MinSizeRel/Tests_Project.exe")
  set_tests_properties(Tests_Project PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/piete/Desktop/My_Logistic_Regression_Project/CMakeLists.txt;66;add_test;C:/Users/piete/Desktop/My_Logistic_Regression_Project/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(Tests_Project "C:/Users/piete/Desktop/My_Logistic_Regression_Project/build/RelWithDebInfo/Tests_Project.exe")
  set_tests_properties(Tests_Project PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/piete/Desktop/My_Logistic_Regression_Project/CMakeLists.txt;66;add_test;C:/Users/piete/Desktop/My_Logistic_Regression_Project/CMakeLists.txt;0;")
else()
  add_test(Tests_Project NOT_AVAILABLE)
endif()
subdirs("_deps/googletest-build")
