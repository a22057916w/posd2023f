#pragma once

#include <unordered_map>
#include <set>
#include <string>

class DomainObject;

class UnitOfWork {
public:
    static UnitOfWork * instance();

    void registerNew(DomainObject * domainObject);

    void registerClean(DomainObject * domainObject);

    void registerDirty(DomainObject * domainObject);

    void registerDeleted(DomainObject * domainObject);

    bool inNew(std::string id) const;
;
    bool inClean(std::string id) const;

    bool inDirty(std::string id) const;

    bool inDeleted(std::string id) const;

    void commit();

protected:
    UnitOfWork();
private:
    std::unordered_map<std::string, DomainObject *> _new;
    std::unordered_map<std::string, DomainObject *> _dirty;
    std::unordered_map<std::string, DomainObject *> _clean;
    std::unordered_map<std::string, DomainObject *> _deleted;
    static UnitOfWork * _instance;
};