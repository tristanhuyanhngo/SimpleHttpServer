#ifndef HTTPPROCESSOR_H
#define HTTPPROCESSOR_H 

#include <cstring>
#include <QMetaType>
#include "HttpGenerator.h"
#include <iostream>

using namespace std;

/* A helper class for processing http requests */

class HttpProcessor {
    public:
        static void process(char* msg, qint64 sz, string& response);
};

#endif /* HTTPPROCESSOR_H */
