#pragma once

#include "file.h"
#include "folder.h"
#include "visitor.h"
#include <fstream>
#include <iostream>
#include <sstream>

class StreamOutVisitor : public Visitor {
public:
    void visitFile(File * file);

    void visitFolder(Folder * folder);

    string getResult() const;
};