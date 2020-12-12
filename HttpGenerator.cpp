#include "HttpGenerator.h"

map<int, string> statusCode = {
    {200, "OK"},
};

string HttpGenerator::header(int code, size_t contentSize, string type) {
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
    ans = header(200, htmlContent.size(), type) + htmlContent + '\n';
    return ans;
}

string HttpGenerator::redirection(string location, string fileDir) {
    ifstream ifs(fileDir);
    string tmp, ans;
    string htmlContent;
    while (getline(ifs, tmp)) {
        htmlContent += tmp + '\n';
    }
    ifs.close();
    return "HTTP/1.1 303 See Other\nLocation: " + location + '\n' + htmlContent + '\n';
}
