#pragma once 

#include<list>

class Node;
class Folder;

class Iterator {
public:
    virtual ~Iterator() {}
    virtual void first() {}
    virtual Node * currentItem() const {
        return nullptr;
    }
    virtual void next() {}
    virtual bool isDone() const {
        return true;
    }
};

class FolderIterator : public Iterator {
public:
    FolderIterator(Folder* composite);
    ~FolderIterator() {}
    void first();
    Node * currentItem() const;
    void next();
    bool isDone() const;

private:
    Folder* const _host;
    std::list<Node *>::iterator _current;
};