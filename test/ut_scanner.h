#pragma once

#include "../src/json_scanner.h"

#include <string>

using std::string;

TEST(ScannerSuite, Normal) {
    string pair = "{\"key\": \"value\"}";

    JsonScanner * scanner = new JsonScanner();
    scanner->setInput(pair);

    EXPECT_EQ('{', scanner->next());
    EXPECT_EQ('"', scanner->next());
    EXPECT_EQ('k', scanner->next());
    EXPECT_EQ('e', scanner->next());
    EXPECT_EQ('y', scanner->next());
    EXPECT_EQ('"', scanner->next());
    EXPECT_EQ(':', scanner->next());
    EXPECT_EQ(' ', scanner->next());

    EXPECT_EQ('"', scanner->next());
    EXPECT_EQ('v', scanner->next());
    EXPECT_EQ('a', scanner->next());
    EXPECT_EQ('l', scanner->next());
    EXPECT_EQ('u', scanner->next());
    EXPECT_EQ('e', scanner->next());
    EXPECT_EQ('"', scanner->next());
    EXPECT_EQ('}', scanner->next());
    
    scanner->next();
    EXPECT_TRUE(scanner->isDone());

    delete scanner;
}