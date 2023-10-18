#pragma once

#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/find_by_name_visitor.h"

class VisitorTest: public ::testing::Test {
    void SetUp() {
        home = new Folder("/Users/user/home");

        profile = new File("/Users/user/home/my_profile");
        home->add(profile);

        download = new Folder("/Users/user/home/Downloads");
        home->add(download);

        document = new Folder("/Users/user/home/Documents");
        home->add(document);

        note = new File("/Users/user/home/Documents/note.txt");
        document->add(note);

        favorite = new Folder("/Users/user/home/Documents/favorites");
        document->add(favorite);
        ddd = new File("/Users/user/home/Documents/favorites/domain-driven-design.pdf");
        favorite->add(ddd);
        ca = new File("/Users/user/home/Documents/favorites/clean-architecture.pdf");
        favorite->add(ca);
        cqrs = new File("/Users/user/home/Documents/favorites/cqrs.pdf");
        favorite->add(cqrs);
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
}