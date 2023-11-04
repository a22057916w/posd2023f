#pragma once

#include <string>

using std::string;

class FileSystemScanner {
public:
    bool isFile() {};

    bool isFolder() {};

    bool isDone() {};

    void setPath(string path) {};

    string currentNodeName() {};

    void nextNode() {};
};
