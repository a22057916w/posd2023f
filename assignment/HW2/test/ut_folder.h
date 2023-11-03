#pragma once 

#include "../src/folder.h"
#include "../src/file.h"

#include <string>

using std::string;

TEST(Folder, createFolderSuccess) {
    Folder * download = new Folder("./test/Users/user/home/Downloads");
    EXPECT_EQ("./test/Users/user/home/Downloads", download->path());
    delete download;
}

TEST(Folder, createFolderFail) {
    EXPECT_ANY_THROW(new Folder("./test/User/user/device"));
}

TEST(Folder, createFileFail) {
    EXPECT_ANY_THROW(new Folder("./test/Users/user/home/hello.txt"));
}

TEST(Folder, normal) {
    Folder home("./test/Users/user/home");

    ASSERT_EQ("home", home.name());
    ASSERT_EQ("./test/Users/user/home", home.path());
}

TEST(Folder, add_file) {
    Folder home("./test/Users/user/home");
    File hello("./test/Users/user/home/hello.txt");
    
    home.add(&hello);
    ASSERT_EQ("hello.txt", home.getChildByName("hello.txt")->name());
}

TEST(Folder, add_incorrect_path_file_to_folder) {
    Folder home("./test/Users/user/home");
    File note("./test/Users/user/home/Documents/note.txt");
    ASSERT_ANY_THROW(home.add(&note));
}

TEST(Folder, add_folder) {
    Folder home("./test/Users/user/home");
    Folder document("./test/Users/user/home/Documents");

    home.add(&document);

    ASSERT_EQ("Documents", home.getChildByName("Documents")->name());
}