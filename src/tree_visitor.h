#pragma once

#include "visitor.h"
#include "order_by.h"
#include "folder.h"
#include "file.h"

#include <string>

using std::string;

class TreeVisitor: public Visitor {
public:
    TreeVisitor(OrderBy orderBy): _orderBy(orderBy) {
        _currLevel = -1;
        _prevLevel = -1;
        _tree = "";
    }

    void visitFile(File * file) {
        _tree += file->name();
    }

    void visitFolder(Folder * folder) {
        if(_orderBy == OrderBy::Name) {
            _currLevel++;
            _prevLevel++;

            Iterator * it = folder->createIterator(_orderBy);
            for(it->first(); !it->isDone(); it->next()) {
                if(it->next() == it->isDone())
                    _prevLevel--;

                if(_currLevel > 0) {
                    _tree += "│";
                    for(int i = 0; i < _currLevel; i++)
                        _tree += "|   "; 
                }
                _tree += "├── ";
                if(dynamic_cast<Folder *>(it->currentItem()))
                    _tree += it->currentItem()->name();
                    
                it->currentItem()->accept(this);
                _tree += "\n";
            }
        }
    }

    void traversByName(Node * folder, string prefix) {
        Iterator * it = folder->createIterator(_orderBy);
        for(it->first(); !it->isDone(); it->next()) {

        }
    }

    string getTree() { return _tree; }
private:
    string _tree = "";
    int _currLevel;
    int _prevLevel;
    OrderBy _orderBy;
};