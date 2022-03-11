#pragma once

#include <sstream>    // stringstream
#include <stdexcept>  // out_of_range

namespace assignment::internal {

  /**
   * Проверка вхождения индекса в полуинтервал [min, max).
   *
   * @param index - значение индекса
   * @param min - нижняя граница (включительно)
   * @param max - верхняя граница (не включительно)
   * @throws out_of_range при выходе индекса за границы полуинтервала
   */
  inline void check_out_of_range(int index, int min, int max) {
    if (index < min || index >= max) {
      std::stringstream ss("index is out of range: ");
      ss << '[' << min << ',' << max << ')';

      throw std::out_of_range(ss.str());
    }
  }

}  // namespace classwork::internal