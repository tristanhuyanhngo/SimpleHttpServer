#ifndef HTTPGENERATOR_H
#define HTTPGENERATOR_H 

#include <QString>
#include <string>
#include <fstream>
#include <map>

using namespace std;

extern map<int, string> statusCode;

/* A helper class for generating http messages */

class HttpGenerator {
    private:
        static string generateHeader(int code, size_t contentSize);
    public:

        /* Read and display html file */
        static string htmlString(string fileDir);
};

#endif /* HTTPGENERATOR_H */
