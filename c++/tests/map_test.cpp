#define BOOST_TEST_MODULE MapTest
#include <boost/test/included/unit_test.hpp>
#include "../data_structures/map.hpp"

// Тестирование основного функционала карты
BOOST_AUTO_TEST_CASE(test_put_and_get) {
    Map<int> map;

    // Добавление элементов в карту
    map.put("one", 1);
    map.put("two", 2);
    map.put("three", 3);

    // Проверка значений по ключам
    BOOST_CHECK_EQUAL(map.get("one"), 1);
    BOOST_CHECK_EQUAL(map.get("two"), 2);
    BOOST_CHECK_EQUAL(map.get("three"), 3);
}

// Тестирование обновления значений в карте
BOOST_AUTO_TEST_CASE(test_put_update_value) {
    Map<int> map;

    // Добавление элементов в карту
    map.put("one", 1);
    map.put("two", 2);

    // Обновление значений
    map.put("one", 11);
    map.put("two", 22);

    // Проверка обновленных значений
    BOOST_CHECK_EQUAL(map.get("one"), 11);
    BOOST_CHECK_EQUAL(map.get("two"), 22);
}

// Тестирование удаления элементов
BOOST_AUTO_TEST_CASE(test_remove) {
    Map<int> map;

    // Добавление элементов
    map.put("one", 1);
    map.put("two", 2);

    // Удаление элемента
    map.remove("one");

    // Проверка после удаления
    BOOST_CHECK_THROW(map.get("one"), runtime_error); // Проверка, что ключ "one" не найден
    BOOST_CHECK_EQUAL(map.get("two"), 2); // Проверка, что другой ключ остался
}

// Тестирование исключений при попытке получить несуществующий элемент
BOOST_AUTO_TEST_CASE(test_get_error) {
    Map<int> map;

    // Проверка на ошибку при получении несуществующего ключа
    BOOST_CHECK_THROW(map.get("nonexistent"), runtime_error);
}

// Тестирование поведения карты при превышении коэффициента загрузки
BOOST_AUTO_TEST_CASE(test_rehash) {
    Map<int> map;

    // Добавление элементов для того, чтобы карта заполнилась и сработал rehash
    for (int i = 0; i < 20; i++) {
        map.put("key" + to_string(i), i);
    }

    // После добавления большого количества элементов должно быть выполнено перераспределение
    BOOST_CHECK(map.getCap() > 16); // Проверка, что капасити карты увеличилась
}

// Тестирование пустой карты
BOOST_AUTO_TEST_CASE(test_empty_map) {
    Map<int> map;

    // Проверка размера пустой карты
    BOOST_CHECK_EQUAL(map.getLen(), 0);
    BOOST_CHECK_THROW(map.get("nonexistent"), std::runtime_error); // Ошибка при попытке получить несуществующий элемент
}

// Тестирование метода join
BOOST_AUTO_TEST_CASE(test_join) {
    Map<int> map;

    // Добавление элементов
    map.put("apple", 1);
    map.put("banana", 2);
    map.put("cherry", 3);

    // Проверка формата строки, который возвращает метод join
    BOOST_CHECK_EQUAL(map.join(), "apple,1;banana,2;cherry,3");
}

BOOST_AUTO_TEST_CASE(test_rehash_integrity) {
    Map<int> map;

    // Добавляем большое количество элементов, чтобы принудить `rehash`
    for (int i = 0; i < 1000; i++) {
        map.put("key" + to_string(i), i);
    }

    // Проверяем, что данные после rehash остались корректными
    for (int i = 0; i < 1000; i++) {
        BOOST_CHECK_EQUAL(map.get("key" + to_string(i)), i);
    }
}


