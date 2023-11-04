#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/tree_visitor.h"

class TreeVisitorTest: public ::testing::Test {
protected:
    virtual void SetUp() {
        home = new Folder("structure/home");

        profile = new File("structure/home/my_profile");
        home->add(profile);

        hello1 = new File("structure/home/hello.txt");
        home->add(hello1);

        document = new Folder("structure/home/Documents");
        home->add(document);

        favorite = new Folder("structure/home/Documents/favorites");
        document->add(favorite);
        ddd = new File("structure/home/Documents/favorites/domain-driven-design.pdf");
        favorite->add(ddd);
        ca = new File("structure/home/Documents/favorites/clean-architecture.pdf");
        favorite->add(ca);
        cqrs = new File("structure/home/Documents/favorites/cqrs.pdf");
        favorite->add(cqrs);

        note = new File("structure/home/Documents/note.txt");
        document->add(note);

        hello2 = new File("structure/home/Documents/hello.txt");
        document->add(hello2);

        download = new Folder("structure/home/Downloads");
        home->add(download);

        funny = new File("structure/home/Downloads/funny.png");
        download->add(funny);

    }

    void TearDown() {
        delete home;
        delete profile;
        delete download;
        delete document;
        delete note;
        delete favorite;
        delete ddd;
        delete ca;
        delete cqrs;
        delete funny;
        delete hello1;
        delete hello2;
    }
    
    Node * home;
    Node * profile;
    Node * download;
    Node * document;
    Node * note;
    Node * favorite;
    Node * ddd;
    Node * ca;
    Node * cqrs;
    Node * funny;
    Node * hello1;
    Node * hello2;
};

TEST_F(TreeVisitorTest, traverseByName) {
    TreeVisitor * visitor = new TreeVisitor(OrderBy::Name);

    home->accept(visitor);
    
    string expect = ".\n";

    expect += "├── Documents\n";
    expect += "│   ├── favorites\n";
    expect += "│   │   ├── clean-architecture.pdf\n";
    expect += "│   │   ├── cqrs.pdf\n";                
    expect += "│   │   └── domain-driven-design.pdf\n";
    expect += "│   ├── hello.txt\n";
    expect += "│   └── note.txt\n";                        
    expect += "├── Downloads\n";  
    expect += "│   └── funny.png\n";                 
    expect += "├── hello.txt\n";                 
    expect += "└── my_profile\n";                 
                     
    EXPECT_EQ(expect, visitor->getTree());
}

