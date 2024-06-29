#ifndef CLIENT_H
#define CLIENT_H

#include "user.h"
#include "book.h"

class Client : public User {
public:
    Client(const string& username, const string& password, const string& type, bool suspended)
        : User(username, password, type, suspended) {}

    bool login(const string& username, const string& password) override {
        return this->username == username && this->password == password;
    }

    void registerUser(const string& username, const string& password, const string& type) override {
        // No implementado, solo los administradores pueden registrar usuarios
    }

    void deleteUser(User** users, int& numUsers) override {
        // No implementado, solo los administradores pueden eliminar usuarios
    }

    void borrowBook(Book** books, int numBooks, int bookId) {
        // Implementación para que el cliente retire un libro
    }

    void returnBook(Book** books, int numBooks, int bookId) {
        // Implementación para que el cliente devuelva un libro
    }
};

#endif // CLIENT_H
