# CMake generated Testfile for 
# Source directory: C:/Users/Owner/Desktop/ELEC278/lab3/lab3
# Build directory: C:/Users/Owner/Desktop/ELEC278/lab3/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[array-case1]=] "C:/Users/Owner/Desktop/ELEC278/lab3/build/array-stack.exe" "C:/Users/Owner/Desktop/ELEC278/lab3/lab3/test-cases/case1.txt")
set_tests_properties([=[array-case1]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Owner/Desktop/ELEC278/lab3/lab3/CMakeLists.txt;20;add_test;C:/Users/Owner/Desktop/ELEC278/lab3/lab3/CMakeLists.txt;0;")
add_test([=[array-case2]=] "C:/Users/Owner/Desktop/ELEC278/lab3/build/array-stack.exe" "C:/Users/Owner/Desktop/ELEC278/lab3/lab3/test-cases/case2.txt" "fail")
set_tests_properties([=[array-case2]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Owner/Desktop/ELEC278/lab3/lab3/CMakeLists.txt;25;add_test;C:/Users/Owner/Desktop/ELEC278/lab3/lab3/CMakeLists.txt;0;")
add_test([=[array-case3]=] "C:/Users/Owner/Desktop/ELEC278/lab3/build/array-stack.exe" "C:/Users/Owner/Desktop/ELEC278/lab3/lab3/test-cases/case3.txt" "fail")
set_tests_properties([=[array-case3]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Owner/Desktop/ELEC278/lab3/lab3/CMakeLists.txt;30;add_test;C:/Users/Owner/Desktop/ELEC278/lab3/lab3/CMakeLists.txt;0;")
add_test([=[linked-case1]=] "C:/Users/Owner/Desktop/ELEC278/lab3/build/linked-stack.exe" "C:/Users/Owner/Desktop/ELEC278/lab3/lab3/test-cases/case1.txt")
set_tests_properties([=[linked-case1]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Owner/Desktop/ELEC278/lab3/lab3/CMakeLists.txt;35;add_test;C:/Users/Owner/Desktop/ELEC278/lab3/lab3/CMakeLists.txt;0;")
add_test([=[linked-case2]=] "C:/Users/Owner/Desktop/ELEC278/lab3/build/linked-stack.exe" "C:/Users/Owner/Desktop/ELEC278/lab3/lab3/test-cases/case2.txt" "fail")
set_tests_properties([=[linked-case2]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Owner/Desktop/ELEC278/lab3/lab3/CMakeLists.txt;40;add_test;C:/Users/Owner/Desktop/ELEC278/lab3/lab3/CMakeLists.txt;0;")
add_test([=[linked-case3]=] "C:/Users/Owner/Desktop/ELEC278/lab3/build/linked-stack.exe" "C:/Users/Owner/Desktop/ELEC278/lab3/lab3/test-cases/case3.txt" "fail")
set_tests_properties([=[linked-case3]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Owner/Desktop/ELEC278/lab3/lab3/CMakeLists.txt;45;add_test;C:/Users/Owner/Desktop/ELEC278/lab3/lab3/CMakeLists.txt;0;")
