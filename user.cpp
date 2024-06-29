#include "user.h"
#include <fstream>
#include <sstream>

using namespace std;

User::User(const string& username, const string& password, const string& type, bool suspended)
    : username(username), password(password), type(type), suspended(suspended) {}

const string& User::getUsername() const {
    return username;
}

const string& User::getPassword() const {
    return password;
}

const string& User::getType() const {
    return type;
}

bool User::isSuspended() const {
    return suspended;
}

void User::setSuspended(bool suspended) {
    this->suspended = suspended;
}

void loadUsersFromCSV(User** users, const string& filename, int& numUsers) {
    ifstream file(filename);
    string line;
    getline(file, line); // Omitir la primera línea (encabezados)

    numUsers = 0;
    while (getline(file, line)) {
        istringstream iss(line);
        string id, username, password, type;
        bool suspended;

        getline(iss, id, ',');
        getline(iss, username, ',');
        getline(iss, password, ',');
        getline(iss, type, ',');
        iss >> suspended;

        if (type == "admin") {
            users[numUsers++] = new Admin(username, password, type, suspended);
        } else if (type == "employee") {
            users[numUsers++] = new Employee(username, password, type, suspended);
        } else if (type == "client") {
            users[numUsers++] = new Client(username, password, type, suspended);
        }
    }

    file.close();
}
