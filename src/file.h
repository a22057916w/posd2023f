#if !defined(FILE_H)
#define FILE_H
#pragma once

#include "./node.h"

using std::string;

class File: public Node {
public:
    File(string path);
};

#endif // FILE_H
