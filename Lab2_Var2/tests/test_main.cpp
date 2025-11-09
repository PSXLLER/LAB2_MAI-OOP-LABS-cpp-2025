#include <gtest/gtest.h>
#include "Array.h"
#include "Hex.h"
#include <stdexcept>

// =======================================================
//                     ТЕСТЫ КЛАССА Array
// =======================================================

// --- 1. Проверка конструктора по размеру ---
TEST(ArrayTest, ConstructorWithSizeAndDefaultValue)
{
    Array a(5, 9);
    EXPECT_EQ(a.size(), 5);
    for (size_t i = 0; i < a.size(); ++i)
        EXPECT_EQ(a.ar(i), 9);
}

// --- 2. Проверка конструктора initializer_list ---
TEST(ArrayTest, ConstructorInitializerList)
{
    Array a({1, 2, 3, 4});
    EXPECT_EQ(a.size(), 4);
    EXPECT_EQ(a.ar(0), 1);
    EXPECT_EQ(a.ar(3), 4);
}

// --- 3. Проверка конструктора из строки ---
TEST(ArrayTest, ConstructorFromString)
{
    Array a(std::string("AB"));
    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(a.ar(0), 'A');
    EXPECT_EQ(a.ar(1), 'B');
}

// --- 4. Копирующий конструктор ---
TEST(ArrayTest, CopyConstructor)
{
    Array a({1, 2, 3});
    Array b(a);
    EXPECT_TRUE(a.equal(b));
}

// --- 5. Перемещающий конструктор ---
TEST(ArrayTest, MoveConstructor)
{
    Array a({10, 20, 30});
    Array b(std::move(a));
    EXPECT_EQ(b.size(), 3);
}

// --- 6. Проверка метода size ---
TEST(ArrayTest, SizeMethod)
{
    Array a({5, 6, 7});
    EXPECT_EQ(a.size(), 3);
}

// --- 7. Проверка метода ar (чтение элемента) ---
TEST(ArrayTest, ArMethod)
{
    Array a({5, 10, 15});
    EXPECT_EQ(a.ar(2), 15);
}

// --- 8. Проверка исключения при выходе за границы ---
TEST(ArrayTest, ArMethodOutOfRange)
{
    Array a({1, 2, 3});
    EXPECT_THROW(a.ar(5), std::out_of_range);
}

// --- 9. Проверка set() ---
TEST(ArrayTest, SetMethod)
{
    Array a({1, 2, 3});
    a.set(1, 42);
    EXPECT_EQ(a.ar(1), 42);
}

// --- 10. Проверка add() ---
TEST(ArrayTest, AddEqualLength)
{
    Array a({1, 2, 3});
    Array b({4, 5, 6});
    Array c = a.add(b);
    EXPECT_EQ(c.ar(0), 5);
    EXPECT_EQ(c.ar(1), 7);
    EXPECT_EQ(c.ar(2), 9);
}

// --- 11. Проверка add() при разных длинах ---
TEST(ArrayTest, AddDifferentLengthThrows)
{
    Array a({1, 2});
    Array b({3, 4, 5});
    EXPECT_THROW(a.add(b), std::invalid_argument);
}

// --- 12. Проверка sub() ---
TEST(ArrayTest, SubEqualLength)
{
    Array a({10, 20, 30});
    Array b({5, 10, 15});
    Array c = a.sub(b);
    EXPECT_EQ(c.ar(0), 5);
    EXPECT_EQ(c.ar(2), 15);
}

// --- 13. Проверка sub() при разных длинах ---
TEST(ArrayTest, SubDifferentLengthThrows)
{
    Array a({1, 2, 3});
    Array b({4, 5});
    EXPECT_THROW(a.sub(b), std::invalid_argument);
}

// --- 14. Проверка equal() ---
TEST(ArrayTest, Equal)
{
    Array a({1, 2, 3});
    Array b({1, 2, 3});
    Array c({1, 2, 4});
    EXPECT_TRUE(a.equal(b));
    EXPECT_FALSE(a.equal(c));
}

// --- 15. Проверка less() и greater() ---
TEST(ArrayTest, LessAndGreater)
{
    Array a({1, 2, 3});
    Array b({1, 2, 4});
    EXPECT_TRUE(a.less(b));
    EXPECT_FALSE(a.greater(b));
}

// =======================================================
//                     ТЕСТЫ КЛАССА Hex
// =======================================================

