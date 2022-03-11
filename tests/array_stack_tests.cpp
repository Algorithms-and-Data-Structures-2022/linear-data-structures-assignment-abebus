#include <catch2/catch.hpp>

#include "utils.hpp"  // rand_array

#include "assignment/array_stack.hpp"  // ArrayStack

using assignment::ArrayStack;

using Catch::Matchers::Contains;
using Catch::Matchers::Equals;
using Catch::Matchers::VectorContains;

SCENARIO("ArrayStack::ArrayStack") {

  WHEN("creating stack using default constructor") {
    const auto stack = ArrayStack();

    THEN("stack should be empty") {
      CHECK(stack.IsEmpty());
    }

    AND_THEN("stack capacity should be equal to " << ArrayStack::kInitCapacity) {
      CHECK(stack.capacity() == ArrayStack::kInitCapacity);
    }

    AND_THEN("stack should be initialized with zeros") {
      const auto zeros = std::vector<int>(ArrayStack::kInitCapacity);
      CHECK_THAT(stack.toVector(), Equals(zeros));
    }
  }

  AND_WHEN("creating stack by specifying capacity > 0") {
    const int capacity = GENERATE(range(1, 11));

    const auto stack = ArrayStack(capacity);

    THEN("stack should be empty") {
      CHECK(stack.IsEmpty());
    }

    AND_THEN("stack capacity should be equal to the specified value") {
      CHECK(stack.capacity() == capacity);
    }

    AND_THEN("stack should be initialized with zeros") {
      const auto zeros = std::vector<int>(capacity);
      CHECK_THAT(stack.toVector(), Equals(zeros));
    }
  }

  AND_WHEN("creating stack by specifying capacity <= 0") {
    const int capacity = GENERATE(range(-10, 1));

    THEN("constructor should throw an exception") {
      CHECK_THROWS(ArrayStack(capacity));
    }
  }
}

SCENARIO("ArrayStack::Peek") {

  GIVEN("empty stack") {
    const int capacity = GENERATE(range(1, 11));

    const auto stack = ArrayStack(capacity);

    REQUIRE(stack.IsEmpty());
    REQUIRE(stack.capacity() == capacity);

    WHEN("peeking an element") {

      THEN("nothing should be returned") {
        CHECK_FALSE(stack.Peek().has_value());
      }
    }
  }

  AND_GIVEN("stack with one or more elements") {
    const int capacity = GENERATE(range(1, 11));
    const int size = GENERATE_COPY(range(1, capacity + 1));

    const auto elems = utils::rand_array(size, 0, 100, true);

    const auto stack = ArrayStack(elems, capacity);

    REQUIRE(stack.size() == size);
    REQUIRE(stack.capacity() == capacity);

    WHEN("peeking an element") {

      THEN("peek should return the last pushed element") {
        const auto last_pushed_elem = elems.back();
        CHECK(stack.Peek() == last_pushed_elem);
      }
    }
  }
}

SCENARIO("ArrayStack::Resize") {

  GIVEN("stack with zero or more elements: size <= capacity") {
    const int capacity = GENERATE(range(1, 11));
    const int size = GENERATE_COPY(range(0, capacity + 1));

    const auto elems = utils::rand_array(size, 0, 100, true);

    auto stack = ArrayStack(elems, capacity);

    REQUIRE(stack.size() == size);
    REQUIRE(stack.capacity() == capacity);

    WHEN("resizing to a new capacity <= previous capacity") {
      const int new_capacity = GENERATE_COPY(range(-10, capacity + 1));

      REQUIRE_FALSE(stack.Resize(new_capacity));

      THEN("stack size should not be changed") {
        const int size_before_resize = size;
        CHECK(stack.size() == size_before_resize);
      }

      AND_THEN("stack capacity should not be changed") {
        const int capacity_before_resize = capacity;
        CHECK(stack.capacity() == capacity_before_resize);
      }

      AND_THEN("stack elements should not be changed") {
        CHECK_THAT(stack.toVector(size), Equals(elems));
      }
    }

    AND_WHEN("resizing to a new capacity > previous capacity") {
      const int new_capacity = GENERATE_COPY(range(capacity + 1, capacity + 6));

      REQUIRE(stack.Resize(new_capacity));

      THEN("stack size should not be changed") {
        const int size_before_resize = size;
        CHECK(stack.size() == size_before_resize);
      }

      AND_THEN("stack capacity should be increased") {
        CHECK(stack.capacity() == new_capacity);
      }

      AND_THEN("stack elements should not be changed") {
        CHECK_THAT(stack.toVector(size), Equals(elems));
      }
    }
  }
}

