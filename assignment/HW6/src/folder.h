#pragma once 

#include <list>
#include <sys/stat.h>
#include "node.h"
#include "file.h"
#include "iterator.h"
#include "iterator_factory.h"
#include "dfs_iterator.h"
#include "order_by.h"
#include "link.h"

#include <iostream>

using namespace std;

class Folder: public Node {
private:
    list<Node *> _nodes;
    int _operationCount = 0;

public:
    Folder(string path): Node(path) {
        struct stat fileInfo;
        const char *c = path.c_str();
        if(lstat(c, &fileInfo) == 0){
            if(S_ISDIR(fileInfo.st_mode))
                return;
        }
        throw "No Folder exists";
    }

    ~Folder() {
        for (auto node: _nodes) {
            delete node;
        }
        _nodes.clear();
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

    void renameAllChild(string path) override {
        Iterator * it = createIterator();
        string newPath = path;
        for(it->first(); !it->isDone(); it->next()) {
            Node * node = it->currentItem();
            node->rename(path + "/" + node->name());
        }
    }

    // Iterator * createIterator(OrderBy orderBy=OrderBy::Normal) override {
    //     switch (orderBy) {
    //         case OrderBy::Name :
    //             return new OrderByNameIterator(this, _operationCount);
    //         case OrderBy::NameWithFolderFirst :
    //             return new OrderByNameWithFolderFirstIterator(this, _operationCount);
    //         case OrderBy::Kind :
    //             return new OrderByKindIterator(this, _operationCount);
    //         case OrderBy::Normal: 
    //         default:
    //             return new FolderIterator(this, _operationCount);
    //     }
    // }

    Iterator * createIterator() override {
        return new FolderIterator(this, _operationCount);
    }

    Iterator * createIterator(IteratorFactory * factory) override {
        return factory->create(this, _operationCount);
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
            delete target;
        }
    }

    void removeChild(Node * target) override {
        _nodes.remove(target);
        _operationCount++;
    }

    void accept(Visitor * visitor) override {
        visitor->visitFolder(this);
    }

private:
    class AbstractFolderIterator: public Iterator {
    private:
        const int _operationCount;
    protected:
        Folder * _host;

        AbstractFolderIterator(Folder * host, int operationCount): _operationCount(operationCount), _host(host) {}

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }
    };

public:
    class FolderIterator : public AbstractFolderIterator {
    public:
        FolderIterator(Folder* composite, int operationCount) : AbstractFolderIterator(composite, operationCount) {}

        ~FolderIterator() {}
        
        void first() override {
            checkAvailable();
            _current = _host->_nodes.begin();
        }

        Node * currentItem() const override {
            return *_current;
        }

        void next() override {
            checkAvailable();
            _current++;
        }

        bool isDone() const override {
            return _current == _host->_nodes.end();
        }

    private:
        std::list<Node *>::iterator _current;
    };

private:
    class OrderByAbstractIterator : public AbstractFolderIterator {
    protected:
        OrderByAbstractIterator(Folder* composite, int operationCount) : AbstractFolderIterator(composite, operationCount) {}

        // template method
        Node * cloneSortedNode(Node * node) {
            // new a link for clone
            Link * link = dynamic_cast<Link *>(node);
            if(link) {
                return new Link(link->path(), link->getTarget());
            }

            File * file = dynamic_cast<File *>(node);
            if (file) {
                return new File(node->path());
            }

            Node * clonedFolder = new Folder(node->path());

            std::list<Node *> children;
            Iterator * it = node->createIterator();
            for (it->first(); !it->isDone(); it->next()) {
                children.push_back(it->currentItem());
            }
            
            sortChildren(children);    // primitive operation

            for (auto childrenIt = children.begin(); childrenIt != children.end(); childrenIt++) {
                clonedFolder->add(cloneSortedNode(*childrenIt));
            }
            return clonedFolder;
        }

        // primitive operation
        virtual void sortChildren(std::list<Node *> &children) = 0;

    };

