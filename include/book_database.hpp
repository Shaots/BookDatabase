#pragma once

#include <initializer_list>
#include <print>
#include <span>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

#include "book.hpp"
#include "concepts.hpp"
#include "heterogeneous_lookup.hpp"

namespace bookdb {

template <BookContainerLike BookContainer = std::vector<Book>>
class BookDatabase {
public:
    // Type aliases
    using value_type = BookContainer::value_type;
    using size_type = BookContainer::size_type;
    using reference = BookContainer::reference;
    using const_reference = BookContainer::const_reference;
    using iterator = BookContainer::iterator;
    using const_iterator = BookContainer::const_iterator;

    // Ваш код здесь

    using AuthorContainer = std::unordered_set<std::string, TransparentStringHash>;

    BookDatabase() = default;

    BookDatabase(std::initializer_list<Book> list) : books_(list) {
        for (Book &book : books_) {
            extractAuthor(book);
        }
    }

    // Standard container interface methods

    // Capacity
    size_type size() const noexcept { return books_.size(); }

    size_type capacity() const noexcept { return books_.capacity(); }

    bool empty() const noexcept { return books_.empty(); }

    void reserve(size_type new_cap) { books_.reserve(new_cap); }

    void shrink_to_fit() { books_.shrink_to_fit(); }

    // Iterators
    iterator begin() noexcept { return books_.begin(); }

    const_iterator begin() const noexcept { return books_.begin(); }

    const_iterator cbegin() const noexcept { return books_.cbegin(); }

    iterator end() { return books_.end(); }

    const_iterator end() const noexcept { return books_.end(); }

    const_iterator cend() const noexcept { return books_.cend(); }

    // Element access
    reference operator[](size_type pos) noexcept { return books_[pos]; }

    const_reference operator[](size_type pos) const noexcept { return books_[pos]; }

    reference at(size_type pos) { return books_.at(pos); }

    const_reference at(size_type pos) const { return books_.at(pos); }

    reference front() noexcept { return books_.front(); }

    const_reference front() const noexcept { return books_.front(); }

    reference back() noexcept { return books_.back(); }

    const_reference back() const noexcept { return books_.back(); }

    // Modifiers
    void Clear() {
        books_.clear();
        authors_.clear();
    }

    void PushBack(const Book &book) {
        extractAuthor(book);
        books_.push_back(book);
    }

    void PushBack(Book &&book) {
        extractAuthor(book);
        books_.push_back(std::move(book));
    }

    template <class... Args>
    reference EmplaceBack(Args &&...args) {
        auto &ref = books_.emplace_back(std::forward<Args>(args)...);
        extractAuthor(ref);
        return ref;
    }

    // For reading
    std::span<Book> GetBooks() noexcept { return books_; }

    std::span<const Book> GetBooks() const noexcept { return books_; }

    const AuthorContainer &GetAuthors() const noexcept { return authors_; }

private:
    BookContainer books_;
    AuthorContainer authors_;

    void extractAuthor(Book &book) {
        auto res = authors_.emplace(book.author);
        book.author = *(res.first);
    }
};

}  // namespace bookdb

namespace std {
template <>
struct formatter<bookdb::BookDatabase<std::vector<bookdb::Book>>> {
    template <typename FormatContext>
    auto format(const bookdb::BookDatabase<std::vector<bookdb::Book>> &db, FormatContext &fc) const {
        format_to(fc.out(), "BookDatabase (size = {}): ", db.size());

        format_to(fc.out(), "Books:\n");
        for (const auto &book : db.GetBooks()) {
            format_to(fc.out(), "- {}\n", book);
        }

        format_to(fc.out(), "Authors:\n");
        for (const auto &author : db.GetAuthors()) {
            format_to(fc.out(), "- {}\n", author);
        }
        return fc.out();
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};
}  // namespace std
