#include "book.hpp"
#include <gtest/gtest.h>

using namespace bookdb;

TEST(TestComponentName, Constructor) {
    Book b1(Genre::Fiction);
    EXPECT_EQ(b1.genre, Genre::Fiction);

    Book b2("Fiction");
    EXPECT_EQ(b2.genre, Genre::Fiction);

    Book b3("NonFiction");
    EXPECT_EQ(b3.genre, Genre::NonFiction);

    Book b4("SciFi");
    EXPECT_EQ(b4.genre, Genre::SciFi);

    Book b5("Biography");
    EXPECT_EQ(b5.genre, Genre::Biography);

    Book b6("Mystery");
    EXPECT_EQ(b6.genre, Genre::Mystery);

    Book b7("Unknown");
    EXPECT_EQ(b7.genre, Genre::Unknown);

    Book b8("ABCDE");
    EXPECT_EQ(b8.genre, Genre::Unknown);
}