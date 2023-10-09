#include "iterator.h"
#include "node.h"
#include "folder.h"

#include <list>

using std::list;

FolderIterator::FolderIterator(Folder * composite): _composite(composite) {}

void FolderIterator::first() {
    _it = _composite->components().begin();
}

void FolderIterator::next() {
    _it++;
}

Node * FolderIterator::currentItem() const {
    return *_it;
}

bool FolderIterator::isDone() const {
    return _it == _composite->components().end();
}
