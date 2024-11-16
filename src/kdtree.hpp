#ifndef KDTREE_H
#define KDTREE_H

#include <boost/iterator/counting_iterator.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/combine.hpp>
#include <cmath>
#include <iostream>
#include <memory>
#include <numeric>
#include <tuple>
#include <vector>

// -------------------------------------------------------------------------------------------------//
// KDNode
// -------------------------------------------------------------------------------------------------//

template <size_t k> using pt = std::array<double_t, k>;

template <size_t k> struct kdNode {
  kdNode(pt<k> location, int split_axis, int id)
      : left(nullptr), right(nullptr), loc(location), _split_axis(split_axis),
        _id(id){};
  kdNode<k> *left;
  kdNode<k> *right;
  pt<k> loc;
  int _id;
  int _split_axis;
};

template <size_t k>
void explore(kdNode<k> *node, const pt<k> &p,
             std::vector<kdNode<k> *> &traversed) {
  kdNode<k> *currNode = node;
  while (currNode != nullptr) {
    traversed.push_back(currNode);

    int axis = currNode->_split_axis;

    if (p[axis] < currNode->loc[axis]) {
      currNode = currNode->left;
    } else {
      currNode = currNode->right;
    }
  }
};

template <size_t k> class KDTree {
private:
  kdNode<k> *_root;
  size_t _size;
  std::vector<pt<k>> _points;

public:
  KDTree(const std::vector<pt<k>> &points, int depth);
  size_t size() const { return _size; }
  std::vector<int> kNearestNeighbors(const pt<k> &p);
};

template <size_t k>
KDTree<k>::KDTree(const std::vector<pt<k>> &points, int depth) {
  // Initialize stored data
  _size = points.size();
  _points = points;
  _root = nullptr;

  // Do nothing if no points
  if (points.empty()) {
    return;
  }
  std::vector<pt<k>> currPoints = points;
  std::vector<int> range(boost::counting_iterator<int>(0),
                         boost::counting_iterator<int>(currPoints.size()));
  auto currPointsIdxPair = boost::combine(range, currPoints);
  // Initialize combinedPoints vector
  std::vector<std::tuple<int, pt<k>>> combinedPoints;

  // Manually iterate over the combined range and populate combinedPoints
  for (const auto &pair : currPointsIdxPair) {
    combinedPoints.emplace_back(pair.template get<0>(), pair.template get<1>());
  }

  // iteratively build tree, store (current points, parent node of points,
  // depth, left or right flag)
  std::vector<
      std::tuple<std::vector<std::tuple<int, pt<k>>>, kdNode<k> *, int, int>>
      stack = {};
  stack.push_back({combinedPoints, _root, 0, 0});

  while (!stack.empty()) {
    auto [currPoints, parent, depth, side] = stack.back();
    stack.pop_back();
    int axis = depth % k;

    std::sort(currPoints.begin(), currPoints.end(),
              [&axis](const std::tuple<int, pt<k>> &a,
                      const std::tuple<int, pt<k>> &b) {
                return std::get<1>(a)[axis] < std::get<1>(b)[axis];
              });

    int mIdx = currPoints.size() / 2;
    auto [id, median] = currPoints[mIdx];

    // Identify new parent of median node
    kdNode<k> *newNode = new kdNode<k>(median, axis, id);
    if (parent == nullptr) {
      this->_root = newNode;
    } else if (side == 0) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }

    // points on left, right of split
    std::vector<std::tuple<int, pt<k>>> lP(currPoints.begin(),
                                           currPoints.begin() + mIdx);
    std::vector<std::tuple<int, pt<k>>> rP(currPoints.begin() + mIdx + 1,
                                           currPoints.end());

    // continue if non empty
    if (!lP.empty()) {
      stack.push_back({lP, newNode, depth + 1, 0});
    }
    if (!rP.empty()) {
      stack.push_back({rP, newNode, depth + 1, 1});
    }
  }
}

template <size_t k>
std::vector<int> KDTree<k>::kNearestNeighbors(const pt<k> &p) {
  if (_size == 0) {
    return {};
  }

  // crawl down the tree
  std::vector<kdNode<k> *> traversed;
  ::explore<k>(_root, p, traversed);

  double minDist = std::numeric_limits<double>::infinity();
  kdNode<k> *nearestNode = nullptr;

  while (!traversed.empty()) {
    kdNode<k> *node = traversed.back();
    traversed.pop_back();
    pt<k> loc = node->loc;
    pt<k> diff;

    std::transform(loc.begin(), loc.end(), p.begin(), diff.begin(),
                   std::minus<double>());
    double sD = std::accumulate(
        diff.begin(), diff.end(), 0.0,
        [](double sum, double a) { return sum + std::pow(a, 2); });

    if (sD < minDist) {
      minDist = sD;
      nearestNode = node;
    }

    int axis = node->_split_axis;
    // find distance to hyperplane by axis
    if (std::pow(p[axis] - loc[axis], 2) < minDist) {
      // We must explore this node also

      // find out which side of axis node is currently on
      if (p[axis] < loc[axis]) {
        ::explore<k>(node->left, p, traversed);
      } else {
        ::explore<k>(node->right, p, traversed);
      }
    };
  }

  std::vector<int> neighbors = {nearestNode->_id};
  return neighbors;
}

#endif
