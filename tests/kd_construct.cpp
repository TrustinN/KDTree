#include "../src/kdtree.hpp"
#include <gtest/gtest.h>
#include <random>
#include <vector>

template <size_t k> using pt = std::array<double, k>;

TEST(KDTree, Construct) {
  constexpr int DIM = 2;
  //
  //   .(7, 1)
  //         .(6, 4)
  //
  //      .(5, 2)
  //
  ///////////////////

  std::vector<pt<DIM>> points = {{7, 1}, {6, 4}, {5, 2}};
  KDTree<DIM> kdtree(points, 0);

  EXPECT_EQ(kdtree.size(), 3);
};

// TEST(KDTree, kNN) {
//   constexpr int DIM = 2;
//   //
//   //   .(7, 1)
//   //         .(6, 4)
//   //
//   //      .(5, 2)
//   //
//   ///////////////////
//
//   std::vector<pt<DIM>> points = {{7, 1}, {6, 4}, {5, 2}};
//   KDTree<DIM> kdtree(points, 0);
//
//   pt<DIM> point = {6, 1};
//   std::vector<int> result = kdtree.kNearestNeighbors(point);
//   EXPECT_EQ(result[0], 0);
//
//   point = {7, 5};
//   result = kdtree.kNearestNeighbors(point);
//   EXPECT_EQ(result[0], 1);
//
//   point = {5, -3};
//   result = kdtree.kNearestNeighbors(point);
//   EXPECT_EQ(result[0], 2);
// }

TEST(KDTree, kNNBoundary) {
  constexpr int DIM = 2;
  //        .(8, 9)
  //        .query3(8, 8)
  //
  //
  //        .(8, 5)
  //
  //        . query1(8, 3)
  //
  //        . query2(8, 1)
  //        .(8, 0)
  /////////////////////////

  std::vector<pt<DIM>> points = {{8, 0}, {8, 5}, {8, 9}};

  KDTree<DIM> kd(points, 0);

  pt<DIM> query1 = {8, 3};
  std::vector<int> result = kd.kNearestNeighbors(query1);
  EXPECT_EQ(result[0], 1);

  pt<DIM> query2 = {8, 1};
  result = kd.kNearestNeighbors(query2);
  EXPECT_EQ(result[0], 0);

  pt<DIM> query3 = {8, 8};
  result = kd.kNearestNeighbors(query3);
  EXPECT_EQ(result[0], 2);
}

TEST(KDTree, kNNBoundaryDense) {
  constexpr int DIM = 2;
  //--------.R(8, 9)-------
  //        |
  //        |    .(13, 7)
  //        |
  //        .(8, 5)
  //        |
  //        |
  //        |
  //        |
  //--------.L(8, 0)-------
  /////////////////////////

  std::vector<pt<DIM>> points = {{8, 0}, {8, 5}, {8, 9}};

  KDTree<DIM> kd(points, 0);

  pt<DIM> query = {8, 3};

  std::vector<int> result = kd.kNearestNeighbors(query);

  EXPECT_EQ(result[0], 1);
}

TEST(KDTree, kNNRandomDIM2) {
  constexpr int DIM = 2;

  std::vector<pt<DIM>> points = {{8, 0}, {8, 5}, {8, 9}};

  KDTree<DIM> kd(points, 0);

  pt<DIM> query = {1, 2};

  std::vector<int> result = kd.kNearestNeighbors(query);

  // brute force find answer
  pt<DIM> answer;
  double minDist = std::numeric_limits<double>::infinity();
  for (pt<DIM> point : points) {
    pt<DIM> diff;
    std::transform(point.begin(), point.end(), query.begin(), diff.begin(),
                   std::minus<double>());
    double sD = std::accumulate(
        diff.begin(), diff.end(), 0.0,
        [](double sum, double a) { return sum + std::pow(a, 2); });
    if (sD < minDist) {
      minDist = sD;
      answer = point;
    }
  }
}

TEST(KDTree, kNNRandomDIM3) {
  constexpr int DIM = 3;
  const int max_points = 10000;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 100.0);

  std::vector<pt<DIM>> points;
  for (int i = 0; i < max_points; i++) {
    pt<DIM> point;
    std::generate(point.begin(), point.end(), [&]() { return dis(gen); });
    points.push_back(point);
  }

  KDTree<DIM> kd(points, 0);

  pt<DIM> query = {1, 2, 3};

  std::vector<int> result = kd.kNearestNeighbors(query);

  // brute force find answer
  pt<DIM> answer;
  double minDist = std::numeric_limits<double>::infinity();
  for (pt<DIM> point : points) {
    pt<DIM> diff;
    std::transform(point.begin(), point.end(), query.begin(), diff.begin(),
                   std::minus<double>());
    double sD = std::accumulate(
        diff.begin(), diff.end(), 0.0,
        [](double sum, double a) { return sum + std::pow(a, 2); });
    if (sD < minDist) {
      minDist = sD;
      answer = point;
    }
  }

  EXPECT_EQ(answer, points[result[0]]);
}
