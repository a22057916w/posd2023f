#pragma once 

#include "../src/file.h"
#include "../src/find_by_name_visitor.h"

TEST(FileTest, normal) {
    File hello("/Users/user/home/hello.txt");
    ASSERT_EQ("hello.txt", hello.name());
    ASSERT_EQ("/Users/user/home/hello.txt", hello.path());
}

TEST(FileTest, VisitFindByName) {
    File * hello = new File("/Users/user/home/hello.txt");
    FindByNameVisitor * visitor = new FindByNameVisitor("hello.txt");
    
    hello->accept(visitor);
    EXPECT_EQ(1, visitor->getPaths().size());
    EXPECT_EQ("/Users/user/home/hello.txt", visitor->getPaths().front());

    delete hello;
    delete visitor;
}