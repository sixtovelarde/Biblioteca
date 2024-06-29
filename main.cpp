#include <iostream>
#include <fstream>
#include <cstring>
#include "user.h"
#include "admin.h"
#include "employee.h"
#include "client.h"
#include "book.h"

using namespace std;

const int MAX_USERS = 100;
const int MAX_BOOKS = 100;

int main() {
    User* users[MAX_USERS];
    Book* books[MAX_BOOKS];
    int numUsers = 0, numBooks = 0;

    // Cargar usuarios y libros desde los archivos CSV
    loadUsersFromCSV(users, "bin/users.csv", numUsers);
    loadBooksFromCSV(books, "bin/books.csv", numBooks);

    string username, password;
    cout << "Ingrese su nombre de usuario: ";
    cin >> username;
    cout << "Ingrese su contraseña: ";
    cin >> password;

    User* currentUser = nullptr;
    for (int i = 0; i < numUsers; i++) {
        if (users[i]->getUsername() == username && users[i]->getPassword() == password) {
            currentUser = users[i];
            break;
        }
    }

    if (currentUser == nullptr) {
        cout << "Credenciales inválidas." << endl;
        return 1;
    }

    while (true) {
        if (dynamic_cast<Admin*>(currentUser) != nullptr) {
            adminMenu(currentUser, users, numUsers, books, numBooks);
        } else if (dynamic_cast<Employee*>(currentUser) != nullptr) {
            employeeMenu(currentUser, books, numBooks);
        } else if (dynamic_cast<Client*>(currentUser) != nullptr) {
            clientMenu(currentUser, books, numBooks);
        }
    }

    return 0;
}
