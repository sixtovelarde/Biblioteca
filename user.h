#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
protected:
    string username;
    string password;
    string type;
    bool suspended;

public:
    User(const string& username, const string& password, const string& type, bool suspended);
    virtual ~User() = default;

    const string& getUsername() const;
    const string& getPassword() const;
    const string& getType() const;
    bool isSuspended() const;
    void setSuspended(bool suspended);

    virtual bool login(const string& username, const string& password) = 0;
    virtual void registerUser(const string& username, const string& password, const string& type) = 0;
    virtual void deleteUser(User** users, int& numUsers) = 0;
};

void loadUsersFromCSV(User** users, const string& filename, int& numUsers);

#endif // USER_H
