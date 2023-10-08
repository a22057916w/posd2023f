#pragma once

#include "../src/node.h"
#include "../src/folder.h"

TEST(FolderSuite, Ping) {
    ASSERT_TRUE(true);
}

TEST(FolderSuite, GetFileName) {
    Node * folder = new Folder("test/dir1");
    EXPECT_TRUE(folder->name() == "dir1");
    delete folder;
}

TEST(FolderSuite, GetFolderPath) {
    Node * folder = new Folder("test/dir1");
    EXPECT_TRUE(folder->path() == "test/dir1");
    delete folder;
}

// result should same as GetFolderPath 
TEST(FolerSuite, GetFolderDirectory) {
    Node * folder = new Folder("test/dir1");
    EXPECT_EQ(folder->directory(), "test/dir1");
    delete folder;
}
