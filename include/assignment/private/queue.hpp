#pragma once

#include <optional>

namespace assignment {

  /**
   * Интерфейс "очередь".
   * "Первый вошел, первый вышел" - FIFO.
   */
  struct Queue {
    /**
     * Деструктор.
     *
     * Высвобождает выделенную память.
     * Поведение зависит от конкретной реализации списка.
     */
    virtual ~Queue() = default;

    /**
     * Добавление элемента в конец очереди.
     *
     * @param value - значение добавляемого элемента
     */
    virtual void Enqueue(int value) = 0;

    /**
     * Удаление элемента из начала очереди.
     *
     * @return true - операция успешна, false - операция невозможна (очередь пустая)
     */
    virtual bool Dequeue() = 0;

    /**
     * Очистка очереди.
     *
     * Поведение зависит от конкретной реализации очереди.
     */
    virtual void Clear() = 0;

    /**
     * Возвращает элемент в начале очереди.
     *
     * @return значение элемента или ничего (пустая очередь)
     */
    virtual std::optional<int> front() const = 0;

    /**
     * Возвращает элемент в конце очереди.
     *
     * @return значение элемента или ничего (пустая очередь)
     */
    virtual std::optional<int> back() const = 0;

    /**
     * Проверка пустоты очереди.
     *
     * @return true - очередь пустая, false - в очереди есть элементы
     */
    virtual bool IsEmpty() const = 0;

    /**
     * Возвращает размер очереди.
     *
     * @return количество элементов в очереди
     */
    virtual int size() const = 0;
  };

}  // namespace assignment