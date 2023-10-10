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
    if(node->directory() == _path) 
        _components.push_back(node);
    else
        cout << "The node's path do not match with the current directory.\n";
}



Iterator * Folder::createIterator(string type) {
    if (type == "Dfs")
        return new DfsIterator(this);
    else if (type == "Bfs")
        return new BfsIterator(this);
    else
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