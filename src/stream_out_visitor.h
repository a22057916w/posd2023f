#pragma once

#include "file.h"
#include "folder.h"
#include "visitor.h"


#include <fstream>
#include <iostream>
#include <sstream>

class StreamOutVisitor : public Visitor {
public:
    void visitFile(File * file) {
        if(file->name() == _name) {
        }
    }

    void visitFolder(Folder * folder) {};

    string getResult() const {}

private:
    string _name;
    std::list<string> _pathList;
};