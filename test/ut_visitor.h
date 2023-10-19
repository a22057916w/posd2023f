#pragma once

#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/find_by_name_visitor.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

class VisitorTest: public ::testing::Test {
protected:
    void SetUp() {
        home = new Folder("/Users/user/home");

        profile = new File("/Users/user/home/my_profile");
        home->add(profile);

        download = new Folder("/Users/user/home/Downloads");
        home->add(download);

        document = new Folder("/Users/user/home/Documents");
        home->add(document);

        note1 = new File("/Users/user/home/Documents/note.txt");
        document->add(note1);

        note2 = new File("/Users/user/home/Downloads/note.txt");
        download->add(note2);

        favorite = new Folder("/Users/user/home/Documents/favorites");
        document->add(favorite);
        ddd = new File("/Users/user/home/Documents/favorites/domain-driven-design.pdf");
        favorite->add(ddd);
        ca = new File("/Users/user/home/Documents/favorites/clean-architecture.pdf");
        favorite->add(ca);
        cqrs = new File("/Users/user/home/Documents/favorites/cqrs.pdf");
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

TEST_F(VisitorTest, FindByNameVisitorFolderWithSameFileNames) {
    FindByNameVisitor * visitor = new FindByNameVisitor("note.txt");
    home->accept(visitor);

    EXPECT_EQ("home", home->name());
    EXPECT_EQ(2, visitor->getPaths().size());
    EXPECT_EQ("/Users/user/home/Downloads/note.txt", visitor->getPaths().front());
    
}

TEST_F(VisitorTest, Istat) {
    struct stat sb;
    int i = stat("Users/user/home/Documents/note.txt", &sb);
    EXPECT_EQ(0, i);
}