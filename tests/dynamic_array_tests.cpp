#include <catch2/catch.hpp>

#include <cmath>  // min

#include "utils.hpp"  // rand_array

#include "assignment/dynamic_array.hpp"  // DynamicArray

using assignment::DynamicArray;

using Catch::Matchers::Contains;
using Catch::Matchers::Equals;
using Catch::Matchers::VectorContains;

SCENARIO("DynamicArray::DynamicArray") {

  WHEN("creating array using default constructor") {
    const auto array = DynamicArray();

    THEN("array should be empty") {
      CHECK(array.IsEmpty());
    }

    AND_THEN("array capacity should be equal to " << DynamicArray::kInitCapacity) {
      CHECK(array.capacity() == DynamicArray::kInitCapacity);
    }

    AND_THEN("array should be initialized with zeros") {
      const auto zeros = std::vector<int>(DynamicArray::kInitCapacity);
      CHECK_THAT(array.toVector(), Equals(zeros));
    }
  }

  AND_WHEN("creating array by specifying capacity > 0") {
    const auto capacity = GENERATE(range(1, 11));

    const auto array = DynamicArray(capacity);

    THEN("array should be empty") {
      CHECK(array.IsEmpty());
    }

    AND_THEN("array capacity should be equal to the specified value") {
      CHECK(array.capacity() == capacity);
    }

    AND_THEN("array should be initialized with zeros") {
      const auto zeros = std::vector<int>(capacity);
      CHECK_THAT(array.toVector(), Equals(zeros));
    }
  }

  AND_WHEN("creating array by specifying capacity <= 0") {
    const int capacity = GENERATE(range(-10, 1));

    THEN("constructor should throw an exception") {
      CHECK_THROWS(DynamicArray(capacity));
    }
  }
}

SCENARIO("DynamicArray::Get") {

  GIVEN("empty array") {
    const int capacity = GENERATE(range(1, 11));

    const auto array = DynamicArray(capacity);

    REQUIRE(array.IsEmpty());
    REQUIRE(array.capacity() == capacity);

    WHEN("getting an element at any index") {
      const int index = GENERATE_COPY(range(-10, capacity + 11));

      THEN("nothing should be returned") {
        CHECK_FALSE(array.Get(index).has_value());
      }
    }
  }

  AND_GIVEN("array with one or more elements") {
    const int capacity = GENERATE(range(1, 11));
    const int size = GENERATE_COPY(range(1, capacity + 1));

    const auto elems = utils::rand_array(size, 0, 100, true);

    const auto array = DynamicArray(elems, capacity);

    REQUIRE(array.size() == size);
    REQUIRE(array.capacity() == capacity);

    WHEN("getting an element at index in [0, size)") {
      const int index = GENERATE_COPY(range(0, size));

      THEN("element at the specified index should be returned") {
        const int elem_at_index = elems[index];
        CHECK(array.Get(index) == elem_at_index);
      }
    }

    AND_WHEN("getting an element at index outside [0, size)") {
      const auto pred = [size](int idx) { return idx < 0 || idx >= size; };
      const int index = GENERATE_REF(filter(pred, range(-10, size + 11)));

      THEN("nothing should be returned") {
        CHECK_FALSE(array.Get(index).has_value());
      }
    }
  }
}

SCENARIO("DynamicArray::Set") {

  GIVEN("empty array") {
    const int capacity = GENERATE(range(1, 6));

    auto array = DynamicArray(capacity);

    REQUIRE(array.IsEmpty());
    REQUIRE(array.capacity() == capacity);

    WHEN("setting an element at any index") {
      const int set_index = GENERATE_COPY(range(-5, capacity + 6));
      const int set_elem = GENERATE(take(5, random(0, 100)));

      REQUIRE_FALSE(array.Set(set_index, set_elem));

      THEN("array should be empty") {
        CHECK(array.IsEmpty());
      }

      AND_THEN("array capacity should not be changed") {
        CHECK(array.capacity() == capacity);
      }

      AND_THEN("array should be initialized with zeros") {
        const auto zeros = std::vector<int>(capacity);
        CHECK_THAT(array.toVector(), Equals(zeros));
      }
    }
  }

  AND_GIVEN("array with one or more elements") {
    const int capacity = GENERATE(range(1, 6));
    const int size = GENERATE_COPY(range(1, capacity + 1));

    const auto elems = utils::rand_array(size, 0, 100, true);

    auto array = DynamicArray(elems, capacity);

    REQUIRE(array.size() == size);
    REQUIRE(array.capacity() == capacity);

    WHEN("setting an element at index in [0, size)") {
      const int set_index = GENERATE_COPY(range(0, size));
      const int set_elem = GENERATE(take(5, random(0, 100)));

      REQUIRE(array.Set(set_index, set_elem));

      THEN("array size should not be changed") {
        const int size_before_set = size;
        CHECK(array.size() == size_before_set);
      }

      AND_THEN("array capacity should not be changed") {
        const int capacity_before_set = capacity;
        CHECK(array.capacity() == capacity_before_set);
      }

      AND_THEN("set should change an element at the specified index") {
        CHECK(array.Get(set_index) == set_elem);
      }
    }

    AND_WHEN("setting an element at index outside [0, size)") {
      const auto pred = [size](int idx) { return idx < 0 || idx >= size; };
      const int set_index = GENERATE_REF(filter(pred, range(-5, size + 6)));

      const int set_elem = GENERATE(take(5, random(0, 100)));

      REQUIRE_FALSE(array.Set(set_index, set_elem));

      THEN("array size should not be changed") {
        const int size_before_set = size;
        CHECK(array.size() == size_before_set);
      }

      AND_THEN("array capacity should not be changed") {
        const int capacity_before_set = capacity;
        CHECK(array.capacity() == capacity_before_set);
      }

      AND_THEN("array elements should be changed") {
        CHECK_THAT(array.toVector(size), Equals(elems));
      }
    }
  }
}

