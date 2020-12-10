#include "HttpProcessor.h"

map<string, string> HttpProcessor::data;

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
            /* m[tmp] = tmp2; */
            /* cerr << tmp << ' ' << tmp2 << '\n'; */
            data[tmp] = tmp2;
            if (tmp == "Accept") cerr << tmp2 << '\n';
            tmp.clear();
            continue;
        }
        if (msg[i] == '\n') {
            tmp.clear();
        }
        tmp += msg[i];
    }
    
    if (request == "GET") {
        content = "./pages" + content;
        cerr << request << ' ' << content << '\n';
        /* response = HttpGenerator::htmlString(content, data["Accept"]); */
        response = HttpGenerator::htmlString(content, "*/*");
    }

}

