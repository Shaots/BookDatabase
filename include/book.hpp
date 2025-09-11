#pragma once

#include <array>
#include <format>
#include <iterator>
#include <stdexcept>
#include <string_view>

namespace bookdb {

enum class Genre { Fiction, NonFiction, SciFi, Biography, Mystery, Unknown, Count };

// Ваш код для constexpr преобразования строк в enum::Genre и наоборот здесь

constexpr Genre GenreFromString(std::string_view s) {
    // Rb tree is not necessary since there are only 6 genres, which is known in compile time
    static constexpr std::array<std::string, static_cast<int>(Genre::Count)> arr = {
        "Fiction", "NonFiction", "SciFi", "Biography", "Mystery", "Unknown"};
    auto it = std::find(arr.begin(), arr.end(), s);
    if (it == arr.end())
        return Genre::Unknown;
    else
        return static_cast<Genre>(std::distance(arr.begin(), it));
}

struct Book {
    // string_view для экономии памяти, чтобы ссылаться на оригинальную строку, хранящуюся в другом контейнере
    std::string_view author = "";
    std::string title = "";

    int year = 0;
    Genre genre;
    double rating = 0.0;
    int read_count = 0;

    constexpr Book(std::string_view genre_, std::string_view author_ = "", std::string_view title_ = "", int year_ = 0,
                   double rating_ = 0.0, int read_count_ = 0)
        : author(author_), title(title_), year(year_), genre(GenreFromString(genre_)), rating(rating_),
          read_count(read_count_) {}

    constexpr Book(Genre genre_, std::string_view author_ = "", std::string_view title_ = "", int year_ = 0,
                   double rating_ = 0.0, int read_count_ = 0)
        : author(author_), title(title_), year(year_), genre(genre_), rating(rating_),
          read_count(read_count_) {}
};
}  // namespace bookdb

namespace std {
template <>
struct formatter<bookdb::Genre, char> {
    template <typename FormatContext>
    auto format(const bookdb::Genre g, FormatContext &fc) const {
        std::string genre_str;

        // clang-format off
        using bookdb::Genre;
        switch (g) {
            case Genre::Fiction:    genre_str = "Fiction"; break;
            case Genre::Mystery:    genre_str = "Mystery"; break;
            case Genre::NonFiction: genre_str = "NonFiction"; break;
            case Genre::SciFi:      genre_str = "SciFi"; break;
            case Genre::Biography:  genre_str = "Biography"; break;
            case Genre::Unknown:    genre_str = "Unknown"; break;
            default:
                throw logic_error{"Unsupported bookdb::Genre"};
            }
        // clang-format on
        return format_to(fc.out(), "{}", genre_str);
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};

template <>
struct formatter<bookdb::Book, char> {
    template <typename FormatContext>
    auto format(const bookdb::Book book, FormatContext &fc) const {
        std::string genre_str = std::format("{}", book.genre);
        return format_to(fc.out(), "Book: Author: {}, Title: {}, Year: {}, Genre: {}, Rating: {}, Read count: {}",
                         book.author, book.title, book.year, genre_str, book.rating, book.read_count);
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};

}  // namespace std