SCENARIO("DynamicArray::IndexOf") {

  GIVEN("array with one or more elements") {
    const int capacity = GENERATE(range(1, 11));
    const int size = GENERATE_COPY(range(1, capacity + 1));

    const auto elems = utils::rand_array(size, 0, 100);

    const auto array = DynamicArray(elems, capacity);

    REQUIRE(array.size() == size);
    REQUIRE(array.capacity() == capacity);

    WHEN("finding index of an existing element") {
      const int index = GENERATE_COPY(range(0, size));
      const int find_elem = elems[index];

      const int find_index = std::distance(elems.cbegin(), std::find(elems.cbegin(), elems.cend(), find_elem));

      THEN("correct index should be found") {
        CHECK(array.IndexOf(find_elem) == find_index);
      }
    }
  }
}

SCENARIO("DynamicArray::Contains") {

  GIVEN("array of one or more elements") {
    const int capacity = GENERATE(range(1, 11));
    const int size = GENERATE_COPY(range(1, capacity + 1));

    const auto elems = utils::rand_array(size, 0, 100);

    const auto array = DynamicArray(elems, capacity);

    REQUIRE(array.size() == size);
    REQUIRE(array.capacity() == capacity);

    WHEN("checking if it contains an existing element") {
      const int index = GENERATE_COPY(range(0, size));
      const int elem = elems[index];

      THEN("contains should return true") {
        CHECK(array.Contains(elem));
      }
    }
  }
}

SCENARIO("DynamicArray::Resize") {

  GIVEN("array with zero or more elements: size <= capacity") {
    const int capacity = GENERATE(range(1, 11));
    const int size = GENERATE_COPY(range(0, capacity + 1));

    const auto elems = utils::rand_array(size, 0, 100, true);

    auto array = DynamicArray(elems, capacity);

    REQUIRE(array.size() == size);
    REQUIRE(array.capacity() == capacity);

    WHEN("resizing to a new capacity <= previous capacity") {
      const int new_capacity = GENERATE_COPY(range(-10, capacity + 1));

      REQUIRE_FALSE(array.Resize(new_capacity));

      THEN("array size should not be changed") {
        const int size_before_resize = size;
        CHECK(array.size() == size_before_resize);
      }

      AND_THEN("array capacity should not be changed") {
        const int capacity_before_resize = capacity;
        CHECK(array.capacity() == capacity_before_resize);
      }

      AND_THEN("array elements should not be changed") {
        CHECK_THAT(array.toVector(size), Equals(elems));
      }
    }

    AND_WHEN("resizing to a new capacity > previous capacity") {
      const int new_capacity = GENERATE_COPY(range(capacity + 1, capacity + 6));

      REQUIRE(array.Resize(new_capacity));

      THEN("array size should not be changed") {
        const int size_before_resize = size;
        CHECK(array.size() == size_before_resize);
      }

      AND_THEN("array capacity should be increased") {
        CHECK(array.capacity() == new_capacity);
      }

      AND_THEN("array elements should not be changed") {
        CHECK_THAT(array.toVector(size), Equals(elems));
      }
    }
  }
}

