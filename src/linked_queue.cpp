#include "assignment/linked_queue.hpp"

namespace assignment {

  LinkedQueue::~LinkedQueue() {

    // эквивалентно очистке очереди
    LinkedQueue::Clear();
  }

  void LinkedQueue::Enqueue(int value) {
    // Write your code here ...
  }

  bool LinkedQueue::Dequeue() {
    // Write your code here ...
    return false;
  }

  void LinkedQueue::Clear() {
    // Write your code here ...
  }

  std::optional<int> LinkedQueue::front() const {
    // Write your code here ...
    return std::nullopt;
  }

  std::optional<int> LinkedQueue::back() const {
    // Write your code here ...
    return std::nullopt;
  }

  bool LinkedQueue::IsEmpty() const {
    return false;
  }

  int LinkedQueue::size() const {
    return 0;
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