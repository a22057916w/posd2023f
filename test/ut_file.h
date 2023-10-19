#pragma once

#include "../src/file.h"
#include "../src/find_by_name_visitor.h"

#include <string>

using std::string;

// const string _cwd = "/Users/willy/Documents/code/posd2023f";
#define CWD "/Users/willy/Documents/code/posd2023f"

TEST(FileTest, CreateSuccess)
{
    File * hello = new File(CWD "/Users/user/home/hello.txt");
    ASSERT_EQ(hello->path(), "/Users/willy/Documents/code/posd2023f/Users/user/home/hello.txt");
}

TEST(FileTest, CreateFail) {
    EXPECT_THROW(File random(CWD "/User/random"), string);
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