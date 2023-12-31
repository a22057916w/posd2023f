#if !defined(FOLDER)
#define FOLDER

#include "./node.h"
#include "./iterator.h"

#include <string>
#include <list>

using namespace std;

class Folder: public Node {
    friend class FolderIterator;
    friend class DfsIterator;
    friend class BfsIterator;
public:
    Folder(string path);    // private setter inside

    // Getter
    string name() const override { return _name; }
    string path() const override { return _path; }
    string directory() const override { return _directory; } // extra def
    list<Node *> components() const { return _components; } // extra def
    bool isVisited() const { return _visited; } // extra def


    // Setter
    void setVisited() { _visited = true; }
    
    // Modifier
    void add(Node * node) override;
    void remove(string path) override;

    // Iterator
    Iterator * createIterator() override;

    // Capacity
    int numberOfFiles() const override;

    // Search
    Node * find(string path) override;
    Node * getChildByName(const char * name) const override;

private:
    string _name;
    string _path;
    string _directory;
    list<Node *> _components;
    bool _visited = false;

    // Setter
    void set_name();
    void set_directory();
};

#endif // FOLDER
