#define BOOST_TEST_MODULE SlistTest
#include <boost/test/included/unit_test.hpp>

#include "../data_structures/slist.hpp"

BOOST_AUTO_TEST_CASE(test_Slist) {
    SList<int> slist;

    slist.pushBack(2);
    BOOST_CHECK_EQUAL(slist.get(0), 2);
    slist.pushBack(4);
    BOOST_CHECK_EQUAL(slist.get(1), 4); // pushback

    slist.pushForward(1);
    BOOST_CHECK_EQUAL(slist.get(0), 1); // pushForward
    slist.pushForward(5);
    BOOST_CHECK_EQUAL(slist.get(0), 5);

    BOOST_CHECK_EQUAL(slist.size(), 4); // size

    slist.removeBack();
    int want[] = {5, 1, 2};
    for (int i = 0;  i < 3; i++) {
        BOOST_CHECK_EQUAL(slist.get(i), want[i]); // removeback
    }

    slist.removeForward();
    int want2[] = {1, 2};
    for (int i = 0;  i < 2; i++) {
        BOOST_CHECK_EQUAL(slist.get(i), want2[i]); // removeForward
    }

    auto a = slist.findByValue(1);
    BOOST_CHECK_EQUAL(a, slist.getHead()); // findByValue

    slist.pushBack(3);

    slist.removeValue(2);
    int want3[] = {1, 3};
    for (int i = 0;  i < 2; i++) {
        BOOST_CHECK_EQUAL(slist.get(i), want3[i]); // removeValue
    }
}

BOOST_AUTO_TEST_CASE(test_error) {
    SList<int> sl;
    BOOST_CHECK_EQUAL(nullptr, sl.getHead());

    BOOST_CHECK_THROW(sl.get(3), runtime_error);
    BOOST_CHECK_THROW(sl.removeForward(), runtime_error);
    BOOST_CHECK_THROW(sl.removeBack(), runtime_error);
    BOOST_CHECK_EQUAL(sl.findByValue(3), nullptr);
}