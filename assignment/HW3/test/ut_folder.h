#include <string>
#include "../src/folder.h"

using namespace std;

TEST(Folder, normal) {
    Folder home("structure/home");

    ASSERT_EQ("home", home.name());
    ASSERT_EQ("structure/home", home.path());
}

TEST(Folder, invalid_folder) {
    ASSERT_ANY_THROW(Folder("/NOT/EXIST/PATH"));
}

TEST(Folder, invalid_folder_2) {
    ASSERT_ANY_THROW(Folder("structure/home/Documents/hello.txt"));
}

TEST(Folder, add_file) {
    Folder home("structure/home");
    File hello("structure/home/hello.txt");
    home.add(&hello);

    ASSERT_EQ("hello.txt", home.getChildByName("hello.txt")->name());
}

TEST(Folder, add_incorrect_path_file_to_folder) {
    Folder home("structure/home");
    File hello("structure/home/Documents/hello.txt");
    ASSERT_ANY_THROW(home.add(&hello));
}

TEST(Folder, add_folder) {
    Folder home("structure/home");
    Folder document("structure/home/Documents");

    home.add(&document);

    ASSERT_EQ("Documents", home.getChildByName("Documents")->name());
}
