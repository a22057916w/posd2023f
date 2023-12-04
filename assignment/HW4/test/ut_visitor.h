#pragma once

#include "../src/beautify_visitor.h"
#include "../src/json_object.h"
#include "../src/string_value.h"
#include "../src/json_iterator.h"

#include <string>

using std::string;

TEST(VisitorSuite, OneKeyStringValue) {
    JsonObject * jo = new JsonObject();
    Value * desc = new StringValue("Product");

    jo->set("desc", desc);

    string expect = "";
    expect += "{\n";
    expect += "    \"desc\": \"Product\"\n";
    expect += "}";

    BeautifyVisitor * visitor = new BeautifyVisitor();
    jo->accept(visitor);

    EXPECT_EQ(expect, visitor->getResult());

    delete visitor;
    delete desc;
    delete jo;
}


TEST(VisitorSuite, MultipleKeyStringValues) {
    JsonObject * jo = new JsonObject();
    Value * desc = new StringValue("Product");
    Value * id = new StringValue("10");
    Value * isDeleted = new StringValue("false");

    jo->set("desc", desc);
    jo->set("id", id);
    jo->set("isDeleted", isDeleted);

    string expect = "";
    expect += "{\n";
    expect += "    \"desc\": \"Product\",\n";
    expect += "    \"id\": \"10\",\n";
    expect += "    \"isDeleted\": \"false\"\n";
    expect += "}";

    BeautifyVisitor * visitor = new BeautifyVisitor();
    jo->accept(visitor);

    EXPECT_EQ(expect, visitor->getResult());

    delete visitor;
    delete desc;
    delete id;
    delete isDeleted;
    delete jo;
}

TEST(VisitorSuite, Composite) {
    JsonObject * root = new JsonObject();
    JsonObject * book = new JsonObject();
    JsonObject * clean = new JsonObject();
    JsonObject * design = new JsonObject();

    Value * author1 = new StringValue("Robert C. Martin");
    Value * name1 = new StringValue("Clean Code");
    clean->set("author", author1);
    clean->set("name", name1);

    Value * author2 = new StringValue("Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides");
    Value * name2 = new StringValue("Design Patterns: Elements of Reusable Object-Oriented Software");
    design->set("author", author2);
    design->set("name", name2);

    book->set("clean code", clean);
    book->set("design patterns", design);
   
    root->set("books", book);

    BeautifyVisitor * visitor = new BeautifyVisitor();
    root->accept(visitor);

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
    delete author1;
    delete author2;
    delete name1;
    delete name2;
    delete clean;
    delete design;
    delete book;
    delete root;
}