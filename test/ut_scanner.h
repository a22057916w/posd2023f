#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/file_system_scanner.h"

#include <string>
#include <dirent.h>

using std::string;

class ScannerTest: public ::testing::Test {
protected:
    virtual void SetUp() {
        home = new Folder("structure/home");

        profile = new File("structure/home/my_profile");
        home->add(profile);

        document = new Folder("structure/home/Documents");
        home->add(document);

        hello = new File("structure/home/hello.txt");
        home->add(hello);

        favorite = new Folder("structure/home/Documents/favorites");
        document->add(favorite);
        ddd = new File("structure/home/Documents/favorites/domain-driven-design.pdf");
        favorite->add(ddd);
        ca = new File("structure/home/Documents/favorites/clean-architecture.pdf");
        favorite->add(ca);
        cqrs = new File("structure/home/Documents/favorites/cqrs.pdf");
        favorite->add(cqrs);

        note = new File("structure/home/Documents/note.txt");
        document->add(note);

        download = new Folder("structure/home/Downloads");
        home->add(download);

        funny = new File("structure/home/Downloads/funny.png");
        download->add(funny);
    }

    void TearDown() {
        delete home;
        delete profile;
        delete download;
        delete document;
        delete note;
        delete favorite;
        delete ddd;
        delete ca;
        delete cqrs;
        delete funny;
        delete hello;
    }
    
    Node * home;
    Node * profile;
    Node * download;
    Node * document;
    Node * note;
    Node * favorite;
    Node * ddd;
    Node * ca;
    Node * cqrs;
    Node * funny;
    Node * hello;
};

// TEST_F(ScannerTest, Normal) {
//     FileSystemScanner * scanner = new FileSystemScanner();
    
//     scanner->setPath(home->path());
//     EXPECT_FALSE(scanner->isDone());


//     //  ***** pass in local *******
//     scanner->nextNode();
//     EXPECT_EQ(profile->name(), scanner->currentNodeName());
//     EXPECT_TRUE(scanner->isFile());

//     scanner->nextNode();
//     EXPECT_EQ(document->name(), scanner->currentNodeName());
//     EXPECT_TRUE(scanner->isFolder());

//     scanner->nextNode();
//     EXPECT_EQ(download->name(), scanner->currentNodeName());
//     EXPECT_TRUE(scanner->isFolder());

//     scanner->nextNode();
//     EXPECT_EQ(hello->name(), scanner->currentNodeName());
//     EXPECT_TRUE(scanner->isFile());

//     scanner->nextNode();
//     EXPECT_TRUE(scanner->isDone());

//     delete scanner;
// }

// TEST_F(ScannerTest, currentNodePath) {
//     FileSystemScanner * scanner = new FileSystemScanner();
//     scanner->setPath(download->path());

//     scanner->nextNode();
//     EXPECT_EQ(funny->path(), scanner->currentNodePath());

//     delete scanner;
// }