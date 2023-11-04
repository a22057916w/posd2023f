#pragma once

#include "visitor.h"
#include "order_by.h"
#include "folder.h"
#include "file.h"

#include <string>
#include <vector>

using std::string;
usgin std::vector;

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

    void traversByName(Folder * folder, string prefix) {
        vector<Node *> entries;

        Iterator * it = folder->createIterator(_orderBy);
        for(it->first(); !it->isDone(); it->next()) {
            entries.push_back(it->currentItem());
        }

        for(int i = 0; i < entries.size(); i++) {
            Node * entry = entries[i];
            vector<string> pointers = i == entries.size() - 1 ? _final_pointers : _inner_pointers;

            _tree += prefix + pointers[0] + entry->name() + "\n";

            if(dynamic_cast<Folder *>(entry))
                traversByName(dynamic_cast<Folder *>(entry), pointers[1]);
        }
    }

    string getTree() { return _tree; }
private:
    string _tree = "";
    vector<string> _inner_pointers = {"├── ", "│   "};
    vector<string> _final_pointers = {"└── ", "    "};
    OrderBy _orderBy;
};