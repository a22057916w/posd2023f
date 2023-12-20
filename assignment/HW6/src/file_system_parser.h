#pragma once

#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>
#include <string>
#include <iostream>

#include "file.h"
#include "folder.h"
#include "file_system_scanner.h"
#include "file_system_builder.h"

using std::string;

class FileSystemParser {
public:
    FileSystemParser(FileSystemBuilder * builder): _builder(builder) {}

    ~FileSystemParser() {
        delete _builder;
    }

    Folder * getRoot() const {
        return _builder->getRoot();
    }

    void parse() {
        parse(_path);
    }

    void setPath(string path) {
        _path = path;
    }

private:
    void parse(string path) {
        _builder->buildFolder(path);
        FileSystemScanner * _scanner = new FileSystemScanner;
        _scanner->setPath(path);

        for (_scanner->nextNode(); !_scanner->isDone(); _scanner->nextNode()) {
            if(_scanner->isFile()){
                _builder->buildFile(path + "/" + _scanner->currentNodeName());
            }
            else if(_scanner->isFolder()){
                parse(path + "/" + _scanner->currentNodeName());
            }
        }

        delete _scanner;
        _builder->endFolder();
    }

    FileSystemBuilder * _builder;
    string _path;
};
