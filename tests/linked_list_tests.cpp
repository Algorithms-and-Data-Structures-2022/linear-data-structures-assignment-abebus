#include <catch2/catch.hpp>

#include <algorithm>  // find

#include "utils.hpp"  // rand_array

#include "assignment/linked_list.hpp"  // LinkedList

using assignment::LinkedList;

using Catch::Matchers::Contains;
using Catch::Matchers::Equals;
using Catch::Matchers::VectorContains;

SCENARIO("LinkedList::LinkedList") {

  WHEN("creating list using default constructor") {
    const auto list = LinkedList();

    THEN("list should be empty") {
      CHECK(list.IsEmpty());
    }

    AND_THEN("front should have no value") {
      CHECK_FALSE(list.front().has_value());
    }

    AND_THEN("back should have no value") {
      CHECK_FALSE(list.front().has_value());
    }

    AND_THEN("list should not contain any element") {
      CHECK(list.toVector().empty());
    }
  }
}

SCENARIO("LinkedList::Add") {

  GIVEN("empty list") {
    auto list = LinkedList();

    REQUIRE(list.IsEmpty());

    WHEN("adding an element") {
      const int add_elem = GENERATE(take(10, random(0, 100)));

      list.Add(add_elem);

      THEN("list size should be increased") {
        const int size_after_add = 1;
        CHECK(list.size() == size_after_add);
      }

      AND_THEN("front should be equal to back") {
        const int front_elem = add_elem;

        REQUIRE(list.front() == front_elem);
        CHECK(list.front() == list.back());
      }

      AND_THEN("list should contain one element") {
        CHECK_THAT(list.toVector(), VectorContains(add_elem));
      }
    }
  }

  AND_GIVEN("list of one or more elements") {
    const int size = GENERATE(range(1, 6));
    const auto elems = utils::rand_array(size, 0, 100, true);

    auto list = LinkedList(elems);

    REQUIRE(list.size() == size);

    WHEN("adding one or more elements") {
      const int num_elems_to_add = GENERATE(range(1, 6));
      const auto add_elems = utils::rand_array(num_elems_to_add, 0, 100, true);

      for (int elem : add_elems) {
        list.Add(elem);
      }

      THEN("list size should be increased") {
        const int size_after_add = size + num_elems_to_add;
        CHECK(list.size() == size_after_add);
      }

      AND_THEN("front should not be changed") {
        const auto front_elem = elems.front();
        CHECK(list.front() == front_elem);
      }

      AND_THEN("back should be equal to the last added element") {
        const int last_added_elem = add_elems.back();
        CHECK(list.back() == last_added_elem);
      }

      AND_THEN("list should contain added elements") {
        CHECK_THAT(list.toVector(), Contains(elems));
        CHECK_THAT(list.toVector(), Contains(add_elems));
      }
    }
  }
}

SCENARIO("LinkedList::FindNode") {

  GIVEN("empty list") {
    const auto list = LinkedList();

    REQUIRE(list.IsEmpty());

    WHEN("finding node at any index") {
      const int find_index = GENERATE(range(-10, 11));

      THEN("nothing should be found") {
        CHECK(list.FindNode(find_index) == nullptr);
      }
    }
  }

  AND_GIVEN("list with one or more elements") {
    const int size = GENERATE(range(1, 11));
    const auto elems = utils::rand_array(size, 0, 100, true);

    const auto list = LinkedList(elems);

    REQUIRE(list.size() == size);

    WHEN("finding node at index in [0, size)") {
      const int find_index = GENERATE_COPY(range(0, size));
      const int elem_at_index = elems[find_index];

      auto* found_node = list.FindNode(find_index);

      THEN("node at the specified index should be found") {
        REQUIRE(found_node != nullptr);
        CHECK(found_node->value == elem_at_index);
      }
    }

    AND_WHEN("finding node at index outside [0, size)") {
      const auto pred = [size](int idx) { return idx < 0 || idx >= size; };
      const int find_index = GENERATE_REF(filter(pred, range(-10, size + 11)));

      THEN("nothing should be found") {
        CHECK(list.FindNode(find_index) == nullptr);
      }
    }
  }
}

SCENARIO("LinkedList::Get") {

  GIVEN("empty list") {
    const auto list = LinkedList();

    REQUIRE(list.IsEmpty());

    WHEN("getting an element at any index") {
      const int index = GENERATE(-10, 11);

      THEN("nothing should be returned") {
        CHECK_FALSE(list.Get(index).has_value());
      }
    }
  }

  AND_GIVEN("list with one or more elements") {
    const int size = GENERATE(range(1, 6));
    const auto elems = utils::rand_array(size, 0, 100, true);

    const auto list = LinkedList(elems);

    REQUIRE(list.size() == size);

    WHEN("getting an element at index in [0, size)") {
      const int index = GENERATE_COPY(range(0, size));

      THEN("element at the specified index should be returned") {
        const int elem_at_index = elems[index];
        CHECK(list.Get(index) == elem_at_index);
      }
    }

    AND_WHEN("getting an element at index outside [0, size)") {
      const auto pred = [size](int idx) { return idx < 0 || idx >= size; };
      const int index = GENERATE_REF(filter(pred, range(-10, size + 11)));

      THEN("nothing should be returned") {
        CHECK_FALSE(list.Get(index).has_value());
      }
    }
  }
}

