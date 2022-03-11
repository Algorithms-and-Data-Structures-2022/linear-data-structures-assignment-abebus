#pragma once

#include <optional>

namespace assignment {

  /**
   * Интерфейс "стек".
   * "Последний зашел, первый вышел" - LIFO.
   */
  struct Stack {
   public:
    /**
     * Деструктор.
     *
     * Высвобождает выделенную память.
     * Поведение зависит от конкретной реализации стека.
     */
    virtual ~Stack() = default;

    /**
     * Добавление элемента на вершину стека.
     *
     * @param value - значение добавляемого элемента
     */
    virtual void Push(int value) = 0;

    /**
     * Удаление элемента с вершины стека.
     *
     * @return true - операция успешна, false - операция невозможна (стек пустой)
     */
    virtual bool Pop() = 0;

    /**
     * Очистка стека.
     *
     * Поведение зависит от конкретной реализации стека.
     */
    virtual void Clear() = 0;

    /**
     * Получение элемента с вершины стека.
     *
     * @return значение элемента или ничего в случае пустого стека
     */
    virtual std::optional<int> Peek() const = 0;

    /**
     * Проверка пустоты стека.
     *
     * @return true - стек пустой, false - в стеке есть элементы
     */
    virtual bool IsEmpty() const = 0;

    /**
     * Возвращает размер стека.
     *
     * @return количество элементов в стеке
     */
    virtual int size() const = 0;
  };

}  // namespace classwork