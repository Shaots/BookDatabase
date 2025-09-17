#include <algorithm>

#include "book_database.hpp"
#include "comparators.hpp"
#include "filters.hpp"
#include "statsistics.hpp"

using namespace bookdb;

int main() {
    // Create a book database
    BookDatabase<std::vector<Book>> db;

    // Add some books
    db.EmplaceBack(Genre::SciFi, "George Orwell", "1984", 1949, 4., 190);
    db.EmplaceBack(Genre::Fiction, "George Orwell", "Animal Farm", 1945, 4.4, 143);
    db.EmplaceBack(Genre::Fiction, "F. Scott Fitzgerald", "The Great Gatsby", 1925, 4.5, 120);
    db.EmplaceBack(Genre::Fiction, "Harper Lee", "To Kill a Mockingbird", 1960, 4.8, 156);
    db.EmplaceBack(Genre::Fiction, "Jane Austen", "Pride and Prejudice", 1813, 4.7, 178);
    db.EmplaceBack(Genre::Fiction, "J.D. Salinger", "The Catcher in the Rye", 1951, 4.3, 112);
    db.EmplaceBack(Genre::SciFi, "Aldous Huxley", "Brave New World", 1932, 4.5, 98);
    db.EmplaceBack(Genre::Fiction, "Charlotte Brontë", "Jane Eyre", 1847, 4.6, 110);
    db.EmplaceBack(Genre::Fiction, "J.R.R. Tolkien", "The Hobbit", 1937, 4.9, 203);
    db.EmplaceBack(Genre::Fiction, "William Golding", "Lord of the Flies", 1954, 4.2, 89);
    std::print("Books: {}\n\n", db);

    // Sorts
    std::sort(db.begin(), db.end(), comp::LessByAuthor{});
    std::print("Books sorted by author: {}\n\n==================\n", db);

    std::sort(db.begin(), db.end(), comp::GreaterByReadCount{});
    std::print("Books sorted by popularity: {}\n\n==================\n", db);

    // Author histogram
    auto histogram = buildAuthorHistogramFlat(db);
    // std::print("Author histogram: {}", histogram);

    // Ratings
    auto genreRatings = calculateGenreRatings(db);
    // std::print("\n\nAverage ratings by genres: {}\n", genreRatings);

    auto avrRating = calculateAverageRating(db);
    std::print("Average books rating in library: {}\n", avrRating);

    // Filters
    auto filtered = filterBooks(db.begin(), db.end(), all_of(YearBetween(1900, 1999), RatingAbove(4.5)));
    std::print("\n\nBooks from the 20th century with rating ≥ 4.5:\n");

    // Top 3 books
    auto topBooks = getTopNBy(db, 3, comp::GreaterByRating{});
    std::print("\n\nTop 3 books by rating:\n");
    std::for_each(topBooks.cbegin(), topBooks.cend(), [](const auto &v) { std::print("{}\n", v.get()); });

    auto orwellBookIt = std::find_if(db.begin(), db.end(), [](const auto &v) { return v.author == "George Orwell"; });
    if (orwellBookIt != db.end()) {
        std::print("\n\nTransparent lookup by authors. Found Orwell's book: {}\n", *orwellBookIt);
    }

    return 0;
}