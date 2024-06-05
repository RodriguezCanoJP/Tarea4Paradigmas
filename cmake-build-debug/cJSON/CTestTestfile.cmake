# CMake generated Testfile for 
# Source directory: /Users/juanpablorodriguez/CLionProjects/PolePosition/cJSON
# Build directory: /Users/juanpablorodriguez/CLionProjects/PolePosition/cmake-build-debug/cJSON
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cJSON_test "/Users/juanpablorodriguez/CLionProjects/PolePosition/cmake-build-debug/cJSON/cJSON_test")
set_tests_properties(cJSON_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/juanpablorodriguez/CLionProjects/PolePosition/cJSON/CMakeLists.txt;248;add_test;/Users/juanpablorodriguez/CLionProjects/PolePosition/cJSON/CMakeLists.txt;0;")
subdirs("tests")
subdirs("fuzzing")
