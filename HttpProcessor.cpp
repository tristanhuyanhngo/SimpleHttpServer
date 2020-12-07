#include "HttpProcessor.h"

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
    
    if (request == "GET") {
        content = "./pages" + content;
        cerr << request << ' ' << content << '\n';
        response = HttpGenerator::htmlString(content);
    }

}

