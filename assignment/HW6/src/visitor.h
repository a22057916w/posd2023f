#pragma once

class File;
class Link;
class Folder;

class Visitor {
public:
    virtual ~Visitor() {}
    virtual void visitFile(File * file) = 0;
    virtual void visitFolder(Folder * folder) = 0;
    virtual void visitLink(Link * link) = 0;
};