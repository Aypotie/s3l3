#define BOOST_TEST_MODULE avlTest
#include <boost/test/included/unit_test.hpp>

#include "../data_structures/avl.hpp"

BOOST_AUTO_TEST_CASE(test_Avl) {
    AVLTree tree;

    // Вставка значений
    tree.insertNum(10);
    tree.insertNum(20);
    tree.insertNum(30);
    tree.insertNum(40);
    tree.insertNum(50);
    tree.insertNum(25);

    // Проверка существования значений
    BOOST_CHECK(tree.find(10) != nullptr);
    BOOST_CHECK(tree.find(20) != nullptr);
    BOOST_CHECK(tree.find(30) != nullptr);
    BOOST_CHECK(tree.find(40) != nullptr);
    BOOST_CHECK(tree.find(50) != nullptr);
    BOOST_CHECK(tree.find(25) != nullptr);
}

BOOST_AUTO_TEST_CASE(test_serialization) {
    AVLTree tree;

    // Вставляем значения
    tree.insertNum(10);
    tree.insertNum(20);
    tree.insertNum(30);

    // Сериализация дерева
    string serialized = tree.serialize();
    BOOST_CHECK(!serialized.empty());

    // Новый объект дерева
    AVLTree newTree;
    newTree.unserialize(serialized);

    // Проверка корректности десериализации
    BOOST_CHECK(newTree.find(10) != nullptr);
    BOOST_CHECK(newTree.find(20) != nullptr);
    BOOST_CHECK(newTree.find(30) != nullptr);
    BOOST_CHECK(newTree.find(40) == nullptr);
}

BOOST_AUTO_TEST_CASE(test_error_handling) {
    AVLTree tree;

    // Попытка удалить несуществующее значение
    BOOST_CHECK_NO_THROW(tree.removeNum(100));

    // Попытка вставить дублирующее значение
    tree.insertNum(10);
    BOOST_CHECK_NO_THROW(tree.insertNum(10));

    // Попытка сериализовать пустое дерево
    AVLTree emptyTree;
    string serialized = emptyTree.serialize();
    BOOST_CHECK_EQUAL(serialized, "#-");

    // Попытка десериализовать пустую строку
    BOOST_CHECK_NO_THROW(emptyTree.unserialize("#-"));
    BOOST_CHECK(emptyTree.find(10) == nullptr);
}

BOOST_AUTO_TEST_CASE(test_edge_cases) {
    AVLTree tree;

    // Добавление и удаление одного элемента
    tree.insertNum(5);
    BOOST_CHECK(tree.find(5) != nullptr);

    tree.removeNum(5);
    BOOST_CHECK(tree.find(5) == nullptr);

    // Проверка сбалансированности при последовательной вставке
    tree.insertNum(1);
    tree.insertNum(2);
    tree.insertNum(3);
    BOOST_CHECK_EQUAL(tree.find(2)->height, 2); // Корень должен быть "2"
    BOOST_CHECK(tree.find(1) != nullptr);
    BOOST_CHECK(tree.find(3) != nullptr);
}

BOOST_AUTO_TEST_CASE(test_AVLTreePrint) {
    AVLTree tree;

    // Построение дерева
    tree.insertNum(30);
    tree.insertNum(20);
    tree.insertNum(40);
    tree.insertNum(10);
    tree.insertNum(25);
    tree.insertNum(35);
    tree.insertNum(50);

    // Ожидаемое представление
    string expectedOutput =
        "    │   ┌──[50]\n"
        "    ┌──[40]\n"
        "    │   └──[35]\n"
        "[30]\n"
        "        ┌──[25]\n"
        "    └──[20]\n"
        "        └──[10]\n";

    // Проверяем вывод дерева
    stringstream ss;
    ss << tree;

    BOOST_CHECK_MESSAGE(ss.str() == expectedOutput, "Output: \n" + ss.str() + "\nExpected: \n" + expectedOutput);
}

