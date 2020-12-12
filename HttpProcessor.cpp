#include "HttpProcessor.h"

map<string, string> HttpProcessor::data;
UserManager HttpProcessor::usm;
FileType HttpProcessor::ft;

void HttpProcessor::process(char *msg, qint64 sz, string& response) {
    string request;
    string content;
    int i = 0;
    for (; i < sz && (msg[i] == ' ' || msg[i] == '\n'); ++i);
    for (; i < sz; ++i) {
        if (msg[i] == ' ') 
            break;
        request += msg[i];
    }
    ++i;
    for (; i < sz; ++i) {
        if (msg[i] == ' ') 
            break;
        content += msg[i];
    }
    string tmp;

    for (; i < sz; ++i) {
        if (msg[i] == ':') {
            i += 2;
            string tmp2;
            while (msg[i] != ',' && msg[i] != '\n') {
                tmp2 += msg[i++];
            }
            data[tmp] = tmp2;
            /* if (tmp == "Accept") cerr << tmp2 << '\n'; */
            tmp.clear();
            continue;
        }
        if (msg[i] == '\n') {
            tmp.clear();
        }
        tmp += msg[i];
    }

    if (request == "POST") {
        string usr, pwd;
        int i = 0;
        cout << "Login in...\n";
        for (; i < (int) tmp.size() && tmp[i] != '&'; ++i);
        usr = tmp.substr(0, i);
        usr = usr.substr(7);
        int j = tmp.size() - 1;
        for (; j >= 0 && tmp[j] != '&'; --j);
        i += 1;
        pwd = tmp.substr(i, j - i);
        pwd = pwd.substr(4);
        /* cerr << usr << ' ' << pwd << '\n'; */
        if (! usm.check(usr, pwd)) {
            response = HttpGenerator::redirection("/404.html", "./pages/404.html");
            /* cout << response << '\n'; */
        }
        else {
            response = HttpGenerator::redirection("/info.html", "./pages/info.html");
        }
        return; 
    }
    
    if (request == "GET") {
        if (content == "/") 
            content = "/index.html";

        content = "./pages" + content;
        /* cerr << request << ' ' << content << '\n'; */
        /* response = HttpGenerator::htmlString(content, data["Accept"]); */
        response = HttpGenerator::htmlString(content, ft.getFileType(content));
    }
}

