#include "book.h"
#include <fstream>
#include <sstream>

using namespace std;

Book::Book(int id, const string& title, const string& author, bool available)
    : id(id), title(title), author(author), available(available) {}

int Book::getId() const {
    return id;
}

const string& Book::getTitle() const {
    return title;
}

const string& Book::getAuthor() const {
    return author;
}

bool Book::isAvailable() const {
    return available;
}

void Book::setAvailable(bool available) {
    this->available = available;
}

void loadBooksFromCSV(Book** books, const string& filename, int& numBooks) {
    ifstream file(filename);
    string line;
    getline(file, line); // Omitir la primera línea (encabezados)

    numBooks = 0;
    while (getline(file, line)) {
        istringstream iss(line);
        string id, title, author, available;

        getline(iss, id, ',');
        getline(iss, title, ',');
        getline(iss, author, ',');
        getline(iss, available, ',');

        books[numBooks++] = new Book(stoi(id), title, author, available == "true");
    }

    file.close();
}
