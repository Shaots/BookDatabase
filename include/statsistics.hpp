#pragma once

#include <algorithm>
#include <cstddef>
#include <flat_map>
#include <iterator>
#include <print>
#include <random>
#include <stdexcept>
#include <string_view>

#include "book.hpp"
#include "book_database.hpp"

namespace bookdb {

template <BookContainerLike T, typename Comparator = TransparentStringLess>
auto buildAuthorHistogramFlat(const BookDatabase<T> &db, Comparator comp = {}) {
    std::flat_map<std::string_view, size_t, Comparator> hist;
    for (const auto &book : db) {
        ++hist[std::ref(book.author)];
    }
    return hist;
}

template <BookContainerLike T>
auto calculateGenreRatings(const BookDatabase<T> &db) {
    struct GenreInfo {
        size_t count = 0;
        double rating = 0.0;
    };
    std::flat_map<Genre, GenreInfo> mapGenreInfo;
    for (auto book : db) {
        ++mapGenreInfo[book.genre].count;
        mapGenreInfo[book.genre].rating += book.rating;
    }

    std::flat_map<Genre, double> res;
    for (auto it = mapGenreInfo.cbegin(); it != mapGenreInfo.cend(); ++it) {
        res.emplace(it->first, it->second.rating / it->second.count);
    }
    return res;
}

template <BookContainerLike T>
double calculateAverageRating(const BookDatabase<T> &db) {
    return db.empty() ? 0 : std::accumulate(db.begin(), db.end(), 0.0, [](const double sum, const Book &book) {
                                return sum + book.rating;
                            }) / db.size();
}

template <BookContainerLike T>
auto sampleRandomBooks(const BookDatabase<T> &db, size_t N) {
    std::vector<std::reference_wrapper<const Book>> res;
    std::sample(db.begin(), db.end(), std::back_inserter(res), N, std::mt19937{std::random_device{}()});
    return res;
}

template <BookContainerLike T, typename Comparator>
auto getTopNBy(BookDatabase<T> &db, size_t N, Comparator comp) {
    std::vector<std::reference_wrapper<const Book>> res;
    size_t sz = std::min(N, db.size());
    std::nth_element(db.begin(), db.begin() + sz, db.end(), comp);
    res = {db.begin(), db.begin() + sz};
    return res;
}



}  // namespace bookdb
