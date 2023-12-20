#pragma once

#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>
#include <string>
#include <stack>

#include "file.h"
#include "folder.h"

using std::string;

class FileSystemBuilder {
public:
    Folder * getRoot() const {
        if (nullptr == _root) {
            throw "Incomplete builder process";
        }
        return _root;
    }

    void buildFile(string path) {
        if (_folders.empty()) {
            throw "A file should be created under a folder";
        }
        _folders.top()->add(new File(path));
    }

    void buildFolder(string path) {
        _folders.push(new Folder(path));
    }

    void endFolder() {
        if (!_folders.empty()) {
            Folder * folder = _folders.top();
            _folders.pop();
            if (_folders.empty()) {
                _root = folder;
            } else {
                _folders.top()->add(folder);
            }
        }
    }

private:
    Folder * _root;
    std::stack<Folder *> _folders;
};
