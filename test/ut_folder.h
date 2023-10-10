#pragma once

#include "../src/node.h"
#include "../src/folder.h"

#include <string>

using std::string;

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
TEST(FolerSuite, GetDirectoryPaht) {
    Node * folder = new Folder("test/dir1");
    EXPECT_EQ(folder->directory(), "test");
    delete folder;
}

TEST(FolderSuite, InvalidFileAdd) {
    Node * folder = new Folder("test/dir1/dir2");
    Node * file = new File("test/dir1/hello.txt");

    testing::internal::CaptureStdout();
    folder->add(file);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "The node's path do not match with the current directory.\n");

    delete folder;
    delete file;
}

TEST(FolderSuite, InvalidFolderAdd) {
    Node * folder = new Folder("test/dir1/dir2");
    Node * child  = new Folder("test/dir1/dir3");

    testing::internal::CaptureStdout();
    folder->add(child);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "The node's path do not match with the current directory.\n");

    delete folder;
    delete child;
}

// TEST(FolderSuite, ValidFileAdd) {
//     Node * folder = new Folder("test/dir1/dir2");
//     Node * file = new File("test/dir1/dir2/dir3/hello.txt");

//     testing::internal::CaptureStdout();
//     folder->add(file);
//     string output = testing::internal::GetCapturedStdout();

//     EXPECT_EQ(1, folder->component().size());

//     delete folder;
//     delete file;
// }
