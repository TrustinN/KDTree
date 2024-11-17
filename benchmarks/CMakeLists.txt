include(FetchContent)

FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG main)

FetchContent_MakeAvailable(benchmark)

set(DCMAKE_BUILD_TYPE Release)

add_executable(benchmark_kdtree benchmark_kdtree.cpp)
target_link_libraries(benchmark_kdtree PRIVATE benchmark::benchmark)
