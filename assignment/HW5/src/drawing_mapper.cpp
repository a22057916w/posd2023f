#include "drawing_mapper.h"
#include "drawing.h"
#include "parser.h"
#include "scanner.h"
#include "builder.h"
#include "painter_mapper.h"


#include <sqlite3.h>
#include <string>
#include <map>

using std::string;

DrawingMapper * DrawingMapper::_instance = nullptr;

Drawing * DrawingMapper::find(string id) {
    return static_cast<Drawing *>(abstractFind(id, DrawingMapper::callback));
}

void DrawingMapper::add(DomainObject * drawing) {
    abstractAdd(drawing);
}

void DrawingMapper::update(string id) {
    Drawing * drawing = find(id);
    abstractUpdate(drawing);
}

void DrawingMapper::del(string id) {
    abstractDelete(id);
}

// *********************************** statements ************************************

string DrawingMapper::findByIdStmt(string id) const {
    string stmt = "SELECT * FROM drawing WHERE ID = '" + id + "'";
    return stmt;
}

string DrawingMapper::addStmt(DomainObject * domainObject) const {
    Drawing * drawing = static_cast<Drawing *>(domainObject);
    string id = drawing->id();
    string painter = drawing->painter()->id();
    string shapes = drawing->getShapesAsString();

    string stmt = "INSERT INTO drawing"
                "(ID, painter, shapes)"
                "values"
                "('" + id + "', '" + painter + "', '" + shapes + "')";
    return stmt;
}

string DrawingMapper::updateStmt(DomainObject * domainObject) const {
    Drawing * drawing = static_cast<Drawing *>(domainObject);
    string id = drawing->id();
    string painter = drawing->painter()->id();
    string shapes = drawing->getShapesAsString();

    string stmt = "UPDATE drawing SET painter='" + painter + "' WHERE ID='" + id + "'";
    return stmt;
}

string DrawingMapper::deleteByIdStmt(string id) const {
    string stmt = "DELETE FROM drawing WHERE ID='" + id + "'";
    return stmt;
}

DrawingMapper * DrawingMapper::instance() {
    if(_instance == nullptr) 
        _instance = new DrawingMapper();
    return _instance;
}

DrawingMapper::DrawingMapper()
{
    _builder = new Builder();
    _scanner = new Scanner();
    _parser = new Parser(_scanner, _builder);
}


int DrawingMapper::callback(void* notUsed, int argc, char** argv, char** colNames) {
    Painter * painter = PainterMapper::instance()->find(argv[1]);
    std::list<Shape *> shapes = DrawingMapper::instance()->convertShapes(argc, argv);
    
    Drawing * drawing = new Drawing(argv[0], painter, shapes);
    DrawingMapper::instance()->load(drawing);
    return 0;
}



std::list<Shape *> DrawingMapper::convertShapes(int argc, char **argv) {
    _parser->clear();
    _parser->setInput(argv[2]);
    _parser->parse();
    return _parser->getShapes();
}
