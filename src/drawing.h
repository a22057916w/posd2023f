#pragma once

#include <string>
#include <list>
#include "domain_object.h"
#include "shape.h"
#include "painter.h"

class Drawing : public DomainObject
{
public:
  Drawing(std::string id, Painter *painter) : DomainObject(id), _painter(painter) {}

  Drawing(std::string id, Painter *painter, std::list<Shape *> shapes) : DomainObject(id), _painter(painter), _shapes(shapes) {}

  Painter * painter() const {
    return _painter;
  }

  void setPainter(Painter *painter) {
    _painter = painter;
    UnitOfWork::instance()->registerDirty(this);
  }

  Shape * getShape(int i) const {
    if (i < 0 || i > (int)_shapes.size() - 1)
      return nullptr;

    auto it = _shapes.begin();
    for (int j = 0; j < i; j++)
      it++;

    return *it;
  }

  std::string getShapesAsString() const {
    std::string result = "";
    for (auto shape : _shapes)
    {
      result += shape->toString() + "\n";
    }
    return result;
  }

private:
  Painter *_painter;
  std::list<Shape *> _shapes;
};