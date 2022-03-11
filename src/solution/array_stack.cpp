#include "assignment/array_stack.hpp"

#include <stdexcept>  // invalid_argument

namespace assignment {

  ArrayStack::ArrayStack(int capacity) {
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }
    // Write your code here ...
  }

  ArrayStack::~ArrayStack() {
    // Write your code here ...
  }

  void ArrayStack::Push(int value) {
    // Write your code here ...
  }

  bool ArrayStack::Pop() {
    // Write your code here ...
    return false;
  }

  void ArrayStack::Clear() {
    // Write your code here ...
  }

  std::optional<int> ArrayStack::Peek() const {
    // Write your code here ...
    return std::nullopt;
  }

  bool ArrayStack::IsEmpty() const {
    // Write your code here ...
    return false;
  }

  int ArrayStack::size() const {
    // Write your code here ...
    return 0;
  }

  int ArrayStack::capacity() const {
    // Write your code here ...
    return 0;
  }

  void ArrayStack::Resize(int new_capacity) {
    if (new_capacity <= capacity_) {
      throw std::invalid_argument("new capacity does not exceed current capacity");
    }
    // Write your code here ...
  }

}  // namespace classwork
