#pragma once 

#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/iterator.h"
#include "../src/dfs_iterator.h"

class IteratorTest: public ::testing::Test {
protected:
    virtual void SetUp() {
        home = new Folder("/Users/user/home");

        profile = new File("/Users/user/home/my_profile");
        home->add(profile);

        document = new Folder("/Users/user/home/Documents");
        home->add(document);

        favorite = new Folder("/Users/user/home/Documents/favorites");
        document->add(favorite);
        ddd = new File("/Users/user/home/Documents/favorites/domain-driven-design.pdf");
        favorite->add(ddd);
        ca = new File("/Users/user/home/Documents/favorites/clean-architecture.pdf");
        favorite->add(ca);
        cqrs = new File("/Users/user/home/Documents/favorites/cqrs.pdf");
        favorite->add(cqrs);

        note = new File("/Users/user/home/Documents/note.txt");
        document->add(note);

        download = new Folder("/Users/user/home/Downloads");
        home->add(download);

        funny = new File("/Users/user/home/Downloads/funny.png");
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
};

TEST_F(IteratorTest, Normal) {
    Iterator * it = home->createIterator();
    it->first();
    ASSERT_FALSE(it->isDone());
    
    ASSERT_EQ("my_profile", it->currentItem()->name());
    
    it->next();
    ASSERT_EQ("Documents", it->currentItem()->name());

    it->next();
    ASSERT_EQ("Downloads", it->currentItem()->name());

    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorTest, DFS) {
    Iterator * dfsIt = new DfsIterator(home);

    dfsIt->first();
    ASSERT_EQ("my_profile", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("Documents", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("favorites", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("domain-driven-design.pdf", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("clean-architecture.pdf", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("cqrs.pdf", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("note.txt", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("Downloads", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("funny.png", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_TRUE(dfsIt->isDone());
}


TEST_F(IteratorTest, BFS) {
    Iterator * bfsIt = new BfsIterator(home);

    bfsIt->first();
    ASSERT_EQ("my_profile", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("Documents", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("Downloads", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("favorites", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("note.txt", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("funny.png", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("domain-driven-design.pdf", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("clean-architecture.pdf", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("cqrs.pdf", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_TRUE(bfsIt->isDone());
}
