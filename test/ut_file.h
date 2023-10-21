#pragma once

#include "../src/file.h"
#include "../src/find_by_name_visitor.h"

#include <string>

using std::string;

TEST(FileTest, CreateFileSuccess) {
    File * cqrs = new File("./test/Users/user/home/Documents/favorites/cqrs.pdf");
    ASSERT_EQ(cqrs->path(), "./test/Users/user/home/Documents/favorites/cqrs.pdf");
    delete cqrs;
}

TEST(FileTest, CreateFileFail) {
    EXPECT_ANY_THROW(File random("./test/User/random.txt"));
}

TEST(FileTest, createFolderFail) {
    EXPECT_ANY_THROW(File home("./test/Users/user/home"));
}

TEST(FileTest, FindFileExist) {
    Node * cqrs = new File("./test/Users/user/home/Documents/favorites/cqrs.pdf");
    EXPECT_EQ(cqrs, cqrs->find("./test/Users/user/home/Documents/favorites/cqrs.pdf"));
    delete cqrs;
}

TEST(FileTest, FindFileNotExist) {
    Node * cqrs = new File("./test/Users/user/home/Documents/favorites/cqrs.pdf");
    EXPECT_EQ(nullptr, cqrs->find("./test/Users/user/home/note.txt"));
    delete cqrs;
}

TEST(FileTest, NumberOfFiles) {
    Node * cqrs = new File("./test/Users/user/home/Documents/favorites/cqrs.pdf");
    EXPECT_EQ(1, cqrs->numberOfFiles());
    delete cqrs;
}

TEST(FileTest, VisitFindByName) {
    File * cqrs = new File("./test/Users/user/home/Documents/favorites/cqrs.pdf");
    FindByNameVisitor * visitor = new FindByNameVisitor("cqrs.pdf");

    cqrs->accept(visitor);
    EXPECT_EQ(1, visitor->getPaths().size());
    EXPECT_EQ("./test/Users/user/home/Documents/favorites/cqrs.pdf", visitor->getPaths().front());

    delete cqrs;
    delete visitor;
}