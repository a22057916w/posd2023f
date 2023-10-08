#include "./file.h"

#include <string>

using std::string;

File::File(string path): _path(path) {
    set_name();
    set_directory();
}

void File::set_name() {
    // find the last separator either '/' or '\'
    size_t pos = _path.find_last_of("/\\");
    
    // Extract the filename  
    if(pos != string::npos) 
        _name = _path.substr(pos + 1);
    else
        _name = "";
}

void File::set_directory() {
    size_t pos = _path.find_last_of("/\\");
    
    if (pos != string::npos) 
        _directory = _path.substr(0, pos);
    else
        _directory = "";  
}