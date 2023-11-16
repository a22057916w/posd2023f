#pragma once

#include <string>

#include "folder.h"
#include "file_system_builder.h"
#include "file_system_scanner.h"

using std::string;

class FileSystemParser {
public:
    FileSystemParser(FileSystemBuilder * builder): _builder(builder) {};

    Folder * getRoot() const {
        return _builder->getRoot();
    };

    // reads the folders/files info with FileSystemScanner and build Folder and File with FileSystemBuilder
    void parse() {
        _builder->buildFolder(_path);
    }

    // sets the path to the folder that will be parsed
    void setPath(string path) {
        _path = path;

    }
private:
    string _path;
    FileSystemBuilder * _builder;
};
