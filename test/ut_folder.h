#pragma once 

#include "../src/constants.h"
#include "../src/folder.h"
#include "../src/file.h"

#include <string>

using std::string;
using Constants::CWD;

TEST(Folder, createFolderSuccess) {
    Folder * download = new Folder(CWD + "/Users/user/home/downloads");
    EXPECT_EQ(CWD + "/Users/user/home/downloads", download->path());
    delete download;
}

TEST(Folder, createFolderFail) {
    EXPECT_ANY_THROW(new Folder(CWD + "/User/user/device"));
}

TEST(Folder, createFileFail) {
    EXPECT_ANY_THROW(new Folder(CWD + "/Users/user/home/hello.txt"));
}

TEST(Folder, normal) {
    Folder home(CWD + "/Users/user/home");

    ASSERT_EQ("home", home.name());
    ASSERT_EQ(CWD + "/Users/user/home", home.path());
}

TEST(Folder, add_file) {
    Folder home(CWD + "/Users/user/home");
    File hello(CWD + "/Users/user/home/hello.txt");
    
    home.add(&hello);
    ASSERT_EQ("hello.txt", home.getChildByName("hello.txt")->name());
}

TEST(Folder, add_incorrect_path_file_to_folder) {
    Folder home(CWD + "/Users/user/home");
    File note(CWD + "/Users/user/home/Documents/note.txt");
    ASSERT_ANY_THROW(home.add(&note));
}

TEST(Folder, add_folder) {
    Folder home(CWD + "/Users/user/home");
    Folder document(CWD + "/Users/user/home/Documents");

    home.add(&document);

    ASSERT_EQ("Documents", home.getChildByName("Documents")->name());
}