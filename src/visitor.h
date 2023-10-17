#pragma once

class File;
class Folder;

class Visitor {
public:
    void visitFile(File * file);
    void visitFolder(Folder * folder);
};