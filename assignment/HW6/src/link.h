#pragma once

#include "node.h"
#include "visitor.h"

#include <string>
#include <list>

using std::string;

class Link : public Node {
private:
    Node * _node;
public:
    Link(string path, Node * node): Node(path), _node(node) {}
    
    Node * getTarget() const {
        return _node;
    }

    void add(Node * node) {
        getTarget()->add(node);
    } 

    int numberOfFiles() const override {
        return getTarget()->numberOfFiles();
    }

    Node * find(string path) override {
        return getTarget()->find(path);
    }

    std::list<string> findByName(string name) override {
        return getTarget()->findByName(name);
    }

    void remove(string path) override {
        return getTarget()->remove(path);
    }

    Node * getChildByName(const char * name) const override {
        return getTarget()->getChildByName(name);
    }

    void accept(Visitor * visitor) override {
        visitor->visitLink(this);
    }
};