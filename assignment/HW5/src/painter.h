#pragma once

#include "domain_object.h"
#include "unit_of_work.h"

class Painter : public DomainObject {
public:
    Painter(std::string id, std::string name) : DomainObject(id), _name(name) {}

    std::string name() const {
        return _name;
    }

    void setName(std::string name) {
        _name = name;
        UnitOfWork::instance()->registerDirty(this);
    }

private:
    std::string _name;
};