SCENARIO("DynamicArray::Add") {

  GIVEN("array with zero or more elements: size < capacity") {
    const int capacity = GENERATE(range(1, 11));
    const int size = GENERATE_COPY(range(0, capacity));

    const auto elems = utils::rand_array(size, 0, 100, true);

    auto array = DynamicArray(elems, capacity);

    REQUIRE(array.size() == size);
    REQUIRE(array.capacity() == capacity);

    WHEN("adding an element") {
      const int add_elem = GENERATE(take(10, random(0, 100)));

      array.Add(add_elem);

      THEN("array size should be increased") {
        const int size_after_add = size + 1;
        CHECK(array.size() == size_after_add);
      }

      AND_THEN("array capacity should not be changed") {
        const int capacity_before_add = capacity;
        CHECK(array.capacity() == capacity_before_add);
      }

      AND_THEN("back should be equal to the added element") {
        const int add_elem_index = size;
        CHECK(array.Get(add_elem_index) == add_elem);
      }

      AND_THEN("previous elements should be present") {
        CHECK_THAT(array.toVector(size), Contains(elems));
      }
    }
  }

  AND_GIVEN("array full of elements: size = capacity") {
    const int capacity = GENERATE(range(1, 11));
    const auto elems = utils::rand_array(capacity, 0, 100, true);

    auto array = DynamicArray(elems, capacity);

    REQUIRE(array.size() == capacity);
    REQUIRE(array.capacity() == capacity);

    WHEN("adding an element") {
      const int add_elem = GENERATE(take(10, random(0, 100)));

      array.Add(add_elem);

      THEN("array size should be increased") {
        const int size_after_add = capacity + 1;
        CHECK(array.size() == size_after_add);
      }

      AND_THEN("array capacity should be increased to the factor of " << DynamicArray::kCapacityGrowthCoefficient) {
        const int capacity_after_add = capacity + DynamicArray::kCapacityGrowthCoefficient;
        CHECK(array.capacity() == capacity_after_add);
      }

      AND_THEN("back should be equal to the added element") {
        const int add_elem_index = capacity;
        CHECK(array.Get(add_elem_index) == add_elem);
      }

      AND_THEN("previous elements should be present") {
        CHECK_THAT(array.toVector(capacity), Contains(elems));
      }
    }
  }
}

SCENARIO("DynamicArray::Insert") {

  GIVEN("array with zero or more elements: size < capacity") {
    const int capacity = GENERATE(range(1, 6));
    const int size = GENERATE_COPY(range(0, capacity));

    const auto elems = utils::rand_array(size, 0, 100, true);

    auto array = DynamicArray(elems, capacity);

    REQUIRE(array.size() == size);
    REQUIRE(array.capacity() == capacity);

    WHEN("inserting an element at index in [0, size]") {
      const int insert_index = GENERATE_COPY(range(0, size + 1));
      const int insert_elem = GENERATE(take(5, random(0, 100)));

      CAPTURE(array.toVector(capacity), elems, insert_elem);

      REQUIRE(array.Insert(insert_index, insert_elem));

      THEN("array size should be increased") {
        const int size_after_insert = size + 1;
        CHECK(array.size() == size_after_insert);
      }

      AND_THEN("array capacity should not be changed") {
        const int capacity_before_insert = capacity;
        CHECK(array.capacity() == capacity_before_insert);
      }

      AND_THEN("inserted element should be at the specified index") {
        CHECK(array.Get(insert_index) == insert_elem);
      }

      AND_THEN("previous elements should be present") {
        CHECK_THAT(array.toVector(capacity), Contains(elems));
      }
    }

    AND_WHEN("inserting an element at index outside [0, size]") {
      const auto pred = [size](int idx) { return idx < 0 || idx >= size + 1; };
      const int insert_index = GENERATE_COPY(filter(pred, range(-10, size + 11)));

      const int insert_elem = GENERATE(take(5, random(0, 100)));

      REQUIRE_FALSE(array.Insert(insert_index, insert_elem));

      THEN("array size should not be changed") {
        const int size_before_insert = size;
        CHECK(array.size() == size_before_insert);
      }

      AND_THEN("array capacity should not be changed") {
        const int capacity_before_insert = capacity;
        CHECK(array.capacity() == capacity_before_insert);
      }

      AND_THEN("array elements should not be changed") {
        CHECK_THAT(array.toVector(size), Equals(elems));
      }
    }
  }

  AND_GIVEN("array full of elements: size = capacity") {
    const int capacity = GENERATE(range(1, 6));
    const auto elems = utils::rand_array(capacity, 0, 100, true);

    auto array = DynamicArray(elems, capacity);

    REQUIRE(array.size() == capacity);
    REQUIRE(array.capacity() == capacity);

    WHEN("inserting an element at index in [0, size]") {
      const int insert_index = GENERATE_COPY(range(0, capacity + 1));
      const int insert_elem = GENERATE(take(5, random(0, 100)));

      REQUIRE(array.Insert(insert_index, insert_elem));

      THEN("array size should be increased") {
        const int size_after_insert = capacity + 1;
        CHECK(array.size() == size_after_insert);
      }

      AND_THEN("array capacity should be increased to the factor of " << DynamicArray::kCapacityGrowthCoefficient) {
        const int capacity_after_insert = capacity + DynamicArray::kCapacityGrowthCoefficient;
        CHECK(array.capacity() == capacity_after_insert);
      }

      AND_THEN("inserted element should be at the specified index") {
        CHECK(array.Get(insert_index) == insert_elem);
      }

      AND_THEN("previous elements should be present") {
        const int size_after_insert = capacity + 1;
        CHECK_THAT(array.toVector(size_after_insert), Contains(elems));
      }
    }

    AND_WHEN("inserting an element at index outside [0, size]") {
      const auto pred = [capacity](int idx) { return idx < 0 || idx >= capacity + 1; };
      const int insert_index = GENERATE_REF(filter(pred, range(-5, capacity + 6)));

      const int insert_elem = GENERATE(take(5, random(0, 100)));

      REQUIRE_FALSE(array.Insert(insert_index, insert_elem));

      THEN("array size should not be changed") {
        const int size_before_insert = capacity;
        CHECK(array.size() == size_before_insert);
      }

      AND_THEN("array capacity should not be changed") {
        const int capacity_before_insert = capacity;
        CHECK(array.capacity() == capacity_before_insert);
      }

      AND_THEN("array elements should not be changed") {
        CHECK_THAT(array.toVector(capacity), Equals(elems));
      }
    }
  }
}

