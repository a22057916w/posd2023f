#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/tree_visitor.h"
#include "../src/order_by.h"
#include "../src/file_system_scanner.h"
#include "../src/file_system_parser.h"
#include "../src/file_system_builder.h"


class ParserTest: public ::testing::Test {
protected:
    virtual void SetUp() {
        home = new Folder("structure/home");

        profile = new File("structure/home/my_profile");
        home->add(profile);

        document = new Folder("structure/home/Documents");
        home->add(document);

        hello = new File("structure/home/hello.txt");
        home->add(hello);

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

        download = new Folder("structure/home/Downloads");
        home->add(download);

        funny = new File("structure/home/Downloads/funny.png");
        download->add(funny);

        visitor_folder = new Folder("structure/visitor");

        file1 = new File("structure/visitor/file1.txt");
        visitor_folder->add(file1);
        
        file2 = new File("structure/visitor/file2.txt");
        visitor_folder->add(file2);
        
        nested = new Folder("structure/visitor/nested");
        visitor_folder->add(nested);
        
        file3 = new File("structure/visitor/nested/file3.txt");
        nested->add(file3);
        
        file4 = new File("structure/visitor/nested/file4.txt");
        nested->add(file4);
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
        delete hello;

        delete visitor_folder;
        delete file1;
        delete file2;
        delete nested;
        delete file3;
        delete file4;
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
    Node * hello;

    Node * visitor_folder;
    Node * file1;
    Node * file2;
    Node * nested;
    Node * file3;
    Node * file4;
};

TEST_F(ParserTest, buildHomeFolder) {
    FileSystemBuilder * builder = new FileSystemBuilder();
    FileSystemParser * parser = new FileSystemParser(builder);
    
    parser->setPath(home->path());
    parser->parse();
    
    Folder * root = parser->getRoot();
    TreeVisitor * visitor = new TreeVisitor(OrderBy::Name);
    root->accept(visitor);

    string expect = ".\n";

    expect += "├── Documents\n";
    expect += "│   ├── apple.pdf\n";
    expect += "│   ├── favorites\n";
    expect += "│   │   ├── clean-architecture.pdf\n";
    expect += "│   │   ├── cqrs.pdf\n";                
    expect += "│   │   └── domain-driven-design.pdf\n";
    expect += "│   ├── hello.txt\n";
    expect += "│   ├── note.txt\n";
    expect += "│   └── whisky.pdf\n";                        
    expect += "├── Downloads\n";  
    expect += "│   └── funny.png\n";                 
    expect += "├── hello.txt\n";                 
    expect += "└── my_profile\n";

    EXPECT_EQ(expect, visitor->getTree());

    delete builder;
    delete parser;
    delete visitor;
}


TEST_F(ParserTest, buildVisitorFolder) {
    FileSystemBuilder * builder = new FileSystemBuilder();
    FileSystemParser * parser = new FileSystemParser(builder);
    
    parser->setPath(visitor_folder->path());
    parser->parse();

    TreeVisitor * visitor = new TreeVisitor(OrderBy::Name);
    visitor_folder->accept(visitor);

    string expect = ".\n";

    expect += "├── file1.txt\n";
    expect += "├── file2.txt\n";
    expect += "└── nested\n";
    expect += "    ├── file3.txt\n";
    expect += "    └── file4.txt\n";

    EXPECT_EQ(expect, visitor->getTree());

    delete builder;
    delete parser;
    delete visitor;
}
