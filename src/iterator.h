#if !defined(ITERATOR_H)
#define ITERATOR_H

#pragma once 

#include <list>
#include <string>

using std::string;

class Node;
class Folder;

class Iterator {
public:
    ~Iterator();
    void first();
    Node * currentItem() const;
    void next();
    bool isDone() const;

    // virtual string type() const { return NULL; }
};

class FolderIterator : public Iterator {
public:
    FolderIterator(Folder* composite);
    void first();
    Node * currentItem() const;
    void next();
    bool isDone() const;

    // string type() const override { return "FolderIterator"; }
private:
    Folder * _composite;
    // string const _type = "FolderIterator";
    std::list<Node *>::iterator _it;
};


#endif // ITERATOR_H