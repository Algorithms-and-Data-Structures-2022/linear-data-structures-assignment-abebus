#include "assignment/dynamic_array.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  DynamicArray::DynamicArray(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость массива
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }

    capacity_ = capacity;
    data_ = new int[capacity];
    std::fill(data_, data_ + capacity, 0);
  }

  DynamicArray::~DynamicArray() {

    delete[] data_;
    Clear();
    capacity_ = 0;
    data_ = nullptr;
  }

  void DynamicArray::Add(int value) {

    if (size_ == capacity_) {
      Resize(capacity_ + kCapacityGrowthCoefficient);
    }

    data_[size_] = value;
    size_++;
  }

  bool DynamicArray::Insert(int index, int value) {

    // index = 0    => вставка в начало массива
    // index = size => добавление в конец массива

    // проверка на выход за границы позиции вставки
    if (index < 0 or index > size_) {
      return false;
    }

    // расширяем емкость массива при заполнении
    if (size_ == capacity_) {
      Resize(capacity_ + kCapacityGrowthCoefficient);
    }

    // мы это сделали в ресайзе std::copy(data_ + index, data_ + size_, data_ + index + 1);
    data_[index] = value;
    size_++;
    return true;
  }

  bool DynamicArray::Set(int index, int new_value) {

    if (index < 0 or index >= size_) {
      return false;
    }
    data_[index] = new_value;
    return true;
  }

  std::optional<int> DynamicArray::Remove(int index) {

    if (index < 0 or index >= size_) {
      return std::nullopt;
    }

    const int removed_elem = data_[index];

    std::copy(data_ + index + 1, data_ + size_, data_ + index);
    size_--;
    return removed_elem;
  }

  void DynamicArray::Clear() {
    size_ = 0;
  }

  std::optional<int> DynamicArray::Get(int index) const {

    if (index < 0 or index >= size_) {
      return std::nullopt;
    }
    return data_[index];
  }

  std::optional<int> DynamicArray::IndexOf(int value) const {

    // линейный поиск элемента в массиве
    for (int index = 0; index < size_; index++) {

      if (data_[index] == value) {
        return index;
      }
    }

    return std::nullopt;
  }

  bool DynamicArray::Contains(int value) const {
    return IndexOf(value).has_value();
  }

  bool DynamicArray::IsEmpty() const {
    return size_ == 0;
  }

  int DynamicArray::size() const {
    return size_;
  }

  int DynamicArray::capacity() const {
    return capacity_;
  }

  bool DynamicArray::Resize(int new_capacity) {

    // "новая" емкость должна быть больше "текущей"
    if (new_capacity <= capacity_) {
      return false;
    }

    auto* new_data = new int[new_capacity];

    std::copy(data_, data_ + capacity_, new_data);

    delete[] data_;


    data_ = new_data;
    capacity_ = new_capacity;
    return true;
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