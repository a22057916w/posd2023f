#if !defined(FOLDER)
#define FOLDER

#include "./node.h"

#include <string>

using namespace std;

class Folder: public Node {
public:
    Folder(string path): _path(path) {};

    string name() const override { return getFilename(); }

    string path() const override { return _path; }

private:
    string _path;

    string getFilename() const {
        size_t pos = _path.find_last_of("/\\");  // find the last separator either '/' or '\'
        if(pos != string::npos) // Extract the filename
            return _path.substr(pos + 1);
        return _path;    // If no separator is found, return path as name
    }
};


#endif // FOLDER
