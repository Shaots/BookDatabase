#include "comparators.hpp"
#include "statsistics.hpp"
#include <algorithm>
#include <gtest/gtest.h>
#include <string>
#include <string_view>

using namespace bookdb;
using namespace std::literals;

BookDatabase<> create() {
    return BookDatabase{{Genre::Fiction, "Lev Tolstoy", "Anna Karenina", 1877, 0.5, 8},
                        {Genre::Fiction, "Fyodor Dostoevsky", "Crime and Punisment", 1867, 0.5, 10},
                        {Genre::Fiction, "Fyodor Dostoevsky", "The Brothers Karamazov", 1880, 0.6, 20},
                        {Genre::SciFi, "George Orwell", "1984", 1949, 0.4, 190},
                        {Genre::Biography, "Jane Austen", "Pride and Prejudice", 1813, 4.7, 178},
                        {Genre::Biography, "J.D. Salinger", "The Catcher in the Rye", 1951, 4.3, 112}};
}

TEST(TestStatic, Histogram) {
    BookDatabase db = create();
    auto hist = buildAuthorHistogramFlat(db);
    EXPECT_EQ(hist["Lev Tolstoy"sv], 1);
    EXPECT_EQ(hist["Fyodor Dostoevsky"sv], 2);
    EXPECT_EQ(hist["George Orwell"sv], 1);
    EXPECT_EQ(hist["Jane Austen"sv], 1);
    EXPECT_EQ(hist["J.D. Salinger"sv], 1);
}

TEST(TestStatic, GenreRatings) {
    BookDatabase db = create();
    auto rating = calculateGenreRatings(db);
    // std::cout << hist[Genre::Fiction].rating <<  " " << hist[Genre::Fiction].counter << std::endl;
    EXPECT_DOUBLE_EQ(rating[Genre::Fiction], 1.6 / 3);
    EXPECT_DOUBLE_EQ(rating[Genre::SciFi], 0.4);
    EXPECT_DOUBLE_EQ(rating[Genre::Biography], 4.5);
}

TEST(TestStatic, AverageRating) {
    BookDatabase db = create();
    double rating = calculateAverageRating(db);
    EXPECT_DOUBLE_EQ(rating, 11.0 / 6);

    db = {};
    EXPECT_DOUBLE_EQ(calculateAverageRating(db), 0);
}

TEST(TestStatic, Sample) {
    BookDatabase db = create();
    EXPECT_EQ(sampleRandomBooks(db, db.size() - 1).size(), db.size() - 1);
    EXPECT_EQ(sampleRandomBooks(db, db.size() + 10).size(), db.size());
    EXPECT_EQ(sampleRandomBooks(db, 1).size(), 1);
}

TEST(TestStatic, getTop) {
    BookDatabase db = create();
    auto res = getTopNBy(db, 3, comp::GreaterByYear{});
    bool b = std::all_of(res.begin(), res.end(), [](const auto& book){return book.get().year >= 1880;});
    EXPECT_EQ(b, true);

    BookDatabase db2 = create();
    int minYear = std::min_element(db2.begin(), db2.end(), [](auto it1, auto it2){return it1.year < it2.year;})->year;
    EXPECT_EQ(minYear, 1813);
    auto res2 = getTopNBy(db2, 10, comp::GreaterByYear{});
    b = std::all_of(res.begin(), res.end(), [minYear](const auto& book){return book.get().year >= minYear;});
    EXPECT_EQ(res2.size(), 6);
    EXPECT_EQ(b, true);
}