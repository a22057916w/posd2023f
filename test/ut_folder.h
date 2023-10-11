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

    root->setIteratorType("Folder");
    FolderIterator *_it = dynamic_cast<FolderIterator *>(root->createIterator());

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
    
    root->setIteratorType("Bfs");
    BfsIterator * _it = dynamic_cast<BfsIterator *>(root->createIterator());

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

TEST(FolderSuite, DfsIterator) {
    Folder * root = new Folder("root");
    Folder * home = new Folder("root/home");

    File * fileA = new File("root/fileA.txt");
    File * fileB = new File("root/home/fileB.txt");
    File * fileC = new File("root/fileC.txt");

    home->add(fileB);
    root->add(fileC);
    root->add(home);
    root->add(fileA);
    
    root->setIteratorType("Dfs");
    DfsIterator * _it = dynamic_cast<DfsIterator *>(root->createIterator());

    // _it->first();
    // EXPECT_EQ(_it->currentItem()->path(), "root/fileA.txt");

    // _it->next();
    // EXPECT_EQ(_it->currentItem()->path(), "root/home");

    // _it->next();
    // EXPECT_EQ(_it->currentItem()->path(), "root/home/fileB.txt");

    // _it->next();
    // EXPECT_EQ(_it->currentItem()->path(), "root/fileA.txt");

    // _it->next();
    // EXPECT_TRUE(_it->isDone());

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

    delete root;
    delete home;
    delete fileA;
    delete fileB;
    delete fileC;
}

TEST(FolderSuite, Find) {
    Folder * root = new Folder("root");
    Folder * home = new Folder("root/home");

    File * fileA = new File("root/fileA.txt");    
    File * fileB = new File("root/home/fileB.txt");

    home->add(fileB);
    root->add(fileA);
    root->add(home);

    Node * node = root->find("root/fileA.txt");
    EXPECT_EQ(node->path(), "root/fileA.txt");

    node = root->find("root/home/fileB.txt");
    EXPECT_EQ(node->path(), "root/home/fileB.txt");

    delete root;
    delete home;
    delete fileA;
    delete fileB; // also delete node
}

TEST(Folder, getChildByName) {
    Folder * root = new Folder("root");
    Folder * home = new Folder("root/home");

    File * fileA = new File("root/home/fileA.txt");

    home->add(fileA);
    root->add(home);

    Node * node = root->getChildByName("fileA.txt");
    EXPECT_EQ(node->path(), "root/home/fileA.txt");

    delete root;
    delete home;
    delete fileA;
}

TEST(FolderSuite, RemoveFiles) {
    Folder * root = new Folder("root");
    Folder * home = new Folder("root/home");

    File * fileA = new File("root/fileA.txt");
    File * fileB = new File("root/fileB.txt");
    File * fileC = new File("root/home/fileC.txt");

    home->add(fileC);
    root->add(fileA);
    root->add(fileB);
    root->add(home);

    root->remove("root/home/fileC.txt");
    EXPECT_EQ(2, root->numberOfFiles());

    // fileC has alredy been remove(delete)
    delete root;
    delete home;
    delete fileA;
    delete fileB;
}