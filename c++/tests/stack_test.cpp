#define BOOST_TEST_MODULE SlistTest
#include <boost/test/included/unit_test.hpp>

#include "../data_structures/stack.hpp"

BOOST_AUTO_TEST_CASE(test_stack) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    BOOST_CHECK_EQUAL(stack.size(), 3);

    auto data = stack.data();
    BOOST_CHECK_EQUAL(data.get(0), 3); // Проверка, что элемент был добавлен сверху
    BOOST_CHECK_EQUAL(data.get(1), 2);
    BOOST_CHECK_EQUAL(data.get(2), 1);

    int popped = stack.pop();
    BOOST_CHECK_EQUAL(popped, 3);

}

BOOST_AUTO_TEST_CASE(test_error) {
    Stack<int> s;
    BOOST_CHECK_THROW(s.pop(), runtime_error);
}