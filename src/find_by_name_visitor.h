#pragma once

#include "file.h"
#include "folder.h"
#include "visitor.h"

class FindByNameVisitor : public Visitor {
public:
    FindByNameVisitor(string name) : _name(name) {}

    void visitFile(File * file) override {
        if (file->name() == _name) {
            _paths.push_back(file->path());
        }
    }

    void visitFolder(Folder * folder) override {
        if (folder->name() == _name) {
            _paths.push_back(folder->path());
        }

        Iterator * it = folder->createIterator();

        it->first();
        for (; !it->isDone(); it->next()) {
            it->currentItem()->accept(this);
        }

        delete it;
    }

    std::list<string> getPaths() const {
        return _paths;
    }

private:
    string _name;
    std::list<string> _paths;
};