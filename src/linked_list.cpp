#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    // Write your code here ...
  }

  bool LinkedList::Insert(int index, int value) {
    // Write your code here ...
    return false;
  }

  bool LinkedList::Set(int index, int new_value) {
    return false;
  }

  std::optional<int> LinkedList::Remove(int index) {
    // Write your code here ...
    return std::nullopt;
  }

  void LinkedList::Clear() {
    // Write your code here ...
  }

  std::optional<int> LinkedList::Get(int index) const {
    // Write your code here ...
    return std::nullopt;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    // Write your code here ...
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    return false;
  }

  bool LinkedList::IsEmpty() const {
    return false;
  }

  int LinkedList::size() const {
    return 0;
  }

  std::optional<int> LinkedList::front() const {
    // Write your code here ...
    return std::nullopt;
  }

  std::optional<int> LinkedList::back() const {
    // Write your code here ...
    return std::nullopt;
  }

  Node* LinkedList::FindNode(int index) const {
    // Write your code here ...
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