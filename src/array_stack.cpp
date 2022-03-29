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
    capacity_ = capacity;
    size_ = 0;
    data_ = new int[capacity_];
    for (int i=0; i < capacity_; i++){
      data_[i] = 0;
    }
  }

  ArrayStack::~ArrayStack() {
    // Write your code here ...
    capacity_ = 0;
    Clear();
  }

  void ArrayStack::Push(int value) {
    // Write your code here ...
    size_ ++;
    if (size_ > capacity_){
      Resize(capacity_ + kCapacityGrowthCoefficient);
    }
    data_[size_] = value;
  }

  bool ArrayStack::Pop() {
    // Write your code here ...
    if (IsEmpty()){
      return false;
    }
    data_[size_] = 0;
    size_ --;
    return true;
  }

  void ArrayStack::Clear() {
    // Write your code here ...
      delete data_;
      data_ = nullptr;
      size_ = 0;
  }

  std::optional<int> ArrayStack::Peek() const {
    // Write your code here ...
    if (IsEmpty()) {
      return std::nullopt;
    }
    return data_[size_];
  }

  bool ArrayStack::IsEmpty() const {
    // Write your code here ...
    return size_ == 0;
  }

  int ArrayStack::size() const {
    // Write your code here ...
    return size_;
  }

  int ArrayStack::capacity() const {
    // Write your code here ...
    return capacity_;
  }

  bool ArrayStack::Resize(int new_capacity) {
    // Write your code here ...
    if (new_capacity <= capacity_){
      return false;
    }
    int* new_data = new int[new_capacity];
    for (int i=0; i < capacity_; i++){
      new_data[i] = data_[i];
    }
    for (int i = capacity_; i < new_capacity; i++){
      new_data[i] = 0;
    }
    capacity_ = new_capacity;
    Clear();
    data_ = new_data;
    delete new_data;
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
