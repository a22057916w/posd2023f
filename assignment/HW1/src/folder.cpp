#include "./folder.h"
#include "./node.h"
#include "./iterator.h"
#include "./dfs_iterator.h"

#include <iostream>
#include <string>
#include <list>

using std::string;
using std::list;
using std::cout;

Folder::Folder(string path): _path(path) {
    set_name();
    set_directory();
}


void Folder::add(Node * node) {
    if(node->directory() == _path)  {
        _components.push_back(node);
        node->_parent = this;
    }
    else
        cout << "The node's path do not match with the current directory.\n";
}


void Folder::remove(string path) {
    Node * node = find(path);
    if(node) {
        Folder * parent = dynamic_cast<Folder *>(node->_parent);
        parent->_components.remove(node);
        delete node;
    }
}

Node * Folder::find(string path) {
    BfsIterator * _it = new BfsIterator(this);
    // BfsIterator *_it = dynamic_cast<BfsIterator *>(createIterator("bfs"));
    for(_it->first(); !_it->isDone(); _it->next()) 
        if(_it->currentItem()->path() == path) 
            return _it->currentItem();

    return nullptr;   
}

Node * Folder::getChildByName(const char * name) const {
    // Make a copy of the current folder
    Folder * copy = new Folder(_path);
    for(Node * component : _components)
        copy->add(component);

    // Count the files by BFS
    BfsIterator * _it = new BfsIterator(copy);
    for(_it->first(); !_it->isDone(); _it->next())
        if(_it->currentItem()->name() == name) {
            return _it->currentItem();
        }
            
    return nullptr;
}

Iterator * Folder::createIterator() {
    return new FolderIterator(this);
}


int Folder::numberOfFiles() const {
    int count = 0;

    // Make a copy of the current folder
    Folder * copy = new Folder(_path);
    for(Node * component : _components)
        copy->add(component);

    // Count the files by BFS
    BfsIterator * it = new BfsIterator(copy);
    for(it->first(); !it->isDone(); it->next())
        // If current node is folder, ignore it.
        if(it->currentItem() != dynamic_cast<Folder *>(it->currentItem()))
            count++;
    return count;
}

void Folder::set_name() {
    // find the last separator either '/' or '\'
    size_t pos = _path.find_last_of("/\\");
    
    // Extract the filename  
    if(pos != string::npos) 
        _name = _path.substr(pos + 1);
    else
        _name = "";
}

void Folder::set_directory() {
    size_t pos = _path.find_last_of("/\\");
    
    if (pos != string::npos) 
        _directory = _path.substr(0, pos);
    else
        _directory = "";  
}