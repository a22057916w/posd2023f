#if !defined(FOLDER)
#define FOLDER

#include "./node.h"
#include "./iterator.h"

#include <string>
#include <list>

using namespace std;

class Folder: public Node {
public:
    Folder(string path);    // setter inside

    // Getter
    string name() const override { return _name; }
    string path() const override { return _path; }
    string directory() const override { return _path; }  // extra def from Node

    // Modifier
    void add(Node * Node) override;

    list<Node *> getComponents() const { return _components; }
    
private:
    string _name;
    string _path;
    list<Node *> _components;

    //setter
    void set_name();
};

#endif // FOLDER
