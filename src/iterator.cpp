#include "iterator.h"
#include "folder.h"

FolderIterator::FolderIterator(Folder* composite)
    :_host(composite) {}

void FolderIterator::first() {
    _current = _host->_nodes.begin();
}

Node * FolderIterator::currentItem() const {
    return *_current;
}

void FolderIterator::next() {
    _current++;
}

bool FolderIterator::isDone() const {
    return _current == _host->_nodes.end();
}
