#pragma once

#include <functional>

#include "book.hpp"
#include "concepts.hpp"

namespace bookdb {

auto YearBetween(const int minYear, const int maxYear) {
    return [=](const Book &book) { return minYear <= book.year && book.year <= maxYear; };
}

auto RatingAbove(const double threashold) {
    return [=](const Book &book) { return book.rating >= threashold; };
}

auto GenreIs(const Genre genre) {
    return [=](const Book &book) { return book.genre == genre; };
}

template <typename... Args>
auto all_of(Args... args) {
    return [=](const Book &book) -> bool { return (args(book) && ...); };
}

template <typename... Args>
auto any_of(Args... args) {
    return [=](const Book &book) -> bool { return (args(book) || ...); };
}

template <BookIterator T, BookPredicate P>
auto filterBooks(const T &begin, const T &end, const P &predictor) {
    std::vector<std::reference_wrapper<const Book>> res;
    res.reserve(end - begin);
    for (T it = begin; it != end; ++it) {
        if (predictor(*it)) {
            res.push_back(*it);
        }
    }
    return res;
}

}  // namespace bookdb