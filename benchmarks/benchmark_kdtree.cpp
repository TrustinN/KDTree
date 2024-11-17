#include "../src/kdtree.hpp"
#include "benchmark/benchmark.h"
#include <random>
#include <vector>

template <size_t k> using pt = std::array<double, k>;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0.0, 100.0);

template <size_t k>
KDTree<k> constructRandomKDTree(std::mt19937 &gen, int num_points) {
  std::vector<pt<k>> points(num_points);

  for (int i = 0; i < num_points; i++) {
    pt<k> point;
    std::generate(point.begin(), point.end(), [&]() { return gen(); });
    points.push_back(point);
  }

  return KDTree<k>(points);
}

static void BM_Constructor(benchmark::State &state) {
  constexpr int DIM = 3;
  int num_points = 10000;

  for (auto _ : state)
    KDTree<DIM> kd = constructRandomKDTree<DIM>(gen, num_points);
}

static void BM_1NN(benchmark::State &state) {
  constexpr int DIM = 3;
  int num_points = 10000;

  KDTree<DIM> kd = constructRandomKDTree<DIM>(gen, num_points);
  int num_nn = 1;
  pt<DIM> query = {2.4, 45.2, 30.5};

  for (auto _ : state)
    std::vector<int> nn = kd.kNearestNeighbors(query, num_nn);
}

static void BM_kNN(benchmark::State &state) {
  constexpr int DIM = 3;
  int num_points = 10000;

  KDTree<DIM> kd = constructRandomKDTree<DIM>(gen, num_points);
  int num_nn = 30;
  pt<DIM> query = {2.4, 45.2, 30.5};

  for (auto _ : state)
    std::vector<int> nn = kd.kNearestNeighbors(query, num_nn);
}

BENCHMARK(BM_Constructor);
BENCHMARK(BM_1NN);
BENCHMARK(BM_kNN);

BENCHMARK_MAIN();
