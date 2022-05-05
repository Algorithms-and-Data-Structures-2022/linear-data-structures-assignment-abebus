#include "assignment/array_stack.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  ArrayStack::ArrayStack(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость стека
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }

    capacity_ = capacity;
    data_ = new int[capacity];
    std::fill(data_, data_ + capacity, 0);
  }

  ArrayStack::~ArrayStack() {

    delete[] data_;
    Clear();
    capacity_ = 0;
    data_ = nullptr;
  }

  void ArrayStack::Push(int value) {

    if (size_ == capacity_) {
      Resize(capacity_ + kCapacityGrowthCoefficient);
    }

    data_[size_] = value;
    size_++;
  }

  bool ArrayStack::Pop() {

    if (size_ == 0) {
      return false;
    }

    size_--;
    return true;
  }

  void ArrayStack::Clear() {

    size_ = 0;
  }

  std::optional<int> ArrayStack::Peek() const {

    if (size_ == 0) {
      return std::nullopt;
    }

    return data_[size_ - 1];
  }

  bool ArrayStack::IsEmpty() const {
    return size_ == 0;
  }

  int ArrayStack::size() const {
    return size_;
  }

  int ArrayStack::capacity() const {
    return capacity_;
  }

  bool ArrayStack::Resize(int new_capacity) {

    if (new_capacity <= capacity_) {
      return false;
    }

    int* new_data = new int[new_capacity];
    std::copy(data_, data_ + capacity_, new_data);
    delete[] data_;
    data_ = new_data;
    return true;
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