#include "kdtree.hpp"
#include <iostream>
#include <vector>

constexpr int DIM = 3;

std::ostream &operator<<(std::ostream &os, std::array<double_t, DIM> arr) {
  for (int i = 0; i < DIM; i++) {
    os << arr[i];
  }
  return os;
}

int main() {

  std::vector<std::array<double_t, DIM>> points = {
      {1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6},
      {5, 6, 7}, {6, 7, 8}, {7, 8, 9}, {8, 9, 10}};

  KDTree<DIM> kdt = KDTree<DIM>(points);

  return 0;
}
