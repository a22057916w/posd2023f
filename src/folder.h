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
    Folder(string path);    // setter inside

    // Getter
    string name() const override { return _name; }
    string path() const override { return _path; }
    string directory() const override { return _directory; } // extra def from Node
    list<Node *> components() const { return _components; } // extra def from Node

    // Modifier
    void add(Node * node) override;
    void remove(string path) override;

    // Iterator
    Iterator * createIterator(string type);

    // Capacity
    int numberOfFiles() const override;

    // Search
    Node * find(string path) override;

private:
    string _name;
    string _path;
    string _directory;
    string _type = "Folder";
    list<Node *> _components;

    // Setter
    void set_name();
    void set_directory();
};

#endif // FOLDER
