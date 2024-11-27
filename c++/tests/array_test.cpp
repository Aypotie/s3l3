#define BOOST_TEST_MODULE ArrayTest
#include <boost/test/included/unit_test.hpp>

#include "../data_structures/vector.hpp"

BOOST_AUTO_TEST_CASE(test_array) {
    Vector<int> testVec;

    for (int i = 0; i < 6; i++) {
        testVec.pushBack(i);
    }
    BOOST_CHECK_EQUAL(testVec.size(), 6); //pushback

    testVec.insert(5, 666);
    int want[] = {0, 1, 2, 3, 4, 666, 5};

    for (int i = 0; i < 7; i++) {
        BOOST_CHECK_EQUAL(testVec.get(i), want[i]); //insert
    }

    BOOST_CHECK_EQUAL(testVec.size(), 7); //len

    testVec.remove(3);
    int want2[] = {0, 1, 2, 4, 666, 5};

    for (int i = 0; i < 6; i++) {
        BOOST_CHECK_EQUAL(testVec.get(i), want2[i]); //remove
    }

    testVec.pushBack(1);
    testVec.pushBack(2);
    testVec.pushBack(3);

    BOOST_CHECK_EQUAL(testVec.capacity(), 32); //extend

    testVec.set(0, 100);
    BOOST_CHECK_EQUAL(testVec.get(0), 100); //set

}
