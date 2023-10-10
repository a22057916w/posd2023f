#if !defined(NODE_H)
#define NODE_H

#include "iterator.h"

#include <string>

using namespace std;

class Node {
public:
    Node * _parent;
    
    virtual string name() const = 0;
    
    virtual string path() const = 0;
    
    // extra definition
    virtual string directory() const = 0;


    virtual void add(Node * node) = 0;

    virtual void remove(string path) {};
    
    virtual Node * getChildByName(const char * name) const { return nullptr; };

    virtual Node * find(string path) { return nullptr;};

    virtual int numberOfFiles() const = 0;

    virtual Iterator * createIterator() = 0;

    virtual ~Node() {};

};


#endif // NODE_H
