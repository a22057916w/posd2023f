#pragma once

#include <stack>
#include <list>

#include "iterator.h"

class DfsIterator: public Iterator {
public:
    DfsIterator(Node* composite) : _root(composite) {}

    void first() {
        while(!_stack.empty()){
            _stack.pop();
        }

        _curr = _root;
        _pushCurrIter();
        next();
    }

    Node * currentItem() const {
        return _curr;
    }

    void next() {
        while(!_stack.empty() && _stack.top()->isDone()){
            _stack.pop();
        }
        if(_stack.empty()){
            return;
        }
        if(!_stack.top()->isDone()){
            _curr = _stack.top()->currentItem();
            _stack.top()->next();
            _pushCurrIter();
        }
    }
    
    bool isDone() const {
        return _stack.empty();
    }
private:
    Node * _root;
    Node * _curr;
    std::stack<Iterator *> _stack;

    void _pushCurrIter() {
        Iterator * it = _curr->createIterator();
        it->first();
        _stack.push(it);
    }
};

class BfsIterator: public Iterator {
public:
    BfsIterator(Node* composite) : _root(composite) {}

    void first(){
        if(!_nextLevel.empty())
            _nextLevel.clear();

        _curr = _root;
        _nextLevel.push_back(_curr);
        next();
    }

    Node * currentItem() const {
        return _curr;
    }

    void next() {
        Iterator * it = _curr->createIterator();
        for(it->first(); !it->isDone(); it->next()){
            _nextLevel.push_back(it->currentItem());
        }

        _nextLevel.pop_front();
        _curr = _nextLevel.front();
        return;
    }
    
    bool isDone() const {
        return _nextLevel.empty();
    }
private:
    Node * _root;
    Node * _curr;
    std::list<Node *> _nextLevel;
};

