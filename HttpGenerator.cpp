#include "HttpGenerator.h"

map<int, string> statusCode = {
    {200, "OK"},
};

string HttpGenerator::generateHeader(int code, size_t contentSize, string type) {
    string ans = "HTTP/1.1 " + to_string(code) + ' ' + statusCode[code] + '\n';
    ans.append("Content-Type: " + type + ";\n");
    ans.append("Content-Length: " + to_string(contentSize) + '\n');
    ans.push_back('\n');
    return ans;
}

string HttpGenerator::htmlString(string fileDir, string type) {
    ifstream ifs(fileDir);
    string tmp, ans;
    string htmlContent;
    while (getline(ifs, tmp)) {
        htmlContent += tmp + '\n';
    }
    ifs.close();
    ans = generateHeader(200, htmlContent.size(), type) + htmlContent + '\n';
    return ans;
}
