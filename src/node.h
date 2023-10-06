#if !defined(NODE_H)
#define NODE_H

#include<string>

using namespace std;

class Node {
public:
    string name() const;
    
    string path() const;
    
    void add(Node * node);

    void remove(string path);
    
    Node * getChildByName(const char * name) const;

    Node * find(string path);

    int numberOfFiles() const;

    Iterator * createIterator();
};


#endif // NODE_H
