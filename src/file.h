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
        if (nodeType != "file")
            throw(std::string("It is not File!"));
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