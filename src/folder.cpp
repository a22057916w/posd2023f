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


Iterator * Folder::createIterator() {
    if (_type == "Dfs")
        return new DfsIterator(this);
    else if (_type == "Bfs")
        return new BfsIterator(this);
    else
        return new FolderIterator(this);
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