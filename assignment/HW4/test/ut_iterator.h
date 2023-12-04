#pragma once

#include "../src/json_iterator.h"
#include "../src/json_object.h"
#include "../src/string_value.h"

#include <string>

using std::string;

TEST(IteratorSuite, StringValue) {
    Value * v1 = new StringValue("value1");

    JsonIterator * it = v1->createIterator();

    EXPECT_TRUE(it->isDone());
    EXPECT_ANY_THROW(it->currentKey());
    EXPECT_ANY_THROW(it->currentValue());

    delete it;
    delete v1;
}


TEST(IteratorSuite, JsonObject) {
    JsonObject * jo = new JsonObject();
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key2", v2);

    JsonIterator * it = jo->createIterator();

    it->first();
    EXPECT_FALSE(it->isDone());
    EXPECT_EQ("key1", it->currentKey());
    EXPECT_EQ("\"value1\"", it->currentValue()->toString());

    it->next();
    EXPECT_FALSE(it->isDone());
    EXPECT_EQ("key2", it->currentKey());
    EXPECT_EQ("\"value2\"", it->currentValue()->toString());

    it->next();
    EXPECT_TRUE(it->isDone());

    delete it;
    delete v1;
    delete v2;
    delete jo;
}

TEST(IteratorSuite, Composite) {
    JsonObject * jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key2", v2);

    JsonObject * j_composite = new JsonObject;
    j_composite->set("keyc", jo);

    JsonIterator * it = j_composite->createIterator();

    it->first();
    EXPECT_FALSE(it->isDone());
    EXPECT_EQ("keyc", it->currentKey());
    EXPECT_EQ("{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}", it->currentValue()->toString());

    it->next();
    EXPECT_TRUE(it->isDone());

    delete it;
    delete v1;
    delete v2;
    delete jo;
    delete j_composite;
}