SCENARIO("LinkedList::Set") {

  GIVEN("empty list") {
    auto list = LinkedList();

    WHEN("setting an element at any index") {
      const int set_index = GENERATE(-10, 11);
      const int set_elem = GENERATE(take(10, random(0, 100)));

      REQUIRE_FALSE(list.Set(set_index, set_elem));

      THEN("list size should not be changed") {
        const int size_before_set = 0;
        CHECK(list.size() == size_before_set);
      }

      AND_THEN("list should not contain any element") {
        CHECK(list.toVector().empty());
      }
    }
  }

  AND_GIVEN("list with one or more elements") {
    const int size = GENERATE(range(1, 11));
    const auto elems = utils::rand_array(size, 0, 100, true);

    auto list = LinkedList(elems);

    REQUIRE(list.size() == size);

    WHEN("setting an element at index in [0, size)") {
      const int set_index = GENERATE_COPY(range(0, size));
      const int set_elem = GENERATE(take(5, random(0, 100)));

      REQUIRE(list.Set(set_index, set_elem));

      THEN("list size should not be changed") {
        const int size_before_insert = size;
        CHECK(list.size() == size_before_insert);
      }

      AND_THEN("element at the specified index should be changed") {
        CHECK(list.Get(set_index) == set_elem);
      }
    }

    AND_WHEN("setting an element at index outside [0, size)") {
      const auto pred = [size](int idx) { return idx < 0 || idx >= size; };
      const int set_index = GENERATE_REF(filter(pred, range(-10, size + 11)));

      const int set_elem = GENERATE(take(10, random(0, 100)));

      REQUIRE_FALSE(list.Set(set_index, set_elem));

      THEN("list size should not be changed") {
        const int size_before_set = size;
        CHECK(list.size() == size_before_set);
      }

      AND_THEN("list elements should not be changed") {
        CHECK_THAT(list.toVector(), Equals(elems));
      }
    }
  }
}

SCENARIO("LinkedList::IndexOf") {

  GIVEN("list with one or more elements") {
    const int size = GENERATE(range(1, 11));
    const auto elems = utils::rand_array(size, 0, 100);

    const auto list = LinkedList(elems);

    REQUIRE(list.size() == size);

    WHEN("finding index of an existing element") {
      const int index = GENERATE_COPY(range(0, size));
      const int find_elem = elems[index];

      const int find_index = std::distance(elems.cbegin(), std::find(elems.cbegin(), elems.cend(), find_elem));

      THEN("correct index should be found") {
        CHECK(list.IndexOf(find_elem) == find_index);
      }
    }
  }
}

SCENARIO("LinkedList::Contains") {

  GIVEN("list with one or more elements") {
    const int size = GENERATE(range(1, 11));
    const auto elems = utils::rand_array(size, 0, 100);

    const auto list = LinkedList(elems);

    REQUIRE(list.size() == size);

    WHEN("checking if it contains an existing element") {
      const int index = GENERATE_COPY(range(0, size));
      const int elem = elems[index];

      THEN("contains should return true") {
        CHECK(list.Contains(elem));
      }
    }
  }
}

