#define BOOST_TEST_MODULE queueTest
#include <boost/test/included/unit_test.hpp>

#include "../data_structures/queue.hpp"

BOOST_AUTO_TEST_CASE(test_Queue) {
    Queue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    BOOST_CHECK_EQUAL(queue.size(), 3);

    auto data = queue.data();
    BOOST_CHECK_EQUAL(data.get(0), 1); 
    BOOST_CHECK_EQUAL(data.get(1), 2);
    BOOST_CHECK_EQUAL(data.get(2), 3);

    int popped = queue.dequeue();
    BOOST_CHECK_EQUAL(popped, 1);
}

BOOST_AUTO_TEST_CASE(test_error) {
    Queue<int> q;
    BOOST_CHECK_THROW(q.dequeue(), runtime_error);
}