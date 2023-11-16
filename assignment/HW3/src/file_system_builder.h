#pragma once
#include "node.h"
#include "folder.h"
#include "file.h"
#include "file_system_scanner.h"

#include <string>
#include <stack>

using std::string;

class FileSystemBuilder {
public:
    // returns the pointer to the root folder.
    Folder * getRoot() const {
        return _root;
    }

    // builds a File for the receiving path and add it to the currently building Folder
    void buildFile(string path) {
        File * file = new File(path);
        
        // There is always at least one folder
        _component.top()->add(file);
    }

    // starts to build a Folder for the receiving path accordingly
    void buildFolder(string path) {
        Folder * folder = new Folder(path); 
        
        _component.push(folder);

        FileSystemScanner * scanner = new FileSystemScanner();
        scanner->setPath(path);

        scanner->nextNode();
        while(!scanner->isDone()) {
            if(scanner->isFile())
                buildFile(scanner->currentNodePath());
            else if(scanner->isFolder())
                buildFolder(scanner->currentNodePath());   
            scanner->nextNode();
        }

        endFolder();

        delete scanner;
    }

    // ends the currently building folder and adds it to its parent Folder
    void endFolder() {
        Folder * folder = _component.top();
        _component.pop();
        if(!_component.empty())
            _component.top()->add(folder);
        else
            _root = folder;
    }
private:
    Folder * _root;
    std::stack<Folder *> _component;
};
