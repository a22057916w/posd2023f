#pragma once

#include "node.h"
#include "visitor.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>

using std::string;

class File: public Node {
public:
    File(string path): Node(path) {
        struct stat sb;
        // if file not found, throw exception
        if(stat(path.c_str(), &sb) == -1) {
            throw string("Path not Found");
        }
        // if the path is a folder, throw exception
        if(S_ISDIR(sb.st_mode)) {
            throw string("Path is a Direcyory");
        }
    }

    int numberOfFiles() const override  {
        return 1;
    }

    Node * find(string path) override  {
        if (this->path() == path) {
            return this;
        }
        return nullptr;
    }

    std::list<string> findByName(string name) override {
        std::list<string> pathList;
        if (this->name() == name) {
            pathList.push_back(this->path());
        }
        return pathList;
    }

    void accept(Visitor * visitor) override {
        visitor->visitFile(this);
    }
};