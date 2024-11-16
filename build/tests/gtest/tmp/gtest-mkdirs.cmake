# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/Users/trustinnguyen/Downloads/Programming/CPP/KDTree/build/tests/gtest/src/gtest")
  file(MAKE_DIRECTORY "/Users/trustinnguyen/Downloads/Programming/CPP/KDTree/build/tests/gtest/src/gtest")
endif()
file(MAKE_DIRECTORY
  "/Users/trustinnguyen/Downloads/Programming/CPP/KDTree/build/tests/gtest/src/gtest-build"
  "/Users/trustinnguyen/Downloads/Programming/CPP/KDTree/build/tests/gtest"
  "/Users/trustinnguyen/Downloads/Programming/CPP/KDTree/build/tests/gtest/tmp"
  "/Users/trustinnguyen/Downloads/Programming/CPP/KDTree/build/tests/gtest/src/gtest-stamp"
  "/Users/trustinnguyen/Downloads/Programming/CPP/KDTree/build/tests/gtest/src"
  "/Users/trustinnguyen/Downloads/Programming/CPP/KDTree/build/tests/gtest/src/gtest-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/trustinnguyen/Downloads/Programming/CPP/KDTree/build/tests/gtest/src/gtest-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/trustinnguyen/Downloads/Programming/CPP/KDTree/build/tests/gtest/src/gtest-stamp${cfgdir}") # cfgdir has leading slash
endif()
