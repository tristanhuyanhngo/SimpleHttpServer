#ifndef FILETYPE_H
#define FILETYPE_H
#include <map>
#include <string>
#include <iostream>

using namespace std;

/* contain a list of mime filetypes */

class FileType {
private:
    static map<string, string> types;
public:
    FileType();
    string getFileType(string &fileName);
};

#endif // FILETYPE_H
