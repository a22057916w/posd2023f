#include "./dfs_iterator.h"
#include "./node.h"
#include "./folder.h"

#include <list>



// DfsIterator::DfsIterator(Node * composite): _composite(composite) {}

// void DfsIterator::first() {
//     // if(isDone()) {
//     //     return;
//     // }

//     // Folder * folder = dynamic_cast<Folder *>(_composite);
//     // if(folder) {
//     //     for(auto it = folder->_components.begin(); it != folder->_components.end(); it++)
//     //         this->first();
//     // }
    
// }

// Node * DfsIterator::currentItem() const {
//     return *_it;
// }

// void DfsIterator::next() {
//     // _it++;

//     // Node * currentNode = this->currentItem();
//     // Folder * folder = dynamic_cast<Folder *>(currentNode);
//     // if(folder) {
//     //     DfsIterator * d_it = dynamic_cast<DfsIterator *>(folder->createIterator("Dfs"));
//     //     d_it->first();
//     //     d_it->run();
//     // }

// }

// bool DfsIterator::isDone() const {
//     // Folder * folder = dynamic_cast<Folder *>(_composite);
//     return _it == folder->_components.end();;
// }



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
    // Folder * folder = dynamic_cast<Folder *>(_composite);
    // if(folder) 
    //     _it = folder->_components.begin();

    Node * currentNode = currentItem();
    Folder * folder = dynamic_cast<Folder *>(currentNode);
    if(folder) {
        FolderIterator * fit = new FolderIterator(folder);
            for(fit->first(); !fit->isDone(); fit++)
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