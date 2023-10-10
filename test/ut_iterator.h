#pragma once

#include "../src/iterator.h"
#include "../src/folder.h"

TEST(IeratorSuite, Ping) {
    ASSERT_TRUE(true);
}

TEST(IteratorSuite, CreateIterator) {
    Node * home = new Folder("home");
    Iterator * it = home->createIterator();
}