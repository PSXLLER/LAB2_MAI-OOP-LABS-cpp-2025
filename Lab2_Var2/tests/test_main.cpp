#include <gtest/gtest.h>
#include "Array.h"
#include "Hex.h"
#include <stdexcept>

TEST(ArrayTest, CtorSizeDefault)
{
    Array a(5, 9);
    ASSERT_EQ(a.size(), 5u);
    for (size_t i = 0; i < a.size(); ++i) {
        EXPECT_EQ(a.ar(i), 9);
    }
}

TEST(ArrayTest, InitListCtor)
{
    auto a = Array{1,2,3,4};
    EXPECT_EQ(a.size(), 4u);
    ASSERT_TRUE(a.ar(0)==1 && a.ar(3)==4);
}

TEST(ArrayTest, FromString)
{
    Array arr(std::string("AB"));
    EXPECT_EQ(arr.size(), 2u);
    EXPECT_EQ(arr.ar(0),'A');
    EXPECT_EQ(arr.ar(1),'B');
}

TEST(ArrayTest, CopyMove)
{
    Array src({1,2,3});
    Array copy(src);
    EXPECT_TRUE(copy.equal(src));

    Array moved(std::move(copy));
    EXPECT_EQ(moved.size(),3u);
}

TEST(ArrayTest, AddAndSub)
{
    Array a({1,2,3}), b({4,5,6});
    auto sum = a.add(b);
    EXPECT_EQ(sum.ar(2),9);

    Array x({10,20,30}), y({5,10,15});
    auto diff = x.sub(y);
    EXPECT_EQ(diff.ar(0),5);
}

TEST(ArrayTest, OutOfRangeAndInvalid)
{
    Array t({1,2,3});
    EXPECT_THROW(t.ar(5), std::out_of_range);

    Array p({1,2}), q({3,4,5});
    EXPECT_THROW(p.add(q), std::invalid_argument);
}

TEST(HexTest, BasicOps)
{
    Hex h1("1A"), h2("5");
    auto sum = h1.add(h2);
    EXPECT_EQ(sum.toString(),"1F");

    Hex sub("15");
    EXPECT_EQ(sub.sub(Hex("5")).toString(),"10");
}

TEST(HexTest, CompareCopy)
{
    Hex a("1F"), b("1F"), c("2A");
    EXPECT_TRUE(a.equal(b));
    EXPECT_TRUE(a.less(c));
    EXPECT_TRUE(c.greater(a));

    Hex z("FF");
    auto copy = z.copy();
    EXPECT_TRUE(copy.equal(z));
}

TEST(HexTest, ThrowsAndEdge)
{
    EXPECT_THROW(Hex("Z1"), std::invalid_argument);
    EXPECT_THROW(Hex(""), std::invalid_argument);

    Hex longA("FFFF"), one("1");
    EXPECT_EQ(longA.add(one).toString(),"10000");

    Hex big("100"), small("1");
    EXPECT_EQ(big.sub(small).toString(),"FF");
}