SCENARIO("LinkedList::Insert") {

  GIVEN("empty list") {
    auto list = LinkedList();

    REQUIRE(list.IsEmpty());

    WHEN("inserting an element at front: index = 0") {
      const int insert_index = 0;
      const int insert_elem = GENERATE(take(10, random(0, 100)));

      REQUIRE(list.Insert(insert_index, insert_elem));

      THEN("list size should be increased") {
        const int size_after_insert = 1;
        CHECK(list.size() == size_after_insert);
      }

      AND_THEN("front and back sound be equal to the inserted element") {
        CHECK(list.front() == insert_elem);
        CHECK(list.front() == list.back());
      }

      AND_THEN("list should contain only the inserted element") {
        CHECK_THAT(list.toVector(), VectorContains(insert_elem));
      }
    }

    AND_WHEN("inserting an element at any index != 0") {
      const auto pred = [](int idx) { return idx != 0; };
      const int insert_index = GENERATE_COPY(filter(pred, range(-10, 11)));

      const int insert_elem = GENERATE(take(10, random(0, 100)));

      REQUIRE_FALSE(list.Insert(insert_index, insert_elem));

      THEN("list should be empty") {
        CHECK(list.IsEmpty());
      }

      AND_THEN("list should not contain any element") {
        CHECK(list.toVector().empty());
      }
    }
  }

  AND_GIVEN("list with one or more elements") {
    const int size = GENERATE(range(1, 11));
    const auto elems = utils::rand_array(size, 0, 100, true);

    auto list = LinkedList(elems);

    REQUIRE(list.size() == size);

    WHEN("inserting an element at front: index = 0") {
      const int insert_index = 0;
      const int insert_elem = GENERATE(take(10, random(0, 100)));

      REQUIRE(list.Insert(insert_index, insert_elem));

      THEN("list size should be increased") {
        const int size_after_insert = size + 1;
        CHECK(list.size() == size_after_insert);
      }

      AND_THEN("front should be equal to the inserted element") {
        CHECK(list.front() == insert_elem);
      }

      AND_THEN("all elements should be present") {
        CHECK_THAT(list.toVector(), Contains(elems));
      }
    }

    AND_WHEN("inserting an element at back: index = size") {
      const int insert_index = size;
      const int insert_elem = GENERATE(take(10, random(0, 100)));

      REQUIRE(list.Insert(insert_index, insert_elem));

      THEN("list size should be increased") {
        const int size_after_insert = size + 1;
        CHECK(list.size() == size_after_insert);
      }

      AND_THEN("back should be equal to the inserted element") {
        CHECK(list.back() == insert_elem);
      }

      AND_THEN("all elements should be present") {
        CHECK_THAT(list.toVector(), Contains(elems));
      }
    }

    if (size > 1) {
      AND_WHEN("inserting an element at index in [1, size)") {
        const int insert_index = GENERATE_COPY(range(1, size));
        const int insert_elem = GENERATE(take(10, random(0, 100)));

        CAPTURE(list.toVector(), insert_elem, insert_index);

        REQUIRE(list.Insert(insert_index, insert_elem));

        THEN("list size should be increased") {
          const int size_after_insert = size + 1;
          CHECK(list.size() == size_after_insert);
        }

        AND_THEN("inserted element should be at the specified index") {
          CHECK(list.Get(insert_index) == insert_elem);
        }

        AND_THEN("all elements should be present") {
          CHECK_THAT(list.toVector(), Contains(elems));
        }
      }
    }

    AND_WHEN("inserting one element at index outside [0, size]") {
      const auto pred = [size](int idx) { return idx < 0 || idx > size; };
      const int insert_index = GENERATE_REF(filter(pred, range(-10, size + 11)));

      const int insert_elem = GENERATE(take(10, random(0, 100)));

      REQUIRE_FALSE(list.Insert(insert_index, insert_elem));

      THEN("list size should be changed") {
        const int size_before_insert = size;
        CHECK(list.size() == size_before_insert);
      }

      AND_THEN("list elements should not be changed") {
        CHECK_THAT(list.toVector(), Equals(elems));
      }
    }
  }
}

SCENARIO("LinkedList::Remove") {

  GIVEN("empty list") {
    auto list = LinkedList();

    REQUIRE(list.IsEmpty());

    WHEN("removing an element at any index") {
      const int remove_index = GENERATE(range(-10, 11));

      REQUIRE_FALSE(list.Remove(remove_index));

      THEN("list should be empty") {
        CHECK(list.IsEmpty());
      }

      AND_THEN("list should not contain any element") {
        CHECK(list.toVector().empty());
      }
    }
  }

  GIVEN("list with one or more elements") {
    const int size = GENERATE(range(1, 11));
    const auto elems = utils::rand_array(size, 0, 100, true);

    auto list = LinkedList(elems);

    REQUIRE(list.size() == size);

    WHEN("removing an element at front: index = 0") {
      const int remove_index = 0;

      const auto removed = list.Remove(remove_index);

      THEN("correct removed element should be returned") {
        const int removed_elem = elems[remove_index];
        CHECK(removed == removed_elem);
      }

      AND_THEN("list size should be decreased") {
        const int size_after_remove = size - 1;
        CHECK(list.size() == size_after_remove);
      }

      AND_THEN("list should not contain the removed element") {
        const int removed_elem = elems[remove_index];
        CHECK_THAT(list.toVector(), !VectorContains(removed_elem));
      }
    }

    if (size > 1) {
      AND_WHEN("removing an element at index in (0, size)") {
        const int remove_index = GENERATE_COPY(range(1, size));

        const auto removed = list.Remove(remove_index);

        THEN("list size should be decreased") {
          const int size_after_remove = size - 1;
          CHECK(list.size() == size_after_remove);
        }

        AND_THEN("correct removed element should be returned") {
          const int removed_elem = elems[remove_index];
          CHECK(removed == removed_elem);
        }

        AND_THEN("list should not contain the removed element") {
          const int removed_elem = elems[remove_index];
          CHECK_THAT(list.toVector(), !VectorContains(removed_elem));
        }
      }
    }
  }
}

SCENARIO("LinkedList::Clear") {

  GIVEN("list with zero or more elements") {
    const int size = GENERATE(range(0, 11));
    const auto elems = utils::rand_array(size, 0, 100);

    auto list = LinkedList(elems);

    REQUIRE(list.size() == size);

    WHEN("clearing the list") {
      list.Clear();

      THEN("list should be empty") {
        CHECK(list.IsEmpty());
      }

      AND_THEN("front and back should have no value") {
        CHECK_FALSE(list.front().has_value());
        CHECK(list.front() == list.back());
      }

      AND_THEN("list should not contains any element") {
        CHECK(list.toVector().empty());
      }
    }
  }
}