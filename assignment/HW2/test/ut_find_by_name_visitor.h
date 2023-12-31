#pragma once

#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/find_by_name_visitor.h"

#include <string>

using std::string;


class FindByNameVisitorTest: public ::testing::Test {
protected:
    void SetUp() {
        home = new Folder("./test/Users/user/home");

        profile = new File("./test/Users/user/home/my_profile");
        home->add(profile);

        download = new Folder("./test/Users/user/home/Downloads");
        home->add(download);

        document = new Folder("./test/Users/user/home/Documents");
        home->add(document);

        note1 = new File("./test/Users/user/home/Documents/note.txt");
        document->add(note1);

        note2 = new File("./test/Users/user/home/Downloads/note.txt");
        download->add(note2);

        favorite = new Folder("./test/Users/user/home/Documents/favorites");
        document->add(favorite);
        ddd = new File("./test/Users/user/home/Documents/favorites/domain-driven-design.pdf");
        favorite->add(ddd);
        ca = new File("./test/Users/user/home/Documents/favorites/clean-architecture.pdf");
        favorite->add(ca);
        cqrs = new File("./test/Users/user/home/Documents/favorites/cqrs.pdf");
        favorite->add(cqrs);
    }

    void TearDown() {
        delete home;
        delete profile;
        delete download;
        delete document;
        delete note1;
        delete note2;
        delete favorite;
        delete ddd;
        delete ca;
        delete cqrs;
    }

    Node * home;
    Node * profile;
    Node * download;
    Node * document;
    Node * note1;
    Node * note2;
    Node * favorite;
    Node * ddd;
    Node * ca;
    Node * cqrs;
};

TEST_F(FindByNameVisitorTest, FileFound) {
    FindByNameVisitor * visitor = new FindByNameVisitor("cqrs.pdf");
    
    cqrs->accept(visitor);
    EXPECT_EQ(1, visitor->getPaths().size());
    EXPECT_EQ("./test/Users/user/home/Documents/favorites/cqrs.pdf", visitor->getPaths().front());
    delete visitor;
}

TEST_F(FindByNameVisitorTest, FileNotFound) {
    FindByNameVisitor * visitor = new FindByNameVisitor("empty.none");

    cqrs->accept(visitor);
    EXPECT_EQ(0, visitor->getPaths().size());

    delete visitor;
}

TEST_F(FindByNameVisitorTest, FileWillNotFoundFloder) {
    FindByNameVisitor * visitor = new FindByNameVisitor("empty");

    cqrs->accept(visitor);
    EXPECT_EQ(0, visitor->getPaths().size());

    delete visitor;
}

TEST_F(FindByNameVisitorTest, FolderFound) {
    FindByNameVisitor * visitor = new FindByNameVisitor("home");
    
    home->accept(visitor);
    EXPECT_EQ(1, visitor->getPaths().size());
    EXPECT_EQ("./test/Users/user/home", visitor->getPaths().front());
    delete visitor;
}

TEST_F(FindByNameVisitorTest, FolderNotFound) {
    FindByNameVisitor * visitor = new FindByNameVisitor("root");
    
    home->accept(visitor);
    EXPECT_EQ(0, visitor->getPaths().size());
    
    delete visitor;
}

TEST_F(FindByNameVisitorTest, FolderFoundNoFile) {
    FindByNameVisitor * visitor = new FindByNameVisitor("empty.none");
    
    home->accept(visitor);
    EXPECT_EQ(0, visitor->getPaths().size());
    
    delete visitor;
}


TEST_F(FindByNameVisitorTest, FolderFoundOneFile) {
    FindByNameVisitor * visitor = new FindByNameVisitor("domain-driven-design.pdf");

    home->accept(visitor);
    EXPECT_EQ(1, visitor->getPaths().size());
    EXPECT_EQ("./test/Users/user/home/Documents/favorites/domain-driven-design.pdf", visitor->getPaths().front());

    delete visitor;
}

TEST_F(FindByNameVisitorTest, FolderFoundManyFile) {
    FindByNameVisitor * visitor = new FindByNameVisitor("note.txt");
    home->accept(visitor);

    EXPECT_EQ("home", home->name());
    EXPECT_EQ(2, visitor->getPaths().size());
    EXPECT_EQ("./test/Users/user/home/Downloads/note.txt", visitor->getPaths().front());
    
    delete visitor;
}