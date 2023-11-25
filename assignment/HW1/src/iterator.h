#if !defined(ITERATOR_H)
#define ITERATOR_H

#pragma once 

#include <list>


class Node;
class Folder;

class Iterator {
public:
    virtual ~Iterator() {};
    virtual void first() {};
    virtual Node * currentItem() const {return nullptr;};
    virtual void next() {};
    virtual bool isDone() const {return false;};

};

class FolderIterator : public Iterator {
public:
    FolderIterator(Folder* composite);
    void first();
    Node * currentItem() const;
    void next();
    bool isDone() const;

private:
    Folder * _composite;
    std::list<Node *>::iterator _it;
};


#endif // ITERATOR_H
