#include "./folder.h"

#include <string>

using std::string;

Folder::Folder(string path): _path(path) {
    set_name();
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