SCENARIO("DynamicArray::Remove") {

  GIVEN("empty array") {
    const int capacity = GENERATE(range(1, 11));

    auto array = DynamicArray(capacity);

    REQUIRE(array.IsEmpty());
    REQUIRE(array.capacity() == capacity);

    WHEN("removing an element at any index") {
      const int remove_index = GENERATE_COPY(range(-10, capacity + 11));

      REQUIRE_FALSE(array.Remove(remove_index).has_value());

      THEN("array size should not be changed") {
        const int size_before_remove = 0;
        CHECK(array.size() == size_before_remove);
      }

      AND_THEN("array capacity should not be changed") {
        const int capacity_before_remove = capacity;
        CHECK(array.capacity() == capacity_before_remove);
      }

      AND_THEN("array elements should be zeros") {
        const auto zeros = std::vector<int>(capacity);
        CHECK_THAT(array.toVector(), Equals(zeros));
      }
    }
  }

  AND_GIVEN("array with one or more elements") {
    const int capacity = GENERATE(range(1, 11));
    const int size = GENERATE_COPY(range(1, capacity + 1));

    const auto elems = utils::rand_array(size, 0, 100, true);

    auto array = DynamicArray(elems, capacity);

    REQUIRE(array.size() == size);
    REQUIRE(array.capacity() == capacity);

    WHEN("removing an element at index in [0, size)") {
      const int remove_index = GENERATE_REF(range(0, size));
      const auto remove_elem = elems[remove_index];

      const auto removed = array.Remove(remove_index);

      THEN("array size should be decreased") {
        const int size_after_remove = size - 1;
        CHECK(array.size() == size_after_remove);
      }

      AND_THEN("array capacity should not be changed") {
        const int capacity_before_remove = capacity;
        CHECK(array.capacity() == capacity_before_remove);
      }

      AND_THEN("removed element should have correct value") {
        CHECK(removed == remove_elem);
      }

      AND_THEN("array should not contain the removed element") {
        const int size_after_remove = size - 1;
        CHECK_THAT(array.toVector(size_after_remove), !VectorContains(remove_elem));
      }
    }

    AND_WHEN("removing an element at index outside [0, size)") {
      const auto pred = [size](int idx) { return idx < 0 || idx >= size; };
      const int remove_index = GENERATE_REF(filter(pred, range(-10, capacity + 11)));

      CHECK_FALSE(array.Remove(remove_index).has_value());

      AND_THEN("array size should not be changed") {
        const int size_before_remove = size;
        CHECK(array.size() == size_before_remove);
      }

      AND_THEN("array capacity should not be changed") {
        const int capacity_before_remove = capacity;
        CHECK(array.capacity() == capacity_before_remove);
      }

      AND_THEN("array elements should not be changed") {
        CHECK_THAT(array.toVector(size), Equals(elems));
      }
    }
  }
}

SCENARIO("DynamicArray::Clear") {

  GIVEN("array with zero or more elements") {
    const int capacity = GENERATE(range(1, 11));
    const int size = GENERATE_REF(range(0, capacity + 1));

    const auto elems = utils::rand_array(size, 0, 100, true);

    auto array = DynamicArray(elems, capacity);

    REQUIRE(array.size() == size);
    REQUIRE(array.capacity() == capacity);

    WHEN("clearing the array") {
      array.Clear();

      THEN("array should be empty") {
        CHECK(array.IsEmpty());
      }

      AND_THEN("array capacity should not be changed") {
        const int capacity_before_clear = capacity;
        CHECK(array.capacity() == capacity_before_clear);
      }
    }
  }
}
