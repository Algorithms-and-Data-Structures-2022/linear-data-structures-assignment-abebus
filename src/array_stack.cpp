#include "assignment/array_stack.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  ArrayStack::ArrayStack(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость стека
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

  bool ArrayStack::Resize(int new_capacity) {
    // Write your code here ...
    return false;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  ArrayStack::ArrayStack(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> ArrayStack::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment
