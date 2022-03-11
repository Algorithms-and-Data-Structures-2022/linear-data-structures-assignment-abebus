#include <catch2/catch.hpp>

#include "utils.hpp"  // rand_array

#include "assignment/linked_queue.hpp"  // LinkedQueue

using assignment::LinkedQueue;

using Catch::Matchers::Contains;
using Catch::Matchers::VectorContains;

SCENARIO("LinkedQueue::LinkedQueue") {

  WHEN("creating queue using default constructor") {
    const auto queue = LinkedQueue();

    THEN("queue should be empty") {
      CHECK(queue.IsEmpty());
    }

    AND_THEN("front should have no value") {
      CHECK_FALSE(queue.front().has_value());
    }

    AND_THEN("back should have no value") {
      CHECK_FALSE(queue.front().has_value());
    }

    AND_THEN("queue should have no elements") {
      CHECK(queue.toVector().empty());
    }
  }
}

SCENARIO("LinkedQueue::Enqueue") {

  GIVEN("queue with zero or more elements") {
    const int size = GENERATE(range(0, 6));
    const auto elems = utils::rand_array(size, 0, 100, true);

    auto queue = LinkedQueue(elems);

    REQUIRE(queue.size() == size);

    WHEN("enqueueing one or more elements") {
      const int num_elems = GENERATE(range(1, 6));
      const auto enqueue_elems = utils::rand_array(num_elems, 0, 100, true);

      for (int elem : enqueue_elems) {
        queue.Enqueue(elem);
      }

      THEN("queue size should be increased") {
        const int size_after_enqueue = size + num_elems;
        CHECK(queue.size() == size_after_enqueue);
      }

      if (size > 0) {
        AND_THEN("front should not be changed") {
          const int front_elem = elems.front();
          CHECK(queue.front() == front_elem);
        }

        AND_THEN("back should be equal to the last enqueued element") {
          const int last_enqueued_elem = enqueue_elems.back();
          CHECK(queue.back() == last_enqueued_elem);
        }
      }

      AND_THEN("queue should contain enqueued elements") {
        CHECK_THAT(queue.toVector(), Contains(elems));
        CHECK_THAT(queue.toVector(), Contains(enqueue_elems));
      }
    }
  }
}

SCENARIO("LinkedQueue::Dequeue") {

  GIVEN("empty queue") {
    auto queue = LinkedQueue();

    REQUIRE(queue.IsEmpty());

    WHEN("dequeing an element") {
      REQUIRE_FALSE(queue.Dequeue());

      THEN("front and back should have no value") {
        CHECK_FALSE(queue.front().has_value());
        CHECK_FALSE(queue.back().has_value());
      }

      AND_THEN("queue should be empty") {
        CHECK(queue.IsEmpty());
      }

      AND_THEN("queue should have no elements") {
        CHECK(queue.toVector().empty());
      }
    }
  }

  AND_GIVEN("queue with one or more elements") {
    const int size = GENERATE(range(1, 6));
    const auto elems = utils::rand_array(size, 0, 100, true);

    auto queue = LinkedQueue(elems);

    REQUIRE(queue.size() == size);

    WHEN("dequeing an element") {

      REQUIRE(queue.Dequeue());

      THEN("queue size should be decreased") {
        const int size_after_dequeue = size - 1;
        CHECK(queue.size() == size_after_dequeue);
      }

      AND_THEN("front should be correct") {
        if (size == 1) {
          CHECK_FALSE(queue.front().has_value());
        } else {
          const int front_elem = elems[1];
          CHECK(queue.front() == front_elem);
        }
      }

      AND_THEN("back should not be changed") {
        if (size == 1) {
          CHECK_FALSE(queue.front().has_value());
        } else {
          const int back_elem = elems.back();
          CHECK(queue.back() == back_elem);
        }
      }

      AND_THEN("queue should not contain the dequeued element") {
        const int dequeued_elem = elems.front();
        CHECK_THAT(queue.toVector(), !VectorContains(dequeued_elem));
      }
    }
  }
}

SCENARIO("LinkedQueue::Clear") {

  GIVEN("queue with zero or more elements") {
    const int size = GENERATE(range(0, 6));
    const auto elems = utils::rand_array(size, 0, 100);

    auto queue = LinkedQueue(elems);

    REQUIRE(queue.size() == size);

    WHEN("clearing the queue") {
      queue.Clear();

      THEN("queue should be empty") {
        CHECK(queue.IsEmpty());
      }

      AND_THEN("front should have no value") {
        CHECK_FALSE(queue.front().has_value());
      }

      AND_THEN("back should have no value") {
        CHECK_FALSE(queue.back().has_value());
      }

      AND_THEN("queue should have no elements") {
        CHECK(queue.toVector().empty());
      }
    }
  }
}
