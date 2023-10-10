#if !defined(DFS_ITERATOR_H)
#define DFS_ITERATOR_H

#include "./iterator.h"

#include <list>

class Node;

class DfsIterator: public Iterator {
public:
    DfsIterator(Node* composite) {};

    void first() {};

    Node * currentItem() const { return nullptr;};

    void next() {};
    
    bool isDone() const { return true;};
private:
    Node * _composite;
    // std::stack<Node *> _stack;
    std::list<Node *>::iterator _it;
};

class BfsIterator: public Iterator {
public:
    BfsIterator(Node* composite);
    void first();
    Node * currentItem() const;
    void next();
    bool isDone() const;
private:
    Node * _composite;
    std::list<Node *> _container;
    std::list<Node *>::iterator _it;
};

#endif // DFS_ITERATOR_H
