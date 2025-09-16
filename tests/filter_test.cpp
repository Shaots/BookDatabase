#include <gtest/gtest.h>

#include <format>
#include <print>

#include "book.hpp"
#include "book_database.hpp"
#include "filters.hpp"
using namespace bookdb;

namespace {
BookDatabase<> create() {
    return BookDatabase{{Genre::Fiction, "Lev Tolstoy", "Anna Karenina", 1877, 0.5, 8},
                        {Genre::Fiction, "Fyodor Dostoevsky", "Crime and Punisment", 1867, 0.5, 10},
                        {Genre::Fiction, "Fyodor Dostoevsky", "The Brothers Karamazov", 1880, 0.6, 20},
                        {Genre::SciFi, "George Orwell", "1984", 1949, 0.4, 190},
                        {Genre::Biography, "Jane Austen", "Pride and Prejudice", 1813, 4.7, 178},
                        {Genre::Biography, "J.D. Salinger", "The Catcher in the Rye", 1951, 4.3, 112}};
}
}  // namespace

TEST(TestFilter, YearBetween) {
    BookDatabase db = create();
    auto res = filterBooks(db.begin(), db.end(), YearBetween(1800, 1900));
    EXPECT_EQ(res.size(), 4);
    EXPECT_EQ(res[0].get().title, "Anna Karenina");
    EXPECT_EQ(res[1].get().title, "Crime and Punisment");
    EXPECT_EQ(res[2].get().title, "The Brothers Karamazov");
    EXPECT_EQ(res[3].get().title, "Pride and Prejudice");
}

TEST(TestFilter, RatingAbove) {
    BookDatabase db = create();
    auto res = filterBooks(db.begin(), db.end(), RatingAbove(1.0));
    EXPECT_EQ(res.size(), 2);
    EXPECT_EQ(res[0].get().title, "Pride and Prejudice");
    EXPECT_EQ(res[1].get().title, "The Catcher in the Rye");
}

TEST(TestFilter, GenreIs) {
    BookDatabase db = create();
    auto res = filterBooks(db.begin(), db.end(), GenreIs(Genre::Biography));
    EXPECT_EQ(res.size(), 2);
    EXPECT_EQ(res[0].get().title, "Pride and Prejudice");
    EXPECT_EQ(res[1].get().title, "The Catcher in the Rye");
}

TEST(TestFilter, all_of) {
    BookDatabase db = create();
    auto res = filterBooks(db.begin(), db.end(), all_of(GenreIs(Genre::Biography), RatingAbove(1.0)));
    EXPECT_EQ(res.size(), 2);
    EXPECT_EQ(res[0].get().title, "Pride and Prejudice");
    EXPECT_EQ(res[1].get().title, "The Catcher in the Rye");
}

TEST(TestFilter, any_of) {
    BookDatabase db = create();
    auto res = filterBooks(db.begin(), db.end(), any_of(GenreIs(Genre::Fiction), YearBetween(1800, 1950)));
    EXPECT_EQ(res.size(), 5);
    EXPECT_EQ(res[0].get().title, "Anna Karenina");
    EXPECT_EQ(res[1].get().title, "Crime and Punisment");
    EXPECT_EQ(res[2].get().title, "The Brothers Karamazov");
    EXPECT_EQ(res[3].get().title, "1984");
    EXPECT_EQ(res[4].get().title, "Pride and Prejudice");
}