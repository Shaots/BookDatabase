#pragma once

#include "book.hpp"
#include <functional>

namespace bookdb::comp {

struct LessByAuthor {
    using is_transparent = void;

    bool operator()(const Book &book1, const Book &book2) { return book1.author < book2.author; }

    bool operator()(const Book &book, std::string_view author) { return book.author < author; }

    bool operator()(std::string_view author, const Book &book) { return author < book.author; }
};

struct LessByTitle {
    using is_transparent = void;
    
    bool operator()(const Book &book1, const Book &book2) { return book1.title < book2.title; }

    bool operator()(const Book &book, std::string_view title) { return book.title < title; }

    bool operator()(std::string_view title, const Book &book) { return title < book.title; }
};

struct LessByYear {
    using is_transparent = void;
    
    bool operator()(const Book &book1, const Book &book2) { return book1.year < book2.year; }

    bool operator()(const Book &book, int year) { return book.year < year; }

    bool operator()(int year, const Book &book) { return year < book.year; }
};

struct LessByRating {
    using is_transparent = void;
    
    bool operator()(const Book &book1, const Book &book2) { return book1.rating < book2.rating; }

    bool operator()(const Book &book, double rating) { return book.rating < rating; }

    bool operator()(double rating, const Book &book) { return rating < book.rating; }
};


struct LessByReadCount {
    using is_transparent = void;
    
    bool operator()(const Book &book1, const Book &book2) { return book1.read_count < book2.read_count; }

    bool operator()(const Book &book, int read_count) { return book.read_count < read_count; }

    bool operator()(int read_count, const Book &book) { return read_count < book.read_count; }
};

}  // namespace bookdb::comp