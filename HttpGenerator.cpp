#include "HttpGenerator.h"

map<int, string> statusCode = {
    {200, "OK"},
};

string HttpGenerator::generateHeader(int code, size_t contentSize) {
    string ans = "HTTP/1.1 " + to_string(code) + ' ' + statusCode[200] + '\n';
    ans.append("Content-Type: text/html;\n");
    ans.append("Content-Length: " + to_string(contentSize) + '\n');
    ans.push_back('\n');
    return ans;
}

string HttpGenerator::htmlString(string fileDir) {
    ifstream ifs(fileDir);
    string tmp, ans;
    string htmlContent;
    while (getline(ifs, tmp)) {
        htmlContent += tmp + '\n';
    }
    ifs.close();
    ans = generateHeader(200, htmlContent.size()) + htmlContent + '\n';
    return ans;
}
