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
    // list<Node *> components() const { return _components; }

    // Modifier
    void add(Node * node) override;

private:
    string _name;
    string _path;
    list<Node *> _components;

    // Setter
    void set_name();
};

#endif // FOLDER
