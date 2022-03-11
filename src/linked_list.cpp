#include "assignment/linked_list.hpp"

#include "assignment/private/private.hpp"  // check_out_of_range

namespace assignment {

  LinkedList::~LinkedList() {
    Clear();
  }

  void LinkedList::Add(int value) {
    // Write your code here ...
  }

  void LinkedList::Insert(int index, int value) {
    internal::check_out_of_range(index, 0, size_);
    // Write your code here ...
  }

  void LinkedList::Set(int index, int new_value) {
    internal::check_out_of_range(index, 0, size_);
    // Write your code here ...
  }

  int LinkedList::Remove(int index) {
    internal::check_out_of_range(index, 0, size_);
    // Write your code here ...
    return 0;
  }

  void LinkedList::Clear() {
    // Write your code here ...
  }

  int LinkedList::Get(int index) const {
    internal::check_out_of_range(index, 0, size_);
    // Write your code here ...
    return 0;
  }

  int LinkedList::IndexOf(int value) const {
    // Write your code here ...
    return 0;
  }

  bool LinkedList::Contains(int value) const {
    // Write your code here ...
    return false;
  }

  bool LinkedList::IsEmpty() const {
    // Write your code here ...
    return false;
  }

  int LinkedList::size() const {
    // Write your code here ...
    return 0;
  }

  int LinkedList::head() const {
    // Write your code here ...
    return 0;
  }

  int LinkedList::tail() const {
    // Write your code here ...
    return 0;
  }

  Node* LinkedList::FindNode(int index) const {
    // Write your code here ...
    return nullptr;
  }

}  // namespace classwork