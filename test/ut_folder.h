#pragma once 

#include <string>
#include "../src/folder.h"

using namespace std;

TEST(Folder, normal) {
    Folder home("/Users/user/home");

    ASSERT_EQ("home", home.name());
    ASSERT_EQ("/Users/user/home", home.path());
}

TEST(Folder, add_file) {
    Folder home("/Users/user/home");
    File hello("/Users/user/home/hello.txt");
    home.add(&hello);

    ASSERT_EQ("hello.txt", home.getChildByName("hello.txt")->name());
}

TEST(Folder, add_incorrect_path_file_to_folder) {
    Folder home("/Users/user/home");
    File hello("/Users/user/home/Documents/hello.txt");
    ASSERT_ANY_THROW(home.add(&hello));
}

TEST(Folder, add_folder) {
    Folder home("/Users/user/home");
    Folder document("/Users/user/home/Documents");

    home.add(&document);

    ASSERT_EQ("Documents", home.getChildByName("Documents")->name());
}