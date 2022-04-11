#include "assignment/linked_queue.hpp"

namespace assignment {

  LinkedQueue::~LinkedQueue() {

    // эквивалентно очистке очереди
    LinkedQueue::Clear();
  }

  void LinkedQueue::Enqueue(int value) {

    // создаем "новый" узел
    auto* node = new Node(value);

    if (front_ == nullptr) {
      // очередь пустая, инициализируем начальный узел
      front_ = node;
    } else {
      // иначе, новый узел "ставим в очередь" за "конечным" узлом
      back_->next = node;
    }

    // обновляем конечный узел
    back_ = node;

    // увеличиваем размер очереди
    size_ += 1;
  }

  bool LinkedQueue::Dequeue() {

    // операция невозможна (пустая очередь)
    if (front_ == nullptr) {
      return false;
    }

    // указатель на "начальный" узел
    Node* remove_node = front_;

    //  начальный узел "выходит из очереди"
    front_ = front_->next;

    // высвобождаем память под вышедший из очереди узел
    delete remove_node;

    // если очередь пустая, то обнуляем указатель на конечный узел
    if (front_ == nullptr) {
      back_ = nullptr;
    }

    // уменьшаем размер очереди
    size_ -= 1;

    return true;
  }

  void LinkedQueue::Clear() {

    // проходимся по всем узлам очереди и высвобождаем память
    for (Node* node = front_; node != nullptr; /* ... */) {
      Node* remove_node = node;
      node = node->next;
      delete remove_node;
    }

    // обнуляем поля
    front_ = nullptr;
    back_ = nullptr;
    size_ = 0;
  }

  std::optional<int> LinkedQueue::front() const {

    // проверка наличия начального узла
    if (front_ == nullptr) {
      return std::nullopt;
    }

    return front_->value;
  }

  std::optional<int> LinkedQueue::back() const {

    // проверка наличия "конечного" узла
    if (back_ == nullptr) {
      return std::nullopt;
    }

    return back_->value;
  }

  bool LinkedQueue::IsEmpty() const {
    return front_ == nullptr;
  }

  int LinkedQueue::size() const {
    return size_;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedQueue::LinkedQueue(const std::vector<int>& values) {

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

  std::vector<int> LinkedQueue::toVector() const {
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