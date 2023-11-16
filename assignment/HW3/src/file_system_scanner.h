#pragma once

#include <string>
#include <dirent.h>

using std::string;

// scans the files and folders under the receiving path, non-recursively
class FileSystemScanner {
public:
    // tells the clients what type of the most recently read node is
    bool isFile() {
        if(strcmp(_dir->d_name, ".") == 0 || strcmp(_dir->d_name, "..") == 0)
            return false;
        else
            return _dir->d_type == DT_REG;
    }

    bool isFolder() {
        if(strcmp(_dir->d_name, ".") == 0 || strcmp(_dir->d_name, "..") == 0)
            return false;
        else
            return _dir->d_type == DT_DIR;
    }

    // returns true if all the files and folders in the given path are read
    bool isDone() {
        if(_dir == NULL)
            closedir(_dp);
        return _dir == NULL;
    }

    // sets the path to the folder that will be scanned
    void setPath(string path) {
        _dp = opendir(path.c_str());
        _dir_path = path;
    }

    // returns the name most recently read node
    string currentNodeName() {
        return _dir->d_name;
    }

    string currentNodePath() const {
        return _dir_path + "/" + _dir->d_name;
    }

    // read the info of next file or folder
    void nextNode() {
        _dir = readdir(_dp);
    }
private:
    DIR * _dp;
    struct dirent * _dir;
    string _dir_path;
};