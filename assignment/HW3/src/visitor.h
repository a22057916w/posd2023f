#pragma once

class File;
class Folder;

class Visitor {
public:
    virtual void visitFile(File * file) = 0;
    virtual void visitFolder(Folder * folder) = 0;
};