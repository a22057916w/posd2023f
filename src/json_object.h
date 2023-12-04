#pragma once

#include "value.h"
#include "json_iterator.h"
#include "visitor.h"

#include <string>
#include <map>

using std::string;

class JsonObject : public Value {
public:
    ~JsonObject() {
        for(auto & item : _map)
            delete item.second;
        _map.clear();
    }

    string toString() override {
        _result += "{";

        int cnt = 0;
        for(auto item : _map) {
            if(cnt > 0)
                _result += ",";

            _result += "\n\"";
            _result += item.first;
            _result += "\":";
            _result += item.second->toString();
            cnt++;
        }
        _result += "\n}";

        return _result;
    }

    void set(string key, Value * value) {
        _map[key] = value;
    }

    Value * getValue(string key) { 
        if(_map.find(key) == _map.end())
            throw string("Key not found.");
        return _map[key]; 
    }

    void accept(JsonVisitor * visitor) override {
        visitor->visitJsonObject(this);
    }

    JsonIterator * createIterator() override {
        return new JsonObjectIterator(this);
    }

    class JsonObjectIterator : public JsonIterator {
    public:
        JsonObjectIterator(JsonObject * composite): _host(composite) {}

        void first() override {
            _it = _host->_map.begin();
        }

        string currentKey() const override {
            return (*_it).first;
        }

        Value * currentValue() const override {
            return (*_it).second;
        }

        void next() override {
            _it++;
        }

        bool isDone() const override {
            return _it == _host->_map.end();
        }

    private:
        JsonObject * _host;
        std::map<string, Value *>::iterator _it;
    };

    private:
        std::map<string, Value *> _map;
        string _result = "";
};