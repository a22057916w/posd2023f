#if !defined(FILE_H)
#define FILE_H

#include "./node.h"

#include <string>

using std::string;

class File: public Node {
public:
    File(string path);  // setter inside

    // Getter
    string name() const override { return _name; }
    string path() const override { return _path; }
    string directory() const override { return _directory; }  // extra def from Node


private:
    string _name;
    string _path;
    string _directory;

    // setter
    void set_name();
    void set_directory();
};

#endif // FILE_H
