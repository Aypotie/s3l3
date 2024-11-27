#define BOOST_TEST_MODULE dlistTest
#include <boost/test/included/unit_test.hpp>

#include "../data_structures/dlist.hpp"

BOOST_AUTO_TEST_CASE(test_Dlist) {
    Dlist<int> dlist;

    dlist.pushBack(2);
    BOOST_CHECK_EQUAL(dlist.get(0), 2);
    dlist.pushBack(4);
    BOOST_CHECK_EQUAL(dlist.get(1), 4); // pushback

    dlist.pushForward(1);
    BOOST_CHECK_EQUAL(dlist.get(0), 1); // pushForward
    dlist.pushForward(5);
    BOOST_CHECK_EQUAL(dlist.get(0), 5);

    BOOST_CHECK_EQUAL(dlist.size(), 4); // size

    dlist.removeBack();
    int want[] = {5, 1, 2};
    for (int i = 0;  i < 3; i++) {
        BOOST_CHECK_EQUAL(dlist.get(i), want[i]); // removeback
    }

    dlist.removeForward();
    int want2[] = {1, 2};
    for (int i = 0;  i < 2; i++) {
        BOOST_CHECK_EQUAL(dlist.get(i), want2[i]); // removeForward
    }

    auto a = dlist.findByValue(1);
    BOOST_CHECK_EQUAL(a, dlist.getHead()); // findByValue

    dlist.pushBack(3);

    dlist.removeValue(2);
    int want3[] = {1, 3};
    for (int i = 0;  i < 2; i++) {
        BOOST_CHECK_EQUAL(dlist.get(i), want3[i]); // removeValue
    }

    dlist.removeValue(3);
    dlist.removeBack();
    BOOST_CHECK_EQUAL(dlist.getHead(), nullptr);
}

BOOST_AUTO_TEST_CASE(test_error) {
    Dlist<int> sl;
    BOOST_CHECK_EQUAL(nullptr, sl.getHead());

    BOOST_CHECK_THROW(sl.get(3), runtime_error);
    BOOST_CHECK_THROW(sl.removeForward(), runtime_error);
    BOOST_CHECK_THROW(sl.removeBack(), runtime_error);
    BOOST_CHECK_EQUAL(sl.findByValue(3), nullptr);
}