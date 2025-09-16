#include <gtest/gtest.h>

#include <format>
#include <print>

#include "book.hpp"
#include "book_database.hpp"

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

TEST(TestComponentName, formatterBook) {
    Book book(Genre::Fiction);
    book.author = "Lev Tolstoy";
    book.title = "Anna Karenina";
    book.year = 1877;
    book.rating = 0.5;
    book.read_count = 8;

    std::string book_str = std::format("{}", book);
    std::println("{}", book_str);
}

TEST(TestDataBase, capacity) {
    // Initializer list
    BookDatabase db{{Genre::Fiction, "Lev Tolstoy", "Anna Karenina", 1877, 0.5, 8},
                    {Genre::Fiction, "Fyodor Dostoevsky", "Crime and Punisment", 1867, 0.5, 10}};

    EXPECT_EQ(db.size(), 2);
    EXPECT_GE(db.capacity(), 2);
    EXPECT_EQ(db.empty(), 0);

    db.reserve(10);
    EXPECT_EQ(db.size(), 2);
    EXPECT_EQ(db.capacity(), 10);

    db.shrink_to_fit();
    EXPECT_EQ(db.size(), 2);
    EXPECT_EQ(db.capacity(), 2);
}

TEST(TestDataBase, iterator) {
    BookDatabase db{{Genre::Fiction, "Lev Tolstoy", "Anna Karenina", 1877, 0.5, 8},
                    {Genre::Fiction, "Fyodor Dostoevsky", "Crime and Punisment", 1867, 0.5, 10}};
    auto it1 = db.begin();
    EXPECT_EQ(it1->genre, Genre::Fiction);
    EXPECT_EQ(it1->author, "Lev Tolstoy");
    EXPECT_EQ(it1->title, "Anna Karenina");
    EXPECT_EQ(it1->year, 1877);
    EXPECT_EQ(it1->rating, 0.5);
    EXPECT_EQ(it1->read_count, 8);

    auto it2 = ++it1;
    EXPECT_EQ(it2->genre, Genre::Fiction);
    EXPECT_EQ(it2->author, "Fyodor Dostoevsky");
    EXPECT_EQ(it2->title, "Crime and Punisment");
    EXPECT_EQ(it2->year, 1867);
    EXPECT_EQ(it2->rating, 0.5);
    EXPECT_EQ(it2->read_count, 10);

    EXPECT_EQ(db.end() - db.begin(), 2);
}

TEST(TestDataBase, elementAccess) {
    BookDatabase db{{Genre::Fiction, "Lev Tolstoy", "Anna Karenina", 1877, 0.5, 8},
                    {Genre::Fiction, "Fyodor Dostoevsky", "Crime and Punisment", 1867, 0.5, 10}};
    EXPECT_EQ(db[0].genre, Genre::Fiction);
    EXPECT_EQ(db[0].author, "Lev Tolstoy");
    EXPECT_EQ(db[0].title, "Anna Karenina");
    EXPECT_EQ(db[0].year, 1877);
    EXPECT_EQ(db[0].rating, 0.5);
    EXPECT_EQ(db[0].read_count, 8);

    EXPECT_EQ(db.at(1).genre, Genre::Fiction);
    EXPECT_EQ(db.at(1).author, "Fyodor Dostoevsky");
    EXPECT_EQ(db.at(1).title, "Crime and Punisment");
    EXPECT_EQ(db.at(1).year, 1867);
    EXPECT_EQ(db.at(1).rating, 0.5);
    EXPECT_EQ(db.at(1).read_count, 10);

    EXPECT_EQ(&(db.front()), &(db[0]));
    EXPECT_EQ(&(db.back()), &(db[1]));
}

TEST(TestDataBase, Modifiers) {
    BookDatabase db;
    db.PushBack({Genre::Fiction, "Lev Tolstoy", "Anna Karenina", 1877, 0.5, 8});

    EXPECT_EQ(db.size(), 1);
    EXPECT_EQ(db[0].genre, Genre::Fiction);
    EXPECT_EQ(db[0].author, "Lev Tolstoy");
    EXPECT_EQ(db[0].title, "Anna Karenina");
    EXPECT_EQ(db[0].year, 1877);
    EXPECT_EQ(db[0].rating, 0.5);
    EXPECT_EQ(db[0].read_count, 8);

    auto bk = db.EmplaceBack(Genre::Fiction, "Fyodor Dostoevsky", "Crime and Punisment", 1867, 0.5, 10);
    EXPECT_EQ(db.size(), 2);
    EXPECT_EQ(bk.genre, Genre::Fiction);
    EXPECT_EQ(bk.author, "Fyodor Dostoevsky");
    EXPECT_EQ(bk.title, "Crime and Punisment");
    EXPECT_EQ(bk.year, 1867);
    EXPECT_EQ(bk.rating, 0.5);
    EXPECT_EQ(bk.read_count, 10);

    auto authors = db.GetAuthors();
    EXPECT_EQ(authors.size(), 2);

    db.Clear();
    EXPECT_EQ(db.GetAuthors().empty(), true);
    EXPECT_EQ(db.GetBooks().size(), 0);
}

TEST(TestDataBase, GetAuthors) {
    BookDatabase db{{Genre::Fiction, "Lev Tolstoy", "Anna Karenina", 1877, 0.5, 8},
                    {Genre::Fiction, "Fyodor Dostoevsky", "Crime and Punisment", 1867, 0.5, 10},
                    {Genre::Fiction, "Fyodor Dostoevsky", "The Brothers Karamazov", 1880, 0.6, 20}};
    auto authors = db.GetAuthors();
    EXPECT_EQ(authors.size(), 2);
    std::cout << authors.size() << std::endl;
}