#ifndef HTTPPROCESSOR_H
#define HTTPPROCESSOR_H 

#include <cstring>
#include <string>
#include <QMetaType>
#include "HttpGenerator.h"
#include <iostream>

using namespace std;

/* A helper class for processing http requests */

class HttpProcessor {
    private: 
        static map<string, string> data;
    public:
        void process(char* msg, qint64 sz, string& response);
};

#endif /* HTTPPROCESSOR_H */
