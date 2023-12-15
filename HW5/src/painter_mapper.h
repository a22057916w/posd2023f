#pragma once

#include <string>
#include <sqlite3.h>

#include "abstract_mapper.h"

class DomainObject;
class Painter; 

class PainterMapper: public AbstractMapper {
public:
    static PainterMapper* instance();

    Painter * find(std::string id);
    
    void add(DomainObject * Painter);
    void update(std::string id);
    void del(std::string id);

protected:
    PainterMapper();

    static int callback(void* notUsed, int argc, char** argv, char** colNames);

    std::string updateStmt(DomainObject * domainObject) const;
    std::string findByIdStmt(std::string id) const;
    std::string addStmt(DomainObject * domainObject) const;
    std::string deleteByIdStmt(std::string id) const;
    
private:
    char* _errorMessage;
    static PainterMapper* _instance;
};