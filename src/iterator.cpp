#include "iterator.h"
#include "node.h"
#include "folder.h"

#include <list>

FolderIterator::FolderIterator(Folder * composite): _composite(composite) {}

void FolderIterator::first() {
    list<Node *> _components = _composite->components();
    _it = _components.begin();
}

bool FolderIterator::isDone() const {
    list<Node *> _components = _composite->components();
    return _it == _components.end();
}
