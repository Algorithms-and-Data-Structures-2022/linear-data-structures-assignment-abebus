#include "assignment/dynamic_array.hpp"

#include <stdexcept>  // invalid_argument

#include "assignment/private/private.hpp"  // check_out_of_range

namespace assignment {

  DynamicArray::DynamicArray(int capacity) {
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }
    // Write your code here ...
  }

  DynamicArray::~DynamicArray() {
    // Write your code here ...
  }

  void DynamicArray::Add(int value) {
    // Write your code here ...
  }

  void DynamicArray::Insert(int index, int value) {
    internal::check_out_of_range(index, 0, size_);
    // Write your code here ...
  }

  void DynamicArray::Set(int index, int new_value) {
    internal::check_out_of_range(index, 0, size_);
    // Write your code here ...
  }

  int DynamicArray::Remove(int index) {
    internal::check_out_of_range(index, 0, size_);
    // Write your code here ...
    return 0;
  }

  void DynamicArray::Clear() {
    // Write your code here ...
  }

  int DynamicArray::Get(int index) const {
    internal::check_out_of_range(index, 0, size_);
    // Write your code here ...
    return 0;
  }

  int DynamicArray::IndexOf(int value) const {
    // Write your code here ...
    return 0;
  }

  bool DynamicArray::Contains(int value) const {
    // Write your code here ...
    return false;
  }

  bool DynamicArray::IsEmpty() const {
    // Write your code here ...
    return false;
  }

  int DynamicArray::size() const {
    // Write your code here ...
    return 0;
  }

  int DynamicArray::capacity() const {
    // Write your code here ...
    return 0;
  }

  void DynamicArray::Resize(int new_capacity) {
    if (new_capacity <= capacity_) {
      throw std::invalid_argument("new capacity does not exceed current capacity");
    }
    // Write your code here ...
  }

}  // namespace classwork