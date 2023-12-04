#pragma once

#include "json_object.h"
#include "string_value.h"

#include <stack>
#include <string>
#include <utility>

class JsonBuilder {
public:
    // builds a StringValue and add it to the currently building JsonObject
    void buildValue(std::string key, std::string value) {
        StringValue * sv = new StringValue(value);

        // there is always at least one JsonObject in stack
        JsonObject * jo = _composite.top().first;
        jo->set(key, sv);
    }

    // starts to build a JsonObject with a key.
    void buildObject(std::string key) {
        _composite.push(make_pair(new JsonObject(), key));
    }

    // ends the currently building JsonObject and adds it to its parent JsonObject
    void endObject() {
        // always a root JsonObject inside _composite
        if(_composite.size() > 1) {
            JsonObject * jo = _composite.top().first;
            string key = _composite.top().second;
            _composite.pop();
        
            JsonObject * parent = _composite.top().first;
            parent->set(key, jo);
        }
    }

    JsonObject * getJsonObject() { 
        return _composite.top().first;
    }

private:
    std::stack<std::pair<JsonObject *, std::string>> _composite;
};
