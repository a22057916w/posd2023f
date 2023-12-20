#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/iterator.h"
#include "../src/file_system_builder.h"
#include "../src/file_system_parser.h"
#include "../src/file_system_scanner.h"
#include "../src/iterator_factories.h"

TEST(FileSystemBuilder, Normal) {
    FileSystemParser * parser = new FileSystemParser(new FileSystemBuilder());
    parser->setPath("structure/home");
    parser->parse();

    Node * home = parser->getRoot();

    Iterator * it = home->createIterator(OrderByNameIteratorFactory::instance());
    it->first();
    ASSERT_FALSE(it->isDone());
    
    ASSERT_EQ("Documents", it->currentItem()->name());
    
    it->next();
    ASSERT_EQ("Downloads", it->currentItem()->name());

    it->next();
    ASSERT_EQ("hello.txt", it->currentItem()->name());

    it->next();
    ASSERT_EQ("my_profile", it->currentItem()->name());

    it->next();
    ASSERT_TRUE(it->isDone());

    delete parser;
    delete home;
    delete it;
}