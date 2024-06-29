#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
#include "book.h"

class Admin : public User {
public:
    Admin(const string& username, const string& password, const string& type, bool suspended)
        : User(username, password, type, suspended) {}

    bool login(const string& username, const string& password) override {
        return this->username == username && this->password == password;
    }

    void registerUser(const string& username, const string& password, const string& type) override {
        // Implementación para registrar un nuevo usuario
    }

    void deleteUser(User** users, int& numUsers) override {
        // Implementación para eliminar un usuario
    }

    void addBook(Book** books, int& numBooks, const string& title, const string& author) {
        // Implementación para agregar un nuevo libro
    }

    void modifyBook(Book** books, int numBooks, int bookId, const string& title, const string& author, bool available) {
        // Implementación para modificar un libro existente
    }

    void deleteBook(Book** books, int& numBooks, int bookId) {
        // Implementación para eliminar un libro
    }
};

#endif // ADMIN_H
