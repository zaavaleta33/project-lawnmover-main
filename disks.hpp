///////////////////////////////////////////////////////////////////////////////
// disks.hpp
//
// Definitions for two algorithms that each solve the alternating disks
// problem.
//
// As provided, this headerctions marked with TOD has four funO comments.
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

enum disk_color { DISK_LIGHT, DISK_DARK};

class disk_state {
private:
  std::vector<disk_color> _colors;

public:
  disk_state(size_t light_count)
    : _colors(light_count * 2, DISK_LIGHT) {

    assert(light_count > 0);

    for (size_t i = 1; i < _colors.size(); i += 2) {
      _colors[i] = DISK_DARK;
    }
  }

  bool operator== (const disk_state& rhs) const {//comparing begining to end
    return std::equal(_colors.begin(), _colors.end(), rhs._colors.begin());
  }

  size_t total_count() const {//returns size of _colors 
    return _colors.size();
  }

  size_t light_count() const {//returns all the dark disk colors
    return total_count() / 2;
  }

  size_t dark_count() const {//returns all the dark disk colors
    return light_count();
  }

  bool is_index(size_t i) const {//takes in an index and returns that index if it is in the total size of _colors
    return (i < total_count());
  }

  disk_color get(size_t index) const {//takes in an index and returns a disk color
    assert(is_index(index));
    return _colors[index];
  }

  void swap(size_t left_index) {//swaps the left index with the right index
    assert(is_index(left_index));
    auto right_index = left_index + 1;
    assert(is_index(right_index));
    std::swap(_colors[left_index], _colors[right_index]);
  }

  std::string to_string() const {
    std::stringstream ss;
    bool first = true;
    for (auto color : _colors) {
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
      for (size_t i = 0; i < total_count(); i++){     //check each position before function
        if (i % 2 == 0){                              //check even position --> should be light
            if (_colors[i] == DISK_DARK) {
              return false;
            }
        } else {                                      //check odd position --> should be dark
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
      
      return true;
  }
};

// Data structure for the output of the alternating disks problem. That
// includes both the final disk_state, as well as a count of the number
// of swaps performed.
class sorted_disks {
private:
  disk_state _after;
  unsigned _swap_count;

public:

  sorted_disks(const disk_state& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }

  sorted_disks(disk_state&& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }

  const disk_state& after() const {
    return _after;
  }

  unsigned swap_count() const {
    return _swap_count;
  }
};



// Algorithm that sorts disks using the alternate algorithm.
sorted_disks sort_alternate(const disk_state& before) {
  
	int numOfSwap = 0;
  disk_state af = before;
  int backwards = 0;
  int swaps_back = 1; 
  bool back = false;
  for(size_t i = 0; i < before.total_count();i++){              //record # of step swap
      if(before.is_index(i) == DISK_DARK && before.is_index(i + 1) == DISK_LIGHT){
       af.swap(i);//
       numOfSwap++;//
      }
      //back = true;
      if(before.is_index(i) == before.total_count() - 1){
        for(size_t j = 0; j < before.total_count();j++){ 
          if(before.is_index(j) == DISK_DARK && before.is_index(j + 1) == DISK_LIGHT){
            af.swap(j);//
            numOfSwap++;//
          }
        }
      }
  }
    
      // i = 0 and i + 1 = 1
      // i = 1 and i + 1 = 2
      // i = 2 and i + 1 = 3
      // i = 3 and i + 1 = 4
      // i = 3 and i + 1 = 5
     
      //Step 1: L D L D L D
      //Step 2: L L D D L D
      //Step 3: L L D D L D
      //Step 4: L L D L D D
      
      
      // set a variable = true
  
  return sorted_disks(disk_state(state), numOfSwap);
}

// while(back == true){
    //      if(before.is_index(i-1) == DISK_LIGHT && before.is_index(i) == DISK_LIGHT){
    //       back = false;
    //       swaps_back = 0;
    //      } else{
    //       af.swap(i-swaps_back);
    //       swaps_back++;
    //      }
    //    }

// Algorithm that sorts disks using the lawnmower algorithm.
sorted_disks sort_lawnmower(const disk_state& before) {
  //the only move we can make is when one disk is next to another one	
  //second algorightm for this seems to be easir
	//}
  //!it does not iterate thorugh each and every index but iterates over each pair
  //Todo1:create a forloop that goes through every other pair
  //Todo2:Create another loop that goes through every disk
  //Todo3:Does the same thing as Todo1
  //todo4:does the same thing as Todo2 
  //!Steps 1 and 2 are reapeated every time
  return sorted_disks(disk_state(state), numOfSwap);
}