// --- 16. Конструктор без параметров ---
TEST(HexTest, DefaultConstructor)
{
    Hex h;
    EXPECT_EQ(h.size(), 1);
    EXPECT_EQ(h.toString(), "0");
}

// --- 17. Конструктор из строки ---
TEST(HexTest, ConstructorFromString)
{
    Hex h("1A3");
    EXPECT_EQ(h.toString(), "1A3");
}

// --- 18. Конструктор initializer_list ---
TEST(HexTest, ConstructorInitializerList)
{
    Hex h({10, 11, 12});
    EXPECT_EQ(h.toString(), "CBA");
}

// --- 19. Конструктор копирования ---
TEST(HexTest, CopyConstructor)
{
    Hex h1("ABC");
    Hex h2(h1);
    EXPECT_TRUE(h1.equal(h2));
}

// --- 20. Конструктор перемещения ---
TEST(HexTest, MoveConstructor)
{
    Hex h1("FF");
    Hex h2(std::move(h1));
    EXPECT_EQ(h2.toString(), "FF");
}

// --- 21. Проверка add() ---
TEST(HexTest, AddSimple)
{
    Hex a("A");
    Hex b("5");
    Hex c = a.add(b);
    EXPECT_EQ(c.toString(), "F");
}

// --- 22. Проверка add() с переносом ---
TEST(HexTest, AddWithCarry)
{
    Hex a("F");
    Hex b("1");
    Hex c = a.add(b);
    EXPECT_EQ(c.toString(), "10");
}

// --- 23. Проверка sub() ---
TEST(HexTest, SubSimple)
{
    Hex a("15");
    Hex b("5");
    Hex c = a.sub(b);
    EXPECT_EQ(c.toString(), "10");
}

// --- 24. Проверка sub() при вычитании большего числа ---
TEST(HexTest, SubLargerThrows)
{
    Hex a("5");
    Hex b("A");
    EXPECT_THROW(a.sub(b), std::invalid_argument);
}

// --- 25. Проверка equal(), less(), greater() ---
TEST(HexTest, Comparisons)
{
    Hex a("1F");
    Hex b("1F");
    Hex c("2A");
    EXPECT_TRUE(a.equal(b));
    EXPECT_TRUE(a.less(c));
    EXPECT_TRUE(c.greater(a));
}

// --- 26. Проверка copy() ---
TEST(HexTest, Copy)
{
    Hex a("FF");
    Hex b = a.copy();
    EXPECT_TRUE(a.equal(b));
}

// --- 27. Проверка toString() ---
TEST(HexTest, ToString)
{
    Hex a("123");
    EXPECT_EQ(a.toString(), "123");
}

// --- 28. Проверка add_a() ---
TEST(HexTest, AddAssign)
{
    Hex a("A");
    Hex b("1");
    a.add_a(b);
    EXPECT_EQ(a.toString(), "B");
}

// --- 29. Проверка sub_a() ---
TEST(HexTest, SubAssign)
{
    Hex a("B");
    Hex b("1");
    a.sub_a(b);
    EXPECT_EQ(a.toString(), "A");
}

// --- 30. Проверка copy_a() ---
TEST(HexTest, CopyAssign)
{
    Hex a("1A");
    Hex b("FF");
    a.copy_a(b);
    EXPECT_TRUE(a.equal(b));
}

// --- 31. Проверка исключений при неправильных символах ---
TEST(HexTest, InvalidCharacterThrows)
{
    EXPECT_THROW(Hex("Z1"), std::invalid_argument);
}

// --- 32. Проверка сложения длинных чисел ---
TEST(HexTest, AddLongNumbers)
{
    Hex a("FFFF");
    Hex b("1");
    Hex c = a.add(b);
    EXPECT_EQ(c.toString(), "10000");
}

// --- 33. Проверка вычитания с заёмом ---
TEST(HexTest, SubWithBorrow)
{
    Hex a("100");
    Hex b("1");
    Hex c = a.sub(b);
    EXPECT_EQ(c.toString(), "FF");
}

// --- 34. Проверка пустой строки ---
TEST(HexTest, EmptyStringThrows)
{
    EXPECT_THROW(Hex(""), std::invalid_argument);
}

// --- 35. Проверка toString() после операций ---
TEST(HexTest, ToStringAfterAddSub)
{
    Hex a("A");
    Hex b("5");
    Hex c = a.add(b);
    EXPECT_EQ(c.toString(), "F");

    Hex d = c.sub(Hex("1"));
    EXPECT_EQ(d.toString(), "E");
}