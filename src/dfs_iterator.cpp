#include "./dfs_iterator.h"
#include "./node.h"
#include "./folder.h"

DfsIterator::DfsIterator(Node * composite): _composite(composite) {

}

void DfsIterator::first() {
    Folder * folder = dynamic_cast<Folder *>(_composite);
    if(folder)
        _it = folder->components().begin();
}

Node * DfsIterator::currentItem() const {
    return nullptr;
}

void DfsIterator::next() {

}

bool DfsIterator::isDone() const {
    Folder * folder = dynamic_cast<Folder *>(_composite);
    if(folder)
        return _it == folder->components().end();
    // If the _composite is a file, return true
    else    
        return true;
}