#pragma once

#include "file.h"
#include "folder.h"
#include "visitor.h"

#include <list>
#include <string>

using std::string;

class FindByNameVisitor : public Visitor {
public:
    FindByNameVisitor(string name): _name(name) {};

    void visitFile(File * file) override {
        if (file->name() == _name)
            _pathList.push_back(file->path());
    }

    void visitFolder(Folder * folder) {
        if (folder->name() == _name)
            _pathList.push_back(folder->path());

        // need to create inner class folderIteartor 
        auto it = compound->createIterator();
         for(it->first(); !it->isDone(); it->next()){
            it->currentItem()->accept(this);
            // std::list<string> paths = (*it)->findByName(_name);
            // for (auto i = paths.begin(); i != paths.end(); i++)
            //     pathList.push_back(*i);   
        }
    }

    std::list<string> getPaths() const { return _pathList; }

private:
    string _name;
    std::list<string> _pathList;
};