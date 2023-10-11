#include "./dfs_iterator.h"
#include "./node.h"
#include "./folder.h"

#include <list>


DfsIterator::DfsIterator(Node * composite): _composite(composite) {
    Folder * folder = dynamic_cast<Folder *>(_composite);
    if(folder) 
        pushFolder(folder);
}

void DfsIterator::first() {
    // Node * currentNode = currentItem();
    // Folder * folder = dynamic_cast<Folder *>(currentNode);
    // if(folder)
    //     pushFolder(folder);

    _it = _container.begin();
}

Node * DfsIterator::currentItem() const {
    return *_it;
}

void DfsIterator::next() {
    if(!isDone()) {
        _container.pop_front();
        
        Node * currentNode = currentItem();
        Folder * folder = dynamic_cast<Folder *>(currentNode);
        if(folder)
            pushFolder(folder);   

        _it = _container.begin();
    }

}

bool DfsIterator::isDone() const {
    return _it == _container.end();
}


void DfsIterator::pushFolder(Folder * folder) {
    FolderIterator * fit = new FolderIterator(folder);
    for(fit->first(); !fit->isDone(); fit->next()) {
        _container.push_front(fit->currentItem());

        if(fit->currentItem() == dynamic_cast<Folder *>(fit->currentItem()))
            pushFolder(dynamic_cast<Folder *>(fit->currentItem()));         
    }
}

// ******************* BfsIterator **********************


BfsIterator::BfsIterator(Node * composite): _composite(composite) {
    Folder * folder = dynamic_cast<Folder *>(_composite);
    if(folder) {
        FolderIterator * fit = new FolderIterator(folder);
        for(fit->first(); !fit->isDone(); fit->next())
            _container.push_back(fit->currentItem());
    }

}

void BfsIterator::first() {
    _it = _container.begin();

    Node * currentNode = currentItem();
    Folder * folder = dynamic_cast<Folder *>(currentNode);
    if(folder) {
        FolderIterator * fit = new FolderIterator(folder);
            for(fit->first(); !fit->isDone(); fit->next())
                _container.push_back(fit->currentItem());
    }
}

Node * BfsIterator::currentItem() const {
    return *_it;
}

void BfsIterator::next() {
    _it++;
    
    if(!isDone()) {
        Node * currentNode = currentItem();
        Folder * folder = dynamic_cast<Folder *>(currentNode);
        if(folder) {
            FolderIterator * fit = new FolderIterator(folder);
            for(fit->first(); !fit->isDone(); fit->next())
                _container.push_back(fit->currentItem());      
        }
    }
}


bool BfsIterator::isDone() const {
    return _it == _container.end();
}