#pragma once

class JsonObject;
class StringValue;

class JsonVisitor {
public:
    virtual ~JsonVisitor() {};
    virtual void visitJsonObject(JsonObject * obj) = 0;
    virtual void visitStringValue(StringValue * val) = 0;
};