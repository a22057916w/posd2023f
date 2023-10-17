#pragma once

#include "file.h"
#include "folder.h"
#include "visitor.h"

class FindByNameVisitor : public Visitor {
public:
    FindByNameVisitor(string name);

    void visitFile(File * file);

    void visitFolder(Folder * folder);

    std::list<string> getPaths() const;
};