#include "../src/tree_visitor.h"
// #include "../src/order_by.h"
#include "../src/iterator_factories.h"

#include <iostream>

class TreeVisitorTest: public ::testing::Test {
protected:
    void SetUp() {

        home = new Folder("structure2/home");

        profile = new File("structure2/home/my_profile");
        home->add(profile);

        hello = new File("structure2/home/hello.txt");
        home->add(hello);

        download = new Folder("structure2/home/Downloads");
        home->add(download);
        funny = new File("structure2/home/Downloads/funny.png");
        download->add(funny);

        document = new Folder("structure2/home/Documents");
        home->add(document);

        note = new File("structure2/home/Documents/note.txt");
        document->add(note);
        hello2 = new File("structure2/home/Documents/hello.txt");
        document->add(hello2);

        programming = new Folder("structure2/home/Documents/programming");
        document->add(programming);
        cpp = new File("structure2/home/Documents/programming/cpp.pub");
        programming->add(cpp);
        oop = new File("structure2/home/Documents/programming/oop.pdf");
        programming->add(oop);
        python = new File("structure2/home/Documents/programming/python.pub");
        programming->add(python);

        ddd = new File("structure2/home/Documents/domain-driven-design.pub");
        document->add(ddd);
        ca = new File("structure2/home/Documents/clean-architecture.pdf");
        document->add(ca);
        ooad = new File("structure2/home/Documents/object-oriented-analysis-and-design.pdf");
        document->add(ooad);

        linkToProgramming = new Link("structure2/home/link_to_programming", programming);
        home->add(linkToProgramming);
    }

    void TearDown() {
        delete home;
        linkToProgramming = nullptr;
        profile = nullptr;
        hello = nullptr;
        download = nullptr;
        funny = nullptr;
        document = nullptr;
        note = nullptr;
        hello2 = nullptr;
        programming = nullptr;
        cpp = nullptr;
        oop = nullptr;
        python = nullptr;
        ddd = nullptr;
        ca = nullptr;
        ooad = nullptr;
    }
    
    Node * home;
    Node * profile;
    Node * hello;
    Node * download;
    Node * funny;
    Node * document;
    Node * note;
    Node * hello2;
    Node * programming;
    Node * cpp;
    Node * oop;
    Node * python;
    Node * ddd;
    Node * ca;
    Node * ooad;
    Node * linkToProgramming;
};

TEST_F(TreeVisitorTest, OrderByName) {
    string expected = 
    ".\n"
    "├── Documents\n"
    "│   ├── clean-architecture.pdf\n"
    "│   ├── domain-driven-design.pub\n"
    "│   ├── hello.txt\n"
    "│   ├── note.txt\n"
    "│   ├── object-oriented-analysis-and-design.pdf\n"
    "│   └── programming\n"
    "│       ├── cpp.pub\n"
    "│       ├── oop.pdf\n"
    "│       └── python.pub\n"
    "├── Downloads\n"
    "│   └── funny.png\n"
    "├── hello.txt\n"
    "├── link_to_programming\n"
    "└── my_profile\n";

    TreeVisitor * tree = new TreeVisitor(OrderByNameIteratorFactory::instance());
    home->accept(tree);
    string result = tree->getTree();

    ASSERT_EQ(expected, result);

    delete tree;
}


TEST_F(TreeVisitorTest, OrderByNameWithFolderFirst) {
    string expected = 
    ".\n"
    "├── Documents\n"
    "│   ├── programming\n"
    "│   │   ├── cpp.pub\n"
    "│   │   ├── oop.pdf\n"
    "│   │   └── python.pub\n"
    "│   ├── clean-architecture.pdf\n"
    "│   ├── domain-driven-design.pub\n"
    "│   ├── hello.txt\n"
    "│   ├── note.txt\n"
    "│   └── object-oriented-analysis-and-design.pdf\n"
    "├── Downloads\n"
    "│   └── funny.png\n"
    "├── hello.txt\n"
    "├── link_to_programming\n"
    "└── my_profile\n";

    TreeVisitor * tree = new TreeVisitor(OrderByNameWithFolderFirstIteratorFactory::instance());
    home->accept(tree);
    string result = tree->getTree();

    ASSERT_EQ(expected, result);

    delete tree;
}

TEST_F(TreeVisitorTest, OrderByKind) {
    string expected = 
    ".\n"
    "├── my_profile\n"
    "├── Documents\n"
    "│   ├── programming\n"
    "│   │   ├── oop.pdf\n"
    "│   │   ├── cpp.pub\n"
    "│   │   └── python.pub\n"
    "│   ├── clean-architecture.pdf\n"
    "│   ├── object-oriented-analysis-and-design.pdf\n"
    "│   ├── domain-driven-design.pub\n"
    "│   ├── hello.txt\n"
    "│   └── note.txt\n"
    "├── Downloads\n"
    "│   └── funny.png\n"
    "├── link_to_programming\n"
    "└── hello.txt\n";

    TreeVisitor * tree = new TreeVisitor(OrderByKindIteratorFactory::instance());
    home->accept(tree);
    string result = tree->getTree();

    ASSERT_EQ(expected, result);

    delete tree;
}