#pragma once

class File;
class Folder;

class Visitor {
public:
    virtual ~Visitor() {};
    virtual void visitFile(File * file) = 0;
    void visitFolder(Folder * folder) {};
};