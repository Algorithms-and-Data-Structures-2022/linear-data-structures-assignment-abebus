#pragma once

#include <vector>  // НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ

#include "assignment/node.hpp"          // Node
#include "assignment/private/list.hpp"  // List

namespace assignment {

  /**
   * Структура данных "связный список".
   * Хранит в себе элементы в виде последовательности "узлов".
   */
  struct LinkedList : List {
   private:
    // поля структуры
    int size_{0};           // кол-вод узлов в списке
    Node* front_{nullptr};  // указатель на начальный узел
    Node* back_{nullptr};   // указатель на конечный узел

   public:
    /**
     * Создание пустого связного списка ~ O(1).
     *
     * Инициализирует поля нулевыми значениями.
     */
    LinkedList() = default;

    /**
     * Деструктор ~ O(n).
     *
     * Высвобождает выделенную память.
     * Устанавливает поля в нулевые значения.
     */
    ~LinkedList() override;

    /**
     * Добавление элемента в конец списка ~ O(1).
     *
     * @param value - значение добавляемого элемента
     */
    void Add(int value) override;

    /**
     * Вставка элемента в список по индексу ~ O(n).
     * Вставка в начало или конец списка ~ O(1).
     *
     * @param index - позиция для вставки элемента в список
     * @param value - значение вставляемого элемента
     * @return true - операция прошла успешно, false - индекс за пределами списка
     */
    bool Insert(int index, int value) override;

    /**
     * Изменение значения элемента списка по индексу ~ O(n).
     *
     * @param index - позиция изменяемого элемента списка
     * @param new_value - новое значение элемента
     * @return true - операция прошла успешно, false - индекс за пределами списка
     */
    bool Set(int index, int new_value) override;

    /**
     * Удаление элемента из списка по индексу ~ O(n).
     * Удаление элемента с начала списка ~ O(1).
     *
     * @param index - позиция удаляемого элемента в списке
     * @return значение удаленного элемента или ничего (индекс за пределами списка)
     */
    std::optional<int> Remove(int index) override;

    /**
     * Очистка списка ~ O(n).
     *
     * Высвобождение выделенной под узлы памяти.
     * Обнуление полей списка.
     */
    void Clear() override;

    /**
     * Получение значения элемента списка по индексу ~ O(n).
     *
     * @param index - позиция элемента в списке
     * @return значение найденного элемента или ничего (индекс за пределами списка)
     */
    std::optional<int> Get(int index) const override;

    /**
     * Поиск индекса первого вхождения узла с указанным значением ~ O(n).
     *
     * @param value - значение элемента
     * @return индекс найденного элемента или ничего (в случае отсутствия элемента)
     */
    std::optional<int> IndexOf(int value) const override;

    /**
     * Проверка наличия элемента в списке по значению ~ O(n).
     *
     * @param value - значение элемента
     * @return true - при наличии узла в списке, false - при отсутствии элемента
     */
    bool Contains(int value) const override;

    /**
     * Проверка пустоты списка ~ O(1).
     *
     * @return true - если список пустой, false - в списке есть элементы
     */
    bool IsEmpty() const override;

    /**
     * Возвращает размер списка ~ O(1).
     *
     * @return количество элементов в списке
     */
    int size() const override;

    /**
     * Возвращает начальный элемент списка ~ O(1).
     *
     * @return значение начального узла или ничего (индекс за пределами списка)
     */
    std::optional<int> front() const;

    /**
     * Возвращает конечный элемент списка ~ O(1).
     *
     * @return значение конечного узла или ничего (индекс за пределами списка)
     */
    std::optional<int> back() const;

    /**
     * Поиск узла по индексу ~ O(n).
     *
     * Используется для операций над списком, выполняемых по индексу.
     *
     * @param index - позиция узла в списке
     * @return указатель на найденный узел или nullptr (индекс за пределами списка)
     */
    Node* FindNode(int index) const;

    // ДЛЯ ТЕСТИРОВАНИЯ
    explicit LinkedList(const std::vector<int>& values);

    std::vector<int> toVector() const;
  };

}  // namespace assignment