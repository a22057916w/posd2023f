#pragma once

#include "../src/json_builder.h"
#include "../src/json_scanner.h"
#include "../src/json_parser.h"
#include "../src/json_object.h"
#include "../src/beautify_visitor.h"
#include "../src/string_value.h"

#include <string>

using std::string;

TEST(ParserSuite, OneKeyStringValue) {
    string input = "{\"desc\": \"Product\"}";

    JsonBuilder * builder = new JsonBuilder();
    JsonScanner * scanner = new JsonScanner();
    JsonParser * parser = new JsonParser(scanner, builder);
    parser->setInput(input);
    parser->parse();

    JsonObject * jo = parser->getJsonObject();

    string expect = "";
    expect += "{\n";
    expect += "    \"desc\": \"Product\"\n";
    expect += "}";

    BeautifyVisitor * visitor = new BeautifyVisitor();
    jo->accept(visitor);

    EXPECT_EQ(expect, visitor->getResult());

    delete visitor;
    delete builder;
    delete scanner;
    delete parser;
    delete jo;
}

TEST(parserSuite, MultipleKeyStringValueWithSpace) {
    string input = "{  \"id\"  :\"10\",\"desc\"  :  \"A Product\"  ,          \"isDeleted\"    :  \"false\"}";

    JsonBuilder * builder = new JsonBuilder();
    JsonScanner * scanner = new JsonScanner();
    JsonParser * parser = new JsonParser(scanner, builder);
    parser->setInput(input);
    parser->parse();

    JsonObject * jo = parser->getJsonObject();

    string expect = "";
    expect += "{\n";
    expect += "    \"desc\": \"A Product\",\n";
    expect += "    \"id\": \"10\",\n";
    expect += "    \"isDeleted\": \"false\"\n";
    expect += "}";

    BeautifyVisitor * visitor = new BeautifyVisitor();
    jo->accept(visitor);

    EXPECT_EQ(expect, visitor->getResult());

    delete visitor;
    delete builder;
    delete scanner;
    delete parser;
    delete jo;
}

TEST(parserSuite, Composite) {
    string input = "{\"id\":\"10\",\"desc\":\"Product\",\"isDeleted\":\"false\",\"details\":{\"title\":\"BBBB\"}}";

    JsonBuilder * builder = new JsonBuilder();
    JsonScanner * scanner = new JsonScanner();
    JsonParser * parser = new JsonParser(scanner, builder);
    parser->setInput(input);
    parser->parse();

    JsonObject * jo = parser->getJsonObject();

    string expect = "";
    expect += "{\n";
    expect += "    \"desc\": \"Product\",\n";
    expect += "    \"details\": {\n";
    expect += "        \"title\": \"BBBB\"\n";
    expect += "    },\n";
    expect += "    \"id\": \"10\",\n";
    expect += "    \"isDeleted\": \"false\"\n";
    expect += "}";

    BeautifyVisitor * visitor = new BeautifyVisitor();
    jo->accept(visitor);

    EXPECT_EQ(expect, visitor->getResult());

    delete visitor;
    delete builder;
    delete scanner;
    delete parser;
    delete jo;
}

TEST(ParserSuite, BeautifiedJsonFormat) {
    string input = "{\"books\": { "\
    "\"design patterns\": {\"name\":\"Design Patterns: Elements of Reusable Object-Oriented Software\","\
    "\"author\":\"Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides\"},\"clean code\":{"\
    "\"name\": \"Clean Code\",\"author\": \"Robert C. Martin\"}}}";

    JsonBuilder * builder = new JsonBuilder();
    JsonScanner * scanner = new JsonScanner();
    JsonParser * parser = new JsonParser(scanner, builder);
    parser->setInput(input);
    parser->parse();

    JsonObject * jo = parser->getJsonObject();

    BeautifyVisitor * visitor = new BeautifyVisitor();
    jo->accept(visitor);

    string expect = ""; 
    expect += "{\n";
    expect += "    \"books\": {\n";
    expect += "        \"clean code\": {\n";
    expect += "            \"author\": \"Robert C. Martin\",\n";
    expect += "            \"name\": \"Clean Code\"\n";
    expect += "        },\n";
    expect += "        \"design patterns\": {\n";
    expect += "            \"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides\",\n";
    expect += "            \"name\": \"Design Patterns: Elements of Reusable Object-Oriented Software\"\n";
    expect += "        }\n";
    expect += "    }\n}";

    EXPECT_EQ(expect, visitor->getResult());

    delete visitor;
    delete builder;
    delete scanner;
    delete parser;
    delete jo;
}