public:

    class OrderByNameIterator: public OrderByAbstractIterator {
    public:
        OrderByNameIterator(Folder * node, int operationCount) : OrderByAbstractIterator(node, operationCount) {
            _root = cloneSortedNode(node);
        }

        ~OrderByNameIterator() {
            delete _root;
            if (_iterator) {
                delete _iterator;
            }
        }

        void first() override {
            checkAvailable();
            if (_iterator != nullptr) {
                delete _iterator;
                _iterator = nullptr;
            } 
            _iterator = _root->createIterator();
            _iterator->first();
        }

        Node * currentItem() const override {
            return _iterator->currentItem();
        }

        void next() override {
            checkAvailable();
            _iterator->next();
        }

        bool isDone() const override {
            return _iterator->isDone();
        }
    protected:
        void sortChildren(std::list<Node *> &children) override {
            children.sort([](const Node * a, const Node * b) {
                return a->name() < b->name();
            });
        }
    
    private:
        Node * _root;
        Iterator * _iterator = nullptr;
    };

    class OrderByNameWithFolderFirstIterator: public OrderByAbstractIterator {
    public:
        OrderByNameWithFolderFirstIterator(Folder * node, int operationCount) : OrderByAbstractIterator(node, operationCount) {
            _root = cloneSortedNode(node);
        }

        ~OrderByNameWithFolderFirstIterator() {
            delete _root;
            if (_iterator) {
                delete _iterator;
            }
        }
        
        void first() override {
            checkAvailable();
            if (_iterator != nullptr) {
                delete _iterator;
                _iterator = nullptr;
            } 
            _iterator = _root->createIterator();
            _iterator->first();
        }

        Node * currentItem() const override {
            return _iterator->currentItem();
        }

        void next() override {
            checkAvailable();
            _iterator->next();
        }

        bool isDone() const override {
            return _iterator->isDone();
        }
    protected:
        void sortChildren(std::list<Node *> &children) override {
            children.sort([](const Node * a, const Node * b) {
                const Folder * folderA = dynamic_cast<const Folder *>(a);
                const Folder * folderB = dynamic_cast<const Folder *>(b);
                if (folderA) {
                    if (nullptr == folderB) {
                        return true;
                    }
                } else {
                    if (folderB) {
                        return false;
                    }
                }
                return a->name() < b->name();
            });
        }

    private:
        Node * _root;
        Iterator * _iterator = nullptr;
    };

    class OrderByKindIterator: public OrderByAbstractIterator {
    public:
        OrderByKindIterator(Folder * node, int operationCount) : OrderByAbstractIterator(node, operationCount) {
            _root = cloneSortedNode(node);
        }

        ~OrderByKindIterator() {
            delete _root;
            if (_iterator) {
                delete _iterator;
            }
        }
        
        void first() override {
            if (_iterator != nullptr) {
                delete _iterator;
                _iterator = nullptr;
            } 
            _iterator = _root->createIterator();
            _iterator->first();
        }

        Node * currentItem() const override {
            return _iterator->currentItem();
        }

        void next() override {
            _iterator->next();
        }

        bool isDone() const override {
            return _iterator->isDone();
        }
    protected:
        void sortChildren(std::list<Node *> &children) override {
            children.sort([](const Node * a, const Node * b) {
                string kindA = getKind(a);
                string kindB = getKind(b);
                if (kindA == kindB) {
                    return a->name() < b->name();
                }
                return kindA < kindB;
            });
        }

    private:
        Node * _root;
        Iterator * _iterator = nullptr;

        static string getKind(const Node * node) {
            const Folder * folder = dynamic_cast<const Folder *>(node);
            if (folder) {
                return "folder";
            }

            // add Link kind
            const Link * link = dynamic_cast<const Link *>(node);
            if(link)
                return "link";

            std::size_t pos = node->name().rfind(".");
            if (pos == std::string::npos) {
                return "file";
            }

            return node->name().substr(pos+1);
        }
    };
};
