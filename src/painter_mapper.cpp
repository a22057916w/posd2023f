#include "painter_mapper.h"
#include "painter.h"
#include "abstract_mapper.h"

#include <string>
#include <iostream>
#include <sqlite3.h>
#include <map>

using std::string;

PainterMapper * PainterMapper::_instance = nullptr;

PainterMapper::PainterMapper() {}

PainterMapper * PainterMapper::instance() {
    if (_instance == nullptr)
        _instance = new PainterMapper();
    return _instance;
}

Painter * PainterMapper::find(string id) {
    return static_cast<Painter *>(abstractFind(id, PainterMapper::callback));
}

void PainterMapper::add(DomainObject * painter) {
    abstractAdd(painter);
}

void PainterMapper::update(string id) {
    Painter * painter = find(id);
    abstractUpdate(painter);
}

void PainterMapper::del(string id) {
    abstractDelete(id);
}

// *********************************** statements ********************************************
 
string PainterMapper::findByIdStmt(string id) const {
    string stmt = "SELECT * FROM painter WHERE ID = '" + id + "'";
    return stmt;
}

string PainterMapper::addStmt(DomainObject * domainObject) const {
    Painter * painter = static_cast<Painter *>(domainObject);
    string id = painter->id();
    string name = painter->name();

    string stmt = "INSERT INTO painter"
                "(ID, name)"
                "values"
                "('"+ id + "', '" + name + "')";
    return stmt;
}

string PainterMapper::updateStmt(DomainObject * domainObject) const {
    Painter * painter = static_cast<Painter *>(domainObject);
    string id = painter->id();
    string name = painter->name();

    string stmt = "UPDATE painter SET name='" + name + "' WHERE ID='" + id + "'";
    return stmt;
}

string PainterMapper::deleteByIdStmt(string id) const {
    string stmt = "DELETE FROM painter WHERE ID='" + id + "'";
    return stmt;
}

int PainterMapper::callback(void* notUsed, int argc, char** argv, char** colNames) {
    Painter * painter = new Painter(argv[0], argv[1]);
    PainterMapper::instance()->load(painter);
    return 0;
}
