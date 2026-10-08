#include <gtest/gtest.h>

#include "include/TVector.h"

TEST(TVectorTest, DefaultConstructor) {
    TVector<int> vector;

    EXPECT_EQ(vector.size(), 0);
    EXPECT_EQ(vector.capacity(), 0);
    EXPECT_TRUE(vector.empty());
}

TEST(TVectorTest, SizeConstructor) {
    TVector<int> vector(5);

    EXPECT_EQ(vector.size(), 5);
    EXPECT_EQ(vector.capacity(), 5);
    EXPECT_TRUE(vector.empty() == false);

    for (std::size_t i = 0; i < vector.size(); ++i) {
        EXPECT_EQ(vector[i], 0);
    }
}

TEST(TVectorTest, InitializerListConstructor) {
    TVector<int> vector{1, 2, 3, 4, 5};

    ASSERT_EQ(vector.size(), 5);

    EXPECT_EQ(vector[0], 1);
    EXPECT_EQ(vector[1], 2);
    EXPECT_EQ(vector[2], 3);
    EXPECT_EQ(vector[3], 4);
    EXPECT_EQ(vector[4], 5);
}

TEST(TVectorTest, PushBack) {
    TVector<int> vector;

    vector.push_back(10);
    vector.push_back(20);
    vector.push_back(30);

    ASSERT_EQ(vector.size(), 3);

    EXPECT_EQ(vector[0], 10);
    EXPECT_EQ(vector[1], 20);
    EXPECT_EQ(vector[2], 30);
}

TEST(TVectorTest, PopBack) {
    TVector<int> vector{1, 2, 3};

    vector.pop_back();

    EXPECT_EQ(vector.size(), 2);
    EXPECT_EQ(vector[0], 1);
    EXPECT_EQ(vector[1], 2);
}

TEST(TVectorTest, Reserve) {
    TVector<int> vector;

    vector.reserve(100);

    EXPECT_EQ(vector.capacity(), 100);
    EXPECT_EQ(vector.size(), 0);

    vector.push_back(42);

    EXPECT_EQ(vector.size(), 1);
    EXPECT_EQ(vector[0], 42);
    EXPECT_EQ(vector.capacity(), 100);
}

TEST(TVectorTest, AtThrows) {
    TVector<int> vector{1, 2, 3};

    EXPECT_THROW(vector.at(3), std::out_of_range);
}

TEST(TVectorTest, CopyConstructor) {
    TVector<int> original{1, 2, 3};
    TVector<int> copy(original);

    EXPECT_EQ(copy.size(), original.size());

    for (std::size_t i = 0; i < original.size(); ++i) {
        EXPECT_EQ(copy[i], original[i]);
    }

    copy[0] = 100;

    EXPECT_EQ(original[0], 1);
    EXPECT_EQ(copy[0], 100);
}

TEST(TVectorTest, CopyAssignment) {
    TVector<int> original{1, 2, 3};
    TVector<int> copy;

    copy = original;

    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy[0], 1);
    EXPECT_EQ(copy[1], 2);
    EXPECT_EQ(copy[2], 3);
}

TEST(TVectorTest, MoveConstructor) {
    TVector<int> original{1, 2, 3};

    TVector<int> moved(std::move(original));

    EXPECT_EQ(moved.size(), 3);
    EXPECT_EQ(moved[0], 1);
    EXPECT_EQ(moved[1], 2);
    EXPECT_EQ(moved[2], 3);

    EXPECT_EQ(original.size(), 0);
    EXPECT_EQ(original.capacity(), 0);
}

TEST(TVectorTest, Clear) {
    TVector<int> vector{1, 2, 3};

    vector.clear();

    EXPECT_EQ(vector.size(), 0);
    EXPECT_TRUE(vector.empty());

    // clear() не обязан уменьшать capacity.
    EXPECT_EQ(vector.capacity(), 3);
}

TEST(TVectorTest, FrontAndBack) {
    TVector<int> vector{10, 20, 30};

    EXPECT_EQ(vector.front(), 10);
    EXPECT_EQ(vector.back(), 30);
}