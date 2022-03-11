#pragma once

#include "assignment//private/stack.hpp"  // Stack

namespace assignment {

  /**
   * Структура данных "стек" на базе "массива переменной длины".
   */
  struct ArrayStack : Stack {
   private:
    // поля структуры
    int size_{0};         // кол-во элементов в стеке
    int capacity_{0};     // емкость стека (кол-во ячеек в стеке)
    int* data_{nullptr};  // указатель на выделенный блок памяти

   public:
    // константы структуры
    static constexpr int kInitCapacity = 10;              // начальная емкость стека
    static constexpr int kCapacityGrowthCoefficient = 5;  // коэффициент увеличения размера стека

    /**
     * Создание стека с указанной емкостью ~ O(n).
     *
     * Выделенные ячейки стека инициализируются нулевым значением.
     *
     * @param capacity - начальная емкость стека (опционально)
     * @throws invalid_argument при указании неположительной емкости стека
     */
    explicit ArrayStack(int capacity = kInitCapacity);

    /**
     * Деструктор ~ O(1).
     *
     * Высвобождает выделенную под стек память.
     * Устанавливает поля в нулевые значения.
     */
    ~ArrayStack() override;

    /**
     * Добавление элемента на вершину стека ~ O(1) или O(n).
     *
     * При недостаточной емкости стек расширяется с сохранением элементов.
     *
     * @param value - значение добавляемого элемента
     */
    void Push(int value) override;

    /**
     * Удаление элемента с вершины стека ~ O(1).
     *
     * @return true - операция успешна, false - операция невозможна (стек пустой)
     */
    bool Pop() override;

    /**
     * Очистка стека ~ O(1).
     *
     * Обнуляет размер массива.
     */
    void Clear() override;

    /**
     * Получение элемента с вершины стека ~ O(1).
     *
     * @return значение элемента или ничего в случае пустого стека
     */
    std::optional<int> Peek() const override;

    /**
     * Проверка пустоты стека.
     *
     * @return true - стек пустой, false - в стеке есть элементы
     */
    bool IsEmpty() const override;

    /**
     * Возвращает размер стека.
     *
     * @return количество элементов в стеке
     */
    int size() const override;

    /**
     * Возвращает емкость стека.
     *
     * @return количество выделенных ячеек стека
     */
    int capacity() const;

    /**
     * Увеличение емкости стека ~ O(n).
     *
     * @param new_capacity - новая емкость стека
     * @throws invalid_argument при указании емкости не больше предыдущей
     */
    void Resize(int new_capacity);
  };

}  // namespace classwork