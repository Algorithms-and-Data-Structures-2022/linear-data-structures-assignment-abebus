#include "assignment/array_stack.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  ArrayStack::ArrayStack(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость стека
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }

    // устанавливаем емкость стека
    capacity_ = capacity;

    // выделяем участок памяти под стек
    data_ = new int[capacity];

    // инициализируем элементы стека нулевым значением
    std::fill(data_, data_ + capacity, 0);
  }

  ArrayStack::~ArrayStack() {

    // высвобождаем выделенную память
    delete[] data_;

    // обнуляем поля
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
  }

  void ArrayStack::Push(int value) {

    // расширяем емкость стека при заполнении
    if (size_ == capacity_) {
      Resize(capacity_ + kCapacityGrowthCoefficient);
    }

    // добавляем элемент на вершину стека (конец массива)
    data_[size_] = value;

    // увеличиваем размер стека
    size_ += 1;
  }

  bool ArrayStack::Pop() {

    // операция невозможна (пустой стек)
    if (size_ == 0) {
      return false;
    }

    // спускаем вершину стека
    size_ -= 1;

    return true;
  }

  void ArrayStack::Clear() {

    // обнуляем вершину стека
    size_ = 0;
  }

  std::optional<int> ArrayStack::Peek() const {

    // стек пустой
    if (size_ == 0) {
      return std::nullopt;
    }

    // возвращаем элемент на вершине стека
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

    // "новая" емкость должна быть больше "текущей"
    if (new_capacity <= capacity_) {
      return false;
    }

    // выделяем "новый" блок памяти большего размера
    int* new_data = new int[new_capacity];

    // копируем данные из "текущего" блока памяти в "новый"
    std::copy(data_, data_ + capacity_, new_data);

    // высвобождаем "текущий" блок памяти
    delete[] data_;

    // сохраняем адрес на "новый" блок памяти
    data_ = new_data;

    // устанавливаем "новую" емкость стека
    capacity_ = new_capacity;

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
