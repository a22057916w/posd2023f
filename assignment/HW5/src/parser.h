#pragma once

#include <list>
#include <stack>
#include "./scanner.h"
#include "./builder.h"

class Parser {
public:
    Parser(Scanner *scanner, Builder * builder) : _scanner(scanner), _builder(builder) {
    }

    void parse() {
        while(!_scanner->isDone()) {
            std::string shape_token = _scanner->nextToken();
            if(shape_token == "triangle") {
                double a = _scanner->nextDouble();
                double b = _scanner->nextDouble();
                double c = _scanner->nextDouble();
                _builder->buildTriangle(a, b, c);
            }
            else if(shape_token == "compound") {
                if(_scanner->nextToken() == "{") {
                    _builder->buildCompound();
                }
            }
            else if (shape_token == "}") {
                _builder->endCompound();
            }
        }
    }
    
    std::list<Shape *> getShapes() {
        return _builder->getShapes();
    }

    void setInput(std::string input) {
        _shapeString = input;
        _scanner->setInput(input);
    }
    
    void clear() {
        _builder->clear();
        _shapeString = "";
    }

private:
    Scanner * _scanner;
    Builder * _builder;
    std::string _shapeString;
};