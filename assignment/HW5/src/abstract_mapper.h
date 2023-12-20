#pragma once

#include "domain_object.h"
#include "unit_of_work.h"

#include <unordered_map>
#include <iostream>

typedef int (*CallbackType)(void *, int argc, char **argv, char **col_names);

class AbstractMapper
{
public:
    virtual ~AbstractMapper() {
        cleanCache();
    }

    virtual std::string updateStmt(DomainObject *domainObject) const = 0;
    virtual std::string findByIdStmt(std::string id) const = 0;
    virtual std::string addStmt(DomainObject * domainObject) const = 0;
    virtual std::string deleteByIdStmt(std::string id) const = 0;

    void setDB(std::string db_file) {
        sqlite3_open(db_file.c_str(), &_db);
    }

    bool isLoaded(const std::string &id) const {
        return _domainObjects.count(id);
    }

    void cleanCache() {
        for(auto it = _domainObjects.begin(); it != _domainObjects.end(); it++)
            delete (*it).second;
        _domainObjects.clear();
    }

protected:
    std::unordered_map<std::string, DomainObject *> _domainObjects; // maintain as cache
    sqlite3 *_db;

    DomainObject * getDomainObject(std::string id) {
        if (_domainObjects.count(id))
            return _domainObjects.at(id);
        else
            return nullptr;
    }

    DomainObject * abstractFind(std::string id, CallbackType callback) {
        DomainObject * domainObject = getDomainObject(id);
        // if object is in cache, return the object
        if(domainObject != nullptr)
            return domainObject;

        // if not found in cache, fetch from database
        sqlite3_exec(_db, findByIdStmt(id).c_str(), callback, NULL, &_errorMessage);
        domainObject = getDomainObject(id);
        if(domainObject != nullptr)
            UnitOfWork::instance()->registerClean(domainObject);
        return domainObject; // may be nullptr
        
    }

    void abstractAdd(DomainObject * domainObject) {
        sqlite3_exec(_db, addStmt(domainObject).c_str(), NULL, NULL, &_errorMessage);
    }

    void abstractUpdate(DomainObject * domainObject) {
        sqlite3_exec(_db, updateStmt(domainObject).c_str(), NULL, NULL, &_errorMessage);
    }

    void abstractDelete(std::string id) {
        DomainObject * domainObject = getDomainObject(id);

        sqlite3_exec(_db, deleteByIdStmt(id).c_str(), NULL, NULL, &_errorMessage);

        // if object is in cache, clean the object
        if(domainObject != nullptr) {
            _domainObjects.erase(id);
            delete domainObject;
        }   
    }

    void load(DomainObject * domainObject) {
        _domainObjects[domainObject->id()] = domainObject;    
    }

private:
    char * _errorMessage;
};