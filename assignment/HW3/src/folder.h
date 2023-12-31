#pragma once 

#include "node.h"
#include "iterator.h"
#include "order_by.h"


#include <list>
#include <sys/stat.h>
#include <algorithm>
#include <cstring>
#include <string>


using namespace std;

class Folder: public Node {
private:
    list<Node *> _nodes;
    int _operationCount = 0;

protected:
    void removeChild(Node * target) override {
        _nodes.remove(target);
        _operationCount++;
    }

public:
    Folder(string path): Node(path) {
        struct stat fileInfo;
        const char *c = path.c_str();
        if(lstat(c, &fileInfo) == 0){
            if(S_ISDIR(fileInfo.st_mode)) {
                _extension = "";
                _type = "Folder";
                return;
            }
        }
        throw "No Folder exists";
    }

    void add(Node * node) override {
        if (node->path() != this->path() + "/" + node->name()) {
            throw string("Incorrect path of node: " + node -> path());
        }
        _nodes.push_back(node);
        node->parent(this);
        _operationCount++;
    }

    Node * getChildByName(const char * name) const override {
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            if ((*it)->name() == name) {
                return *it;
            }
        }

        return nullptr;
    }

    int numberOfFiles() const override {
        int num = 0;
        if (_nodes.size() == 0) {
            return 0;
        }
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            num += (*it)->numberOfFiles();
        }
        return num;
    }

    Node * find(string path) override {
        if (this->path() == path) {
            return this;
        }

        size_t index = path.find(this->path());

        if (string::npos == index) {
            return nullptr;
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            Node * result = (*it)->find(path);
            if (result) {
                return result;
            }
        }
        return nullptr;
    }

    std::list<string> findByName(string name) override {
        std::list<string> pathList;
        if (this->name() == name) {
            pathList.push_back(this->path());
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            std::list<string> paths = (*it)->findByName(name);
            for (auto i = paths.begin(); i != paths.end(); i++)
            {
                pathList.push_back(*i);  
            }
        }

        return pathList;
    }

    void remove(string path) override {
        Node * target = find(path);
        if (target) {
            target->parent()->removeChild(target);
        }
    }

    void accept(Visitor * visitor) override {
        visitor->visitFolder(this);
    }

    Iterator * createIterator() override {
        return new FolderIterator(this, _operationCount);
    }

    Iterator * createIterator(OrderBy category) override {
        if(category == OrderBy::Normal)
            return new FolderIterator(this, _operationCount);
        else if(category == OrderBy::Name)
            return new OrderByNameIterator(this, _operationCount);
        else if(category == OrderBy::NameWithFolderFirst)
            return new OrderByNameWithFolderFirstIterator(this, _operationCount);
        else if(category == OrderBy::Kind)
            return new OrderByKindIterator(this, _operationCount);
        else
            return new NullIterator();
    }

    class FolderIterator : public Iterator {
    public:
        FolderIterator(Folder* composite, int operationCount) : _host(composite), _operationCount(operationCount) {}

        ~FolderIterator() {}

        void first() {
            checkAvailable();
            _current = _host->_nodes.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _host->_nodes.end();
        }

    private:
        Folder* const _host;
        std::list<Node *>::iterator _current;
        int _operationCount;

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }
    };

    class OrderByNameIterator: public Iterator {
    public:
        OrderByNameIterator(Folder * composite, int operationCount): _host(composite), _operationCount(operationCount) {
            // copy _host->_nodes to this->_nodes
            std::copy(_host->_nodes.begin(), _host->_nodes.end(), std::back_inserter(_nodes));
            
            // sort the list alphabetically
            _nodes.sort([](const Node * n1, const Node * n2) {
                return n1->name() < n2->name();
            });  
        };

        ~OrderByNameIterator() {}

         void first() {
            checkAvailable();
            _current = _nodes.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _nodes.end();
        }

    private:
        Folder * const _host;
        std::list<Node *> _nodes;
        std::list<Node *>::iterator _current;
        int _operationCount;

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }
    };

    class OrderByNameWithFolderFirstIterator: public Iterator {
    public:
        OrderByNameWithFolderFirstIterator(Folder * composite, int operationCount): _host(composite), _operationCount(operationCount) {
            // copy _host->_nodes to this->_nodes
            std::copy(_host->_nodes.begin(), _host->_nodes.end(), std::back_inserter(_nodes));
            
            // sort the list with folder first
            _nodes.sort([](const Node * n1, const Node * n2) {
                if(n1->type() == "Folder" && n2->type() == "File")
                    return true;
                else if(n1->type() == "File" && n2->type() == "Folder")
                    return false;
                else
                    return n1->name() < n2->name();
            });  
        };

        ~OrderByNameWithFolderFirstIterator() {}

         void first() {
            checkAvailable();
            _current = _nodes.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _nodes.end();
        }

    private:
        Folder * const _host;
        std::list<Node *> _nodes;
        std::list<Node *>::iterator _current;
        int _operationCount;

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }
    };

    class OrderByKindIterator: public Iterator {
    public:
        OrderByKindIterator(Folder * composite, int operationCount): _host(composite), _operationCount(operationCount) {
            // copy _host->_nodes to this->_nodes
            std::copy(_host->_nodes.begin(), _host->_nodes.end(), std::back_inserter(_nodes));
            
            // sort the list by node kinds
            _nodes.sort([](const Node * n1, const Node * n2) {
                // file with no extension sort first
                if(n1->type() == "File" && n1->extension() == "")
                    return true;
                if(n2->type() == "File" && n2->extension() == "")
                    return false;
                
                // folder sort before file
                if(n1->type() == "Folder" && n2->type() == "File")
                    return true;
                else if(n1->type() == "File" && n2->type() == "Folder")
                    return false;
                // sort file by file extension
                else if(n1->type() == "File" && n2->type() == "File") {
                    // compare extension, if equal compare name
                    if(n1->extension() != n2->extension())
                        return n1->extension() < n2->extension();
                    else
                        return n1->name() < n2->name();
                }
                else
                    return n1->name() < n2->name();
            });  
        };
        
        ~OrderByKindIterator() {}

         void first() {
            checkAvailable();
            _current = _nodes.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _nodes.end();
        }

    private:
        Folder * const _host;
        std::list<Node *> _nodes;
        std::list<Node *>::iterator _current;
        int _operationCount;

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }
    };
};
