#if !defined(ITERATOR_H)
#define ITERATOR_H

#pragma once 

#include<list>

class Node;
class Folder;

class Iterator {
public:
    ~Iterator();
    void first();
    Node * currentItem() const;
    void next();
    bool isDone() const;
};

class FolderIterator : public Iterator {
public:
    FolderIterator(Folder* composite);
    void first();
    Node * currentItem() const;
    void next();
    bool isDone() const;
};


#endif // ITERATOR_H
