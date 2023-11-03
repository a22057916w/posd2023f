#pragma once

#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/stream_out_visitor.h"

#include <string>

using std::string;


class StreamOutVisitorTest: public ::testing::Test {
protected:
    void SetUp() {
        home = new Folder("./test/Users/user/home");

        hello = new File("./test/Users/user/home/hello.txt");
        home->add(hello);

        document = new Folder("./test/Users/user/home/Documents");
        home->add(document);

        note = new File("./test/Users/user/home/Documents/note.txt");
        document->add(note);
    }

    void TearDown() {
        delete home;
        delete hello;
        delete document;
        delete note;
    }

    Node * home;
    Node * hello;
    Node * document;
    Node * note;
    
};

TEST_F(StreamOutVisitorTest, StreamOutFile) {
    StreamOutVisitor * visitor = new StreamOutVisitor();

    hello->accept(visitor);
    string expect_output = "_____________________________________________\n./test/Users/user/home/hello.txt\n---------------------------------------------\nhello, world\r\nhello\n_____________________________________________\n";
    EXPECT_EQ(expect_output, visitor->getResult());

    delete visitor;
}

TEST_F(StreamOutVisitorTest, StreamOutFolder) {
    StreamOutVisitor * visitor = new StreamOutVisitor();

    home->accept(visitor);
    string expect_output = "_____________________________________________\n./test/Users/user/home/hello.txt\n---------------------------------------------\nhello, world\r\nhello\n_____________________________________________\n\n_____________________________________________\n./test/Users/user/home/Documents/note.txt\n---------------------------------------------\nhello, world\n_____________________________________________\n\n";
    EXPECT_EQ(expect_output, visitor->getResult());

    delete visitor;
}