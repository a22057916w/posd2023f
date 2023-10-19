#pragma once

#include "../src/file.h"
#include "../src/find_by_name_visitor.h"

#include <string>

using std::string;

#define CWD "/Users/willy/Documents/code/posd2023f"

TEST(FileTest, CreateFileSuccess) {
    File * hello = new File(CWD "/Users/user/home/hello.txt");
    ASSERT_EQ(hello->path(), "/Users/willy/Documents/code/posd2023f/Users/user/home/hello.txt");
    delete hello;
}

TEST(FileTest, CreateFileFail) {
    EXPECT_ANY_THROW(File random(CWD "/User/random"));
}

TEST(FileTest, createFolderFail) {
    EXPECT_ANY_THROW(File home(CWD "/Users/user/home"));
}

TEST(FileTest, FindFileExist) {
    Node * hello = new File(CWD "/Users/user/home/hello.txt");
    EXPECT_EQ(hello, hello->find(CWD "/Users/user/home/hello.txt"));
    delete hello;
}

TEST(FileTest, FindFileNotExist) {
    Node * hello = new File(CWD "/Users/user/home/hello.txt");
    EXPECT_EQ(nullptr, hello->find(CWD "/Users/user/home/note.txt"));
    delete hello;
}

TEST(FileTest, NumberOFFiles) {
    Node * hello = new File(CWD "/Users/user/home/hello.txt");
    EXPECT_EQ(1, hello->numberOfFiles());
    delete hello;
}

TEST(FileTest, VisitFindByName) {
    File * hello = new File(CWD "/Users/user/home/hello.txt");
    FindByNameVisitor * visitor = new FindByNameVisitor("hello.txt");

    hello->accept(visitor);
    EXPECT_EQ(1, visitor->getPaths().size());
    EXPECT_EQ(CWD "/Users/user/home/hello.txt", visitor->getPaths().front());

    delete hello;
    delete visitor;
}