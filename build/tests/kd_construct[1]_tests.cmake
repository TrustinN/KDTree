add_test([=[KDTree.Construct]=]  /Users/trustinnguyen/Downloads/Programming/CPP/KDTree/build/tests/kd_construct [==[--gtest_filter=KDTree.Construct]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[KDTree.Construct]=]  PROPERTIES WORKING_DIRECTORY /Users/trustinnguyen/Downloads/Programming/CPP/KDTree/build/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[KDTree.kNN]=]  /Users/trustinnguyen/Downloads/Programming/CPP/KDTree/build/tests/kd_construct [==[--gtest_filter=KDTree.kNN]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[KDTree.kNN]=]  PROPERTIES WORKING_DIRECTORY /Users/trustinnguyen/Downloads/Programming/CPP/KDTree/build/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[KDTree.kNNRandomDIM2]=]  /Users/trustinnguyen/Downloads/Programming/CPP/KDTree/build/tests/kd_construct [==[--gtest_filter=KDTree.kNNRandomDIM2]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[KDTree.kNNRandomDIM2]=]  PROPERTIES WORKING_DIRECTORY /Users/trustinnguyen/Downloads/Programming/CPP/KDTree/build/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[KDTree.kNNRandomDIM3]=]  /Users/trustinnguyen/Downloads/Programming/CPP/KDTree/build/tests/kd_construct [==[--gtest_filter=KDTree.kNNRandomDIM3]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[KDTree.kNNRandomDIM3]=]  PROPERTIES WORKING_DIRECTORY /Users/trustinnguyen/Downloads/Programming/CPP/KDTree/build/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  kd_construct_TESTS KDTree.Construct KDTree.kNN KDTree.kNNRandomDIM2 KDTree.kNNRandomDIM3)
