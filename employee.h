#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "user.h"
#include "book.h"

class Employee : public User {
public:
    Employee(const string& username, const string& password, const string& type, bool suspended)
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

#endif // EMPLOYEE_H
