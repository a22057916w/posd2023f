#pragma once

#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>
#include <string>

#include "file.h"
#include "folder.h"

using std::string;

class FileSystemScanner {

public:
    bool isFile() {
        return _dp->d_type == DT_REG;
    }

    bool isFolder() {
        return _dp->d_type == DT_DIR && string(_dp->d_name) != "." && string(_dp->d_name) != "..";
    }

    bool isDone() {
        return _dp == nullptr;
    }

    void setPath(string path) {
        _path = path;
    }

    string currentNodeName() {
        return _dp->d_name;
    }

    void nextNode() {
        if (nullptr == _dir) {
            _dir = opendir(_path.c_str());
            if (nullptr == _dir) {
                throw "not a folder";
            }
        }
        _dp = readdir(_dir);
    }

private:
    string _path;
    DIR * _dir = nullptr;
    struct dirent * _dp;
};
