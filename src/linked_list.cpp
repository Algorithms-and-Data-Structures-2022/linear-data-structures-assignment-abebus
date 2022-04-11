#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {

    // создаем "новый" узел
    auto* node = new Node(value);

    if (front_ == nullptr) {
      // если список пустой, то инициализируем "начальный" узел
      front_ = node;
    } else {
      // иначе, добавляем "новый" узел после "конечного"
      back_->next = node;
    }

    // обновляем "конечный" узел
    back_ = node;

    // увеличиваем размер списка
    size_ += 1;
  }

  bool LinkedList::Insert(int index, int value) {

    // index = 0    => вставка в начало списка
    // index = size => вставка в конец списка

    // проверка на выход за границы позиции вставки
    if (index < 0 || index > size_) {
      return false;
    }

    auto* node = new Node(value);

    if (front_ == nullptr) {
      // пустой список: "начальный" и "конечный" узлы одинаковы
      front_ = node;
      back_ = node;

    } else {
      // вставка в "начало" списка
      if (index == 0) {
        node->next = front_;
        front_ = node;

      } else if (index == size_) {
        // вставка в "конец" списка
        back_->next = node;
        back_ = node;

      } else {
        // вставка "внутрь" списка
        auto* prev_node = FindNode(index - 1);

        node->next = prev_node->next;
        prev_node->next = node;
      }
    }

    size_ += 1;

    return true;
  }

  bool LinkedList::Set(int index, int new_value) {

    auto* node = FindNode(index);

    if (node == nullptr) {
      return false;
    }

    node->value = new_value;

    return true;
  }

  std::optional<int> LinkedList::Remove(int index) {

    // проверка на выход за пределы списка
    if (index < 0 || index >= size_) {
      return std::nullopt;
    }

    // удаление из "начала" списка
    if (index == 0) {
      auto* remove_node = front_;
      const int remove_value = remove_node->value;

      // сдвигаем "начало" списка на следующий узел
      front_ = front_->next;

      // высвобождаем выделенную под удаляемый узел память
      delete remove_node;

      // уменьшаем размер списка
      size_ -= 1;

      return remove_value;
    }

    // удаление из любой другой позиции

    auto* prev_node = FindNode(index - 1);

    // находим удаляемый узел и его значение
    auto* removed_node = prev_node->next;
    const int removed_value = removed_node->value;

    // предыдущий узел "указываем" на следующий после удаляемого узла
    prev_node->next = removed_node->next;

    // высвобождаем выделенную под удаляемый узел память
    delete removed_node;

    // уменьшаем размер списка
    size_ -= 1;

    return removed_value;
  }

  void LinkedList::Clear() {

    // проходимся от "начала" до "конца" списка
    for (auto* curr_node = front_; curr_node != nullptr; /* ... */) {
      // сохраняем адрес удаляемого узла
      auto* remove_node = curr_node;

      // переходим на следующий узел
      curr_node = curr_node->next;

      // высвобождаем память под предыдущий узел
      delete remove_node;
    }

    // обнуляем поля
    size_ = 0;
    front_ = nullptr;
    back_ = nullptr;
  }

  std::optional<int> LinkedList::Get(int index) const {

    // поиск узла по индексу
    auto* node = FindNode(index);

    if (node == nullptr) {
      return std::nullopt;
    }

    return node->value;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {

    // отслеживаем текущий индекс и проходимся по всем узлам списка
    int curr_index = 0;

    for (auto* curr_node = front_; curr_node != nullptr; curr_node = curr_node->next) {
      if (curr_node->value == value) {
        return curr_index;
      }

      curr_index += 1;
    }

    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    return IndexOf(value).has_value();
  }

  bool LinkedList::IsEmpty() const {
    return size_ == 0;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {

    // проверка на наличие узла
    if (front_ == nullptr) {
      return std::nullopt;
    }

    return front_->value;
  }

  std::optional<int> LinkedList::back() const {

    // проверка на наличие узла
    if (back_ == nullptr) {
      return std::nullopt;
    }

    return back_->value;
  }

  Node* LinkedList::FindNode(int index) const {

    // проверка на выход за границы списка
    if (index < 0 || index >= size_) {
      return nullptr;
    }

    // возвращаем "конец" списка
    if (index == size_ - 1) {
      return back_;
    }

    // отслеживаем текущий индекс и проходимся по всем узлам списка
    int curr_idx = 0;

    for (auto* node = front_; node != nullptr; node = node->next) {
      if (curr_idx == index) {
        return node;
      }

      curr_idx += 1;
    }

    return nullptr;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment