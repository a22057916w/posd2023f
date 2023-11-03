#pragma once

#include "visitor.h"
#include "order_by.h"

class TreeVisitor: public Visitor {
public:
    TreeVisitor(OrderBy orderBy);

    void visitFile(File * file);
    void visitFolder(Folder * folder);

    string getTree();
};