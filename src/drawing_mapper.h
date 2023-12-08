#pragma once

#include <string>
#include <list>
#include <sqlite3.h>

#include "abstract_mapper.h"

class DomainObject;
class Drawing;
class Scanner;
class Parser;
class Builder;
class Painter;
class Shape;

class DrawingMapper : public AbstractMapper
{
public:
    Drawing * find(std::string id);

    // add
    void add(DomainObject * drawing);
    // update
    void update(std::string id);
    // delete
    void del(std::string id);


    static DrawingMapper * instance();

protected:
    DrawingMapper();

    static int callback(void *notUsed, int argc, char **argv, char **colNames);

    std::list<Shape *> convertShapes(int argc, char **argv);

    std::string updateStmt(DomainObject *domainObject) const;
    std::string findByIdStmt(std::string id) const;
    std::string addStmt(DomainObject *domainObject) const;
    std::string deleteByIdStmt(std::string id) const;

private:
    char *_errorMessage;
    static DrawingMapper *_instance;
    Builder *_builder;
    Scanner *_scanner;
    Parser *_parser;

    Painter * _painter;
};