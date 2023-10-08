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
}


void Folder::add(Node * node) {
    string node_direcotry = node->directory();
    // if folder path is in the node's(file or folder) path
    if(node_direcotry.find(_path) != string::npos) 
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

void Folder::set_name() {
    // find the last separator either '/' or '\'
    size_t pos = _path.find_last_of("/\\");
    
    // Extract the filename  
    if(pos != string::npos) 
        _name = _path.substr(pos + 1);
    else
        _name = "";
}