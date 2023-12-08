#pragma once

#include <string>

class DomainObject {
public:
    DomainObject(std::string id): _id(id) {}

    std::string id() const {
        return _id;
    }

    virtual ~DomainObject() {}
    
protected:
    std::string _id;
};