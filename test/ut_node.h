#pragma once 

#include "../src/constants.h"
#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"

using Constants::CWD;

class NodeTest: public ::testing::Test {
protected:
    void SetUp() {
        home = new Folder(CWD + "/Users/user/home");

        profile = new File(CWD + "/Users/user/home/my_profile");
        home->add(profile);

        download = new Folder(CWD + "/Users/user/home/Downloads");
        home->add(download);

        document = new Folder(CWD + "/Users/user/home/Documents");
        home->add(document);

        note = new File(CWD + "/Users/user/home/Documents/note.txt");
        document->add(note);

        favorite = new Folder(CWD + "/Users/user/home/Documents/favorites");
        document->add(favorite);
        ddd = new File(CWD + "/Users/user/home/Documents/favorites/domain-driven-design.pdf");
        favorite->add(ddd);
        ca = new File(CWD + "/Users/user/home/Documents/favorites/clean-architecture.pdf");
        favorite->add(ca);
        cqrs = new File(CWD + "/Users/user/home/Documents/favorites/cqrs.pdf");
        favorite->add(cqrs);
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

    
};


TEST_F(NodeTest, numberOfFiles) {
    ASSERT_EQ(5, home->numberOfFiles());
}

TEST_F(NodeTest, find_a_file) {
    Node * result = home->find(CWD + "/Users/user/home/Documents/favorites/cqrs.pdf");
    ASSERT_EQ(cqrs, result);
}

TEST_F(NodeTest, find_a_file_not_exist) {
    Node * result = home->find(CWD + "/Users/user/home/Documents/favorites/helloworld.pdf");
    ASSERT_EQ(nullptr, result);
}

TEST_F(NodeTest, find_a_folder) {
    Node * result = document->find(CWD + "/Users/user/home/Documents/favorites");
    ASSERT_EQ(favorite, result);
}

TEST_F(NodeTest, find_a_folder_not_exist) {
    Node * result = document->find(CWD + "/Users/user/home/Documents/not_like");
    ASSERT_EQ(nullptr, result);
}

TEST_F(NodeTest, delete_a_file) {
    ASSERT_EQ(cqrs->name(), home->find(CWD + "/Users/user/home/Documents/favorites/cqrs.pdf")->name());
    home->remove(CWD + "/Users/user/home/Documents/favorites/cqrs.pdf");
    ASSERT_EQ(nullptr, home->find(CWD + "/Users/user/home/Documents/favorites/cqrs.pdf"));
}

TEST_F(NodeTest, delete_a_folder) {
    ASSERT_EQ(favorite->name(), home->find(CWD + "/Users/user/home/Documents/favorites")->name());
    home->remove(CWD + "/Users/user/home/Documents/favorites");
    ASSERT_EQ(nullptr, home->find(CWD + "/Users/user/home/Documents/favorites"));
}
