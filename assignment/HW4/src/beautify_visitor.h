#pragma once

#include "visitor.h"
#include "json_object.h"
#include "string_value.h"
#include "json_iterator.h"

#include <string>

using std::string;

class BeautifyVisitor : public JsonVisitor {
public:
    void visitJsonObject(JsonObject * obj) override {
        indent += 4;
        string space = string(indent, ' ');

        JsonIterator * it = obj->createIterator();
        int cnt = 0;
        for(it->first(); !it->isDone(); it->next()) {
            if(cnt > 0)
                _result += ",\n";
            
            // handling key part
            _result += space + "\"" + it->currentKey() + "\": ";
            if(dynamic_cast<JsonObject *>(it->currentValue()))
                _result += "{\n";

            // handling value part
            it->currentValue()->accept(this);

            if(dynamic_cast<JsonObject *>(it->currentValue()))
                _result += "\n" + space + "}";

            cnt++;
        }

        indent -= 4;
    }

    void visitStringValue(StringValue * val) override {
        _result += val->toString();
    }

    std::string getResult() const {
        return "{\n" + _result + "\n}"; 
    }

private:
    int indent = 0;
    string _result = "";
};