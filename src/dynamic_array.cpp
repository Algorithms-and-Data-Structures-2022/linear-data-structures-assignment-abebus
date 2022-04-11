#include "assignment/dynamic_array.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  DynamicArray::DynamicArray(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость массива
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }

    // устанавливаем емкость массива
    capacity_ = capacity;

    // выделяем участок памяти под массив
    data_ = new int[capacity];

    // инициализируем элементы массива нулевым значением
    std::fill(data_, data_ + capacity, 0);
  }

  DynamicArray::~DynamicArray() {

    // высвобождаем выделенную память
    delete[] data_;

    // обнуляем поля
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
  }

  void DynamicArray::Add(int value) {

    // расширяем емкость массива при заполнении
    if (size_ == capacity_) {
      Resize(capacity_ + kCapacityGrowthCoefficient);
    }

    // добавляем элемент в конец массива
    data_[size_] = value;

    // увеличиваем размер массива
    size_ += 1;
  }

  bool DynamicArray::Insert(int index, int value) {

    // index = 0    => вставка в начало массива
    // index = size => добавление в конец массива

    // проверка на выход за границы позиции вставки
    if (index < 0 || index > size_) {
      return false;
    }

    // расширяем емкость массива при заполнении
    if (size_ == capacity_) {
      Resize(capacity_ + kCapacityGrowthCoefficient);
    }

    // сдвигаем все элементы правее позиции вставки на 1 вправо
    std::copy(data_ + index, data_ + size_, data_ + index + 1);

    // вставляем элемент по индексу
    data_[index] = value;

    // увеличиваем размер массива
    size_ += 1;

    return true;
  }

  bool DynamicArray::Set(int index, int new_value) {

    // проверка на выход за пределы массива
    if (index < 0 || index >= size_) {
      return false;
    }

    // устанавливаем значение элемента по индексу
    data_[index] = new_value;

    return true;
  }

  std::optional<int> DynamicArray::Remove(int index) {

    // проверка на выход за пределы массива
    if (index < 0 || index >= size_) {
      return std::nullopt;
    }

    // сохраняем значение удаляемого элемента
    const int removed_elem = data_[index];

    // сдвигаем все элементы справа от позиции удаляемого элемента на 1 ячейку влево
    std::copy(data_ + index + 1, data_ + size_, data_ + index);

    // уменьшаем размер массива
    size_ -= 1;

    // возвращаем значение удаленного элемента
    return removed_elem;
  }

  void DynamicArray::Clear() {

    // обнуляем размер массива
    size_ = 0;
  }

  std::optional<int> DynamicArray::Get(int index) const {

    // проверка на выход за пределы массива
    if (index < 0 || index >= size_) {
      return std::nullopt;
    }

    // возвращаем значение элемента по индексу
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

    // выделяем "новый" блок памяти большего размера
    auto* new_data = new int[new_capacity];

    // копируем данные из "текущего" блока памяти в "новый"
    std::copy(data_, data_ + capacity_, new_data);

    // высвобождаем "текущий" блок памяти
    delete[] data_;

    // сохраняем адрес на "новый" блок памяти
    data_ = new_data;

    // устанавливаем "новую" емкость массива
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