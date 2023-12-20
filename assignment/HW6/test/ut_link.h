#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/link.h"

class LinkTest: public ::testing::Test {
protected:
    void SetUp() {
        home = new Folder("structure/home");

        profile = new File("structure/home/my_profile");
        home->add(profile);

        download = new Folder("structure/home/Downloads");
        home->add(download);

        document = new Folder("structure/home/Documents");
        home->add(document);

        note = new File("structure/home/Documents/note.txt");
        document->add(note);

        favorite = new Folder("structure/home/Documents/favorites");
        document->add(favorite);
        ddd = new File("structure/home/Documents/favorites/domain-driven-design.pdf");
        favorite->add(ddd);
        ca = new File("structure/home/Documents/favorites/clean-architecture.pdf");
        favorite->add(ca);
        cqrs = new File("structure/home/Documents/favorites/cqrs.pdf");
        favorite->add(cqrs);
    }

    void TearDown() {
        delete home;
        home = nullptr;
        profile = nullptr;
        download = nullptr;
        document = nullptr;
        note = nullptr;
        favorite = nullptr;
        ddd = nullptr;
        ca = nullptr;
        cqrs = nullptr;
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
};

TEST_F(LinkTest, LinkToFile) {
    Link * link = new Link("structure/home/Documents/note.txt", note);

    EXPECT_EQ(1, link->numberOfFiles());
    EXPECT_EQ(note, link->find(note->path()));
    EXPECT_EQ(1, link->findByName(note->name()).size());
}

TEST_F(LinkTest, LinkToFolder) {
    Link * link = new Link("structure/link_to_home", home);

    EXPECT_EQ(5, link->numberOfFiles());
    EXPECT_EQ(home, link->find(home->path()));
    EXPECT_EQ(1, link->findByName("cqrs.pdf").size());
    EXPECT_EQ(document, link->getChildByName("Documents"));
    
    link->remove("structure/home/Documents");
    EXPECT_EQ(1, link->numberOfFiles());
}