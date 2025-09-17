#pragma once

#include "book.hpp"
#include <concepts>
#include <iterator>

namespace bookdb {

template <typename T>
concept BookContainerLike = requires(T t) {
    typename T::value_type;
    typename T::size_type;
    typename T::reference;
    typename T::const_reference;
    typename T::iterator;
    typename T::const_iterator;

    { t.begin() } -> std::forward_iterator;
    { t.end() } -> std::forward_iterator;
    { t.size() } -> std::convertible_to<std::size_t>;
};

template <typename T>
concept BookIterator = std::is_same<Book, typename std::iterator_traits<T>::value_type>::value;

template <typename S, typename I>
concept BookSentinel = std::sentinel_for<S, I>;

template <typename P>
concept BookPredicate = std::predicate<P, const Book &>;

template <typename C>
concept BookComparator = std::predicate<C, const Book &, const Book &>;

}  // namespace bookdb