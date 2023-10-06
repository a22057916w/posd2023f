#if !defined(NODE_H)
#define NODE_H

#include<string>

using namespace std;

class Node {
public:
    string name() const;
    
    string path() const;
    
    virtual void add(Node * node) = 0;

    virtual void remove(string path) = 0;
    
    Node * getChildByName(const char * name) const;

    Node * find(string path);

    int numberOfFiles() const;

    Iterator * createIterator();
};


#endif // NODE_H
