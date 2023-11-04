#pragma once

#include "visitor.h"
#include "order_by.h"
#include "folder.h"
#include "file.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class TreeVisitor: public Visitor {
public:
    TreeVisitor(OrderBy orderBy): _orderBy(orderBy) {}

    void visitFile(File * file) {
        _tree += "└── " + file->name();
    }

    void visitFolder(Folder * folder) {
        traverseByName(folder, "");
    }

    void traverseByName(Folder * folder, string prefix) {
        vector<Node *> entries;

        Iterator * it = folder->createIterator(_orderBy);
        for(it->first(); !it->isDone(); it->next()) {
            entries.push_back(it->currentItem());
        }

        for(size_t i = 0; i < entries.size(); i++) {
            Node * entry = entries[i];
            vector<string> pointers = i == entries.size() - 1 ? _final_pointers : _inner_pointers;

            _tree += prefix + pointers[0] + entry->name() + "\n";

            if(dynamic_cast<Folder *>(entry))
                traverseByName(dynamic_cast<Folder *>(entry), prefix + pointers[1]);
        }
    }

    string getTree() { return _tree; }
private:
    string _tree = ".\n";
    vector<string> _inner_pointers = {"├── ", "│   "};
    vector<string> _final_pointers = {"└── ", "    "};
    OrderBy _orderBy;
};