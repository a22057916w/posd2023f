#pragma once

#include "../src/node.h"
#include "../src/folder.h"
#include "../src/iterator.h"
#include "../src/dfs_iterator.h"

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

TEST(FolderSuite, ValidFileAdd) {
    Folder * folder = new Folder("test/dir1/dir2");
    Node * file = new File("test/dir1/dir2/hello.txt");

    folder->add(file);
    EXPECT_EQ(1, folder->components().size());

    delete folder;
    delete file;
}

TEST(FolderSuite, ValidFolderAdd) {
    Folder * root = new Folder("root");
    Folder * home = new Folder("root/home");

    root->add(home);
    EXPECT_EQ(1, root->components().size());

    delete root;
    delete home;
}


TEST(FolderSuite, FolderIterator) {
    Folder * root = new Folder("root");
    Folder * home = new Folder("root/home");

    File * file = new File("root/hello.txt");

    root->add(home);
    root->add(file);

    FolderIterator *_it = dynamic_cast<FolderIterator *>(root->createIterator("Folder"));

    _it->first();
    EXPECT_EQ(_it->currentItem()->path(), "root/home");

    _it->next();
    EXPECT_EQ(_it->currentItem()->path(), "root/hello.txt");
    
    _it->next();
    EXPECT_TRUE(_it->isDone());

    delete file;
    delete home;
    delete root;
    delete _it;
}

TEST(FolderSuite, BfsIterator) {
    Folder * root = new Folder("root");
    Folder * home = new Folder("root/home");

    File * fileA = new File("root/fileA.txt");
    File * fileB = new File("root/fileB.txt");
    File * fileC = new File("root/home/fileC.txt");

    home->add(fileC);
    root->add(fileA);
    root->add(home);
    root->add(fileB);
    
    BfsIterator * _it = dynamic_cast<BfsIterator *>(root->createIterator("Bfs"));

    _it->first();
    EXPECT_EQ(_it->currentItem()->path(), "root/fileA.txt");

    _it->next();
    EXPECT_EQ(_it->currentItem()->path(), "root/home");

    _it->next();
    EXPECT_EQ(_it->currentItem()->path(), "root/fileB.txt");

    _it->next();
    EXPECT_EQ(_it->currentItem()->path(), "root/home/fileC.txt");

    _it->next();
    EXPECT_TRUE(_it->isDone());

    delete root;
    delete home;
    delete fileA;
    delete fileB;
    delete fileC;
    delete _it;

}

TEST(FolderSuite, NumberOfFiles) {
    Folder * root = new Folder("root");
    Folder * home = new Folder("root/home");

    File * fileA = new File("root/fileA.txt");
    File * fileB = new File("root/fileB.txt");
    File * fileC = new File("root/home/fileC.txt");

    home->add(fileC);
    root->add(fileA);
    root->add(fileB);
    root->add(home);

    EXPECT_EQ(3, root->numberOfFiles());
}