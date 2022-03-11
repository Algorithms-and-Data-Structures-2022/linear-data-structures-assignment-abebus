#include "assignment/dynamic_array.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  DynamicArray::DynamicArray(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость массива
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

  bool DynamicArray::Insert(int index, int value) {
    // Write your code here ...
    return false;
  }

  bool DynamicArray::Set(int index, int new_value) {
    // Write your code here ...
    return false;
  }

  std::optional<int> DynamicArray::Remove(int index) {
    // Write your code here ...
    return std::nullopt;
  }

  void DynamicArray::Clear() {
    // Write your code here ...
  }

  std::optional<int> DynamicArray::Get(int index) const {
    // Write your code here ...
    return std::nullopt;
  }

  std::optional<int> DynamicArray::IndexOf(int value) const {
    // Write your code here ...
    return std::nullopt;
  }

  bool DynamicArray::Contains(int value) const {
    return false;
  }

  bool DynamicArray::IsEmpty() const {
    return false;
  }

  int DynamicArray::size() const {
    return 0;
  }

  int DynamicArray::capacity() const {
    return 0;
  }

  bool DynamicArray::Resize(int new_capacity) {
    // Write your code here ...
    return false;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  DynamicArray::DynamicArray(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> DynamicArray::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment