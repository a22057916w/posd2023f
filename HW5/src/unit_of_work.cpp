#include "unit_of_work.h"
#include "drawing_mapper.h"
#include "painter_mapper.h"
#include "domain_object.h"
#include "painter.h"
#include "drawing.h"

#include <list>
#include <iostream>
#include <string>

using std::string;

// initiation
UnitOfWork * UnitOfWork::_instance = nullptr;

UnitOfWork::UnitOfWork() {}

UnitOfWork * UnitOfWork::instance() {
    if(_instance == nullptr)
        _instance = new UnitOfWork();
    return _instance;
}

void UnitOfWork::registerNew(DomainObject * domainObject) {
    _new[domainObject->id()] = domainObject;
}

void UnitOfWork::registerClean(DomainObject * domainObject) {
    _clean[domainObject->id()] = domainObject;
}
void UnitOfWork::registerDirty(DomainObject * domainObject) {
    _dirty[domainObject->id()] = domainObject;
    _clean.erase(domainObject->id());
}
void UnitOfWork::registerDeleted(DomainObject * domainObject) {
    if(inNew(domainObject->id())) {
        _new.erase(domainObject->id());
        return;
    }
    _deleted[domainObject->id()] = domainObject;
    _clean.erase(domainObject->id());
}

bool UnitOfWork::inNew(std::string id) const {
    return _new.count(id);
}
bool UnitOfWork::inClean(std::string id) const {
    return _clean.count(id);
}
bool UnitOfWork::inDirty(std::string id) const {
    return _dirty.count(id);
}
bool UnitOfWork::inDeleted(std::string id) const {
    return _deleted.count(id);
}

void UnitOfWork::commit() {
    for(auto item : _new) {
        if(dynamic_cast<Painter *>(item.second))
            PainterMapper::instance()->add(item.second);
        else
            DrawingMapper::instance()->add(item.second);
        UnitOfWork::instance()->registerClean(item.second);
    }

    for(auto item : _dirty) {
        if(dynamic_cast<Painter *>(item.second))
            PainterMapper::instance()->update(item.first);
        else
            DrawingMapper::instance()->update(item.first);
        UnitOfWork::instance()->registerClean(item.second);
    }

    for(auto item : _deleted) {
        if(dynamic_cast<Painter *>(item.second))
            PainterMapper::instance()->del(item.first);
        else
            DrawingMapper::instance()->del(item.first);
    }

    _new.clear();
    _dirty.clear();
    _deleted.clear();
}