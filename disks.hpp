///////////////////////////////////////////////////////////////////////////////
// disks.hpp
//
// Definitions for two algorithms that each solve the alternating disks
// problem.
//
// As provided, this header has four functions marked with TODO comments.
// You need to write in your own implementation of these functions.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>

#include <cassert>

#include <cstddef>

#include <sstream>

#include <string>

#include <vector>

#include <functional>

#include <iostream>

enum disk_color {
  DISK_LIGHT,
  DISK_DARK
};

class disk_state {
  private: std::vector < disk_color > _colors;

  public: disk_state(size_t light_count): _colors(light_count * 2, DISK_LIGHT) {

    assert(light_count > 0);

    for (size_t i = 1; i < _colors.size(); i += 2) {
      _colors[i] = DISK_DARK;
    }
  }

  bool operator == (const disk_state & rhs) const {
    return std::equal(_colors.begin(), _colors.end(), rhs._colors.begin());
  }

  size_t total_count() const {
    return _colors.size();
  }

  size_t light_count() const {
    return total_count() / 2;
  }

  size_t dark_count() const {
    return light_count();
  }

  bool is_index(size_t i) const {
    return (i < total_count());
  }

  disk_color get(size_t index) const {
    assert(is_index(index));
    return _colors[index];
  }

  void swap(size_t left_index) {
    assert(is_index(left_index));
    auto right_index = left_index + 1;
    assert(is_index(right_index));
    std::swap(_colors[left_index], _colors[right_index]);
  }

  std::string to_string() const {
    std::stringstream ss;
    bool first = true;
    for (auto color: _colors) {
      if (!first) {
        ss << " ";
      }

      if (color == DISK_LIGHT) {
        ss << "L";
      } else {
        ss << "D";
      }

      first = false;
    }
    return ss.str();
  }

  // Return true when this disk_state is in alternating format. That means
  // that the first disk at index 0 is light, the second disk at index 1
  // is dark, and so on for the entire row of disks.
  bool is_initialized() const {
    for (size_t i = 0; i < total_count(); i++) { //check each position before function
      if (i % 2 == 0) { //check even position --> should be light
        if (_colors[i] == DISK_DARK) {
          return false;
        }
      } else { //check odd position --> should be dark
        if (_colors[i] == DISK_LIGHT) {
          return false;
        }
      }
    }

    return true;
  }

  // Return true when this disk_state is fully sorted, with all light disks on
  // the left (low indices) and all dark disks on the right (high indices).
  bool is_sorted() const {
    for (size_t i = 0; i < total_count() - 1; i++) { //iterate through whole array
      if (i < total_count() / 2 && get(i) != DISK_LIGHT) { //check's to see if i is less than totalcount/2 and if light is not a light disk
        return false;
      }
      if (i > total_count() / 2 && get(i) != DISK_DARK) { //check's to see if i is greate then half the total_count and sees if it's a dark disk
        return false;
      }
    }
    return true;
  }
};

// Data structure for the output of the alternating disks problem. That
// includes both the final disk_state, as well as a count of the number
// of swaps performed.
class sorted_disks {
  private: disk_state _after;
  unsigned _swap_count;

  public:

    sorted_disks(const disk_state & after, unsigned swap_count): _after(after),
  _swap_count(swap_count) {}

  sorted_disks(disk_state && after, unsigned swap_count): _after(after),
  _swap_count(swap_count) {}

  const disk_state & after() const {
    return _after;
  }

  unsigned swap_count() const {
    return _swap_count;
  }
};

// Algorithm that sorts disks using the alternate algorithm.
sorted_disks sort_alternate(const disk_state & before) {
  int numOfSwap = 0; //record # of step swap
  disk_state af = before; //copies everything from before into af
  for (size_t i = 0; i < af.total_count() - 1; i++) { //iterate thorugh each index
    for (size_t j = 0; j < af.total_count() - 1; j += 2) { //iterate through all the odd 
      //!this first iteration goes through each and every iteration
      if (af.get(j) == DISK_DARK && af.get(j + 1) == DISK_LIGHT) {
        af.swap(j); ////swaps a and the next index
        numOfSwap++; ////add's to numswap counter
      }
    }
    for (size_t a = 1; a < af.total_count() - 1; a += 2) { //iterats through all the even
      if (af.get(a) == DISK_DARK && af.get(a + 1) == DISK_LIGHT) {
        af.swap(a); //swaps a and the next index
        numOfSwap++; //add's to numswap counter
      }
    }
  }
  return sorted_disks(disk_state(af /*state*/ ), numOfSwap);
}

// Algorithm that sorts disks using the lawnmower algorithm.
sorted_disks sort_lawnmower(const disk_state & before) {
  //the only move we can make is when one disk is next to another one	
  //second algorightm for this seems to be easir
  disk_state aft = before;
  int num_swap = 0;
  //Todo:start from the left and go to each iteration
  for (size_t i = 0; i < aft.total_count() - 1; i++) {
    for (size_t j = 0; j < aft.total_count() - 1; j++) { //iterates from left to right
      if (aft.get(j) == DISK_DARK && aft.get(j + 1) == DISK_LIGHT) {
        aft.swap(j); //swaps from left to right
        num_swap++; //increases the numswap
      }
    }
    for (size_t t = aft.total_count() - 1; t > 0; t--) { //iterates from right to left
      if (aft.get(t) == DISK_LIGHT && aft.get(t - 1) == DISK_DARK) {
        aft.swap(t - 1); //swaps from right to left
        num_swap++; //increases the numswap
      }
    }
  }
  //Todo: Once you reach the end you go from right to left
  return sorted_disks(disk_state(aft), num_swap);
}