#include "usermanager.h"

UserManager::UserManager() {
    ifstream ifs("./data/users.csv");
    string s;
    while (getline(ifs, s)) {
        int i;
        for (i = 0; i < (int) s.size() && s[i] != ','; ++i);
        users[s.substr(0, i)] = s.substr(i + 1);
        /* cout << s.substr(0, i) << ' ' << s.substr(i + 1); */
    }
}

bool UserManager::check(string &usr, string &pwd) {
    return users[usr] == pwd;
}