SCENARIO("ArrayStack::Push") {

  GIVEN("stack with zero or more elements: size < capacity") {
    const int capacity = GENERATE(range(1, 11));
    const int size = GENERATE_COPY(range(0, capacity));

    const auto elems = utils::rand_array(size, 0, 100, true);

    auto stack = ArrayStack(elems, capacity);

    REQUIRE(stack.size() == size);
    REQUIRE(stack.capacity() == capacity);

    WHEN("pushing an element") {
      const int push_elem = GENERATE(take(5, random(0, 100)));

      stack.Push(push_elem);

      THEN("stack size should be increased") {
        const int size_after_push = size + 1;
        CHECK(stack.size() == size_after_push);
      }

      AND_THEN("stack capacity should not be changed") {
        const int capacity_before_push = capacity;
        CHECK(stack.capacity() == capacity_before_push);
      }

      AND_THEN("peek should return the pushed element") {
        CHECK(stack.Peek() == push_elem);
      }

      AND_THEN("stack should contain all previous elements") {
        CHECK_THAT(stack.toVector(size), Contains(elems));
      }
    }
  }

  AND_GIVEN("stack full of elements: size = capacity") {
    const int capacity = GENERATE(range(1, 11));
    const auto elems = utils::rand_array(capacity, 0, 100, true);

    auto stack = ArrayStack(elems, capacity);

    REQUIRE(stack.size() == capacity);
    REQUIRE(stack.capacity() == capacity);

    WHEN("pushing an element") {
      const int push_elem = GENERATE(take(10, random(0, 100)));

      stack.Push(push_elem);

      THEN("stack size should be increased") {
        const int size_after_push = capacity + 1;
        CHECK(stack.size() == size_after_push);
      }

      AND_THEN("stack capacity should be increased to the factor of " << ArrayStack::kCapacityGrowthCoefficient) {
        const int capacity_after_push = capacity + ArrayStack::kCapacityGrowthCoefficient;
        CHECK(stack.capacity() == capacity_after_push);
      }

      AND_THEN("peek should return the pushed element") {
        CHECK(stack.Peek() == push_elem);
      }

      AND_THEN("stack should contains all previous elements") {
        CHECK_THAT(stack.toVector(), Contains(elems));
      }
    }
  }
}

SCENARIO("ArrayStack::Pop") {

  GIVEN("empty stack") {
    const int capacity = GENERATE(range(1, 11));

    auto stack = ArrayStack(capacity);

    REQUIRE(stack.IsEmpty());
    REQUIRE(stack.capacity() == capacity);

    WHEN("popping an element") {
      REQUIRE_FALSE(stack.Pop());

      THEN("stack should be empty") {
        CHECK(stack.IsEmpty());
      }

      AND_THEN("stack capacity should not be changed") {
        const int capacity_before_pop = capacity;
        CHECK(stack.capacity() == capacity_before_pop);
      }

      AND_THEN("stack should be initialized with zeros") {
        const auto zeros = std::vector<int>(capacity);
        CHECK_THAT(stack.toVector(), Equals(zeros));
      }
    }
  }

  AND_GIVEN("stack with one or more elements") {
    const int capacity = GENERATE(range(1, 11));
    const int size = GENERATE_COPY(range(1, capacity + 1));

    const auto elems = utils::rand_array(size, 0, 100, true);

    auto stack = ArrayStack(elems, capacity);

    REQUIRE(stack.size() == size);
    REQUIRE(stack.capacity() == capacity);

    WHEN("popping an element") {

      REQUIRE(stack.Pop());

      THEN("stack size should be decreased") {
        const int size_after_pop = size - 1;
        CHECK(stack.size() == size_after_pop);
      }

      AND_THEN("stack capacity should not be changed") {
        const int capacity_before_pop = capacity;
        CHECK(stack.capacity() == capacity_before_pop);
      }

      AND_THEN("stack should not contain the popped element") {
        const int size_after_pop = size - 1;
        const int popped_elem = elems[elems.size() - 1];

        CHECK_THAT(stack.toVector(size_after_pop), !VectorContains(popped_elem));
      }
    }
  }
}

SCENARIO("ArrayStack::Clear") {

  GIVEN("stack with zero or more elements") {
    const int capacity = GENERATE(range(1, 11));
    const int size = GENERATE_COPY(range(0, capacity + 1));

    const auto elems = utils::rand_array(size, 0, 100, true);

    auto stack = ArrayStack(elems, capacity);

    REQUIRE(stack.size() == size);
    REQUIRE(stack.capacity() == capacity);

    WHEN("clearing the stack") {
      stack.Clear();

      THEN("stack should be empty") {
        CHECK(stack.IsEmpty());
      }

      AND_THEN("stack capacity should not be changed") {
        const int capacity_before_clear = capacity;
        CHECK(stack.capacity() == capacity_before_clear);
      }
    }
  }
}
