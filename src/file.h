#if !defined(FILE_H)
#define FILE_H
#pragma once

#include "./node.h"

#include <string>

using std::string;

class File: public Node {
public:
    File(string path): _path(path) {};

    string name() const override {
        size_t pos = _path.find_last_of("/\\");  // find the last separator either '/' or '\'
        if(pos != string::npos) // Extract the filename
            return _path.substr(pos + 1);
        return _path;    // If no separator is found, return path as name
    }
private:
    string _path;
};

#endif // FILE_H
