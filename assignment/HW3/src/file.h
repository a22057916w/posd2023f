#pragma once

#include "node.h"
#include "visitor.h"

class File: public Node {
public:
    File(string path): Node(path) {
        struct stat fileInfo;
        const char *c = path.c_str();
        if(lstat(c, &fileInfo) == 0){
            if(S_ISREG(fileInfo.st_mode)) {
                // initiate _extension
                size_t lastDot = path.find_first_of(".");
                if(lastDot != string::npos)
                    _extension = path.substr(lastDot + 1);
                else
                    _extension = "";
                
                // assign node type
                _type = "File";
                
                return;
            }
        }
        throw "No File exists";
    }

    int numberOfFiles() const override {
        return 1;
    }

    Node * find(string path) override {
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
