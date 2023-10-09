#if !defined(NODE_H)
#define NODE_H

#include "iterator.h"

#include <string>

using namespace std;

class Node {
public:
    virtual string name() const = 0;
    
    virtual string path() const = 0;
    
    // extra definition
    virtual string directory() const = 0;

    virtual void add(Node * node) = 0;

    // virtual void remove(string path) = 0;
    
    Node * getChildByName(const char * name) const;

    Node * find(string path);

    // int numberOfFiles() const;

    virtual Iterator * createIterator(string type) { return NULL; };

    virtual ~Node() {};
};


#endif // NODE_H
