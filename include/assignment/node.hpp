#pragma once

namespace assignment {

  /**
   * Структура "узел".
   * Оболочка над значением и указателем на следующий узел.
   */
  struct Node {
    // поля структуры
    int value{0};         // значение узла
    Node* next{nullptr};  // указатель на следующий узел

    /**
     * Создание узла со значением и указателем на следующий узел.
     *
     * @param value - значение узла
     * @param next - указатель на следующий узел
     */
    explicit Node(int value, Node* next = nullptr);
  };

  /**
   * Структура "двусторонний узел".
   * Оболочка над значением, указателями на предыдущий и следующий узлы.
   */
  struct DoubleNode {
    // поля структуры
    int value{0};
    Node* prev{nullptr};  // указатель на предыдущий узел
    Node* next{nullptr};  // указатель на следующий узел

    /**
     * Создание узла со значением, указателями на предыдущий и следующий узлы.
     *
     * @param value - значение узла
     * @param prev - указатель на предыдущий узел
     * @param next - указатель на следующий узел
     */
    explicit DoubleNode(int value, Node* prev = nullptr, Node* next = nullptr);
  };

}  // namespace assignment