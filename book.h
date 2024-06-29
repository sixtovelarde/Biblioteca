#ifndef BOOK_H
#define BOOK_H

#include <string>

using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    bool available;

public:
    Book(int id, const string& title, const string& author, bool available);
    int getId() const;
    const string& getTitle() const;
    const string& getAuthor() const;
    bool isAvailable() const;
    void setAvailable(bool available);
};

void loadBooksFromCSV(Book** books, const string& filename, int& numBooks);

#endif // BOOK_H
