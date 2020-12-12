#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <map>
#include <fstream>

using namespace std;

class UserManager {
private:
    map<string, string> users;
public:
    UserManager();
    bool check(string &usr, string &pwd);
};

#endif // USERMANAGER_H
