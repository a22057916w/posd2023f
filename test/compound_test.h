#include "../src/compound.h"
#include <vector>

TEST(CompoundSuite, CompoundOfTwoTriangles) {
    std::vector<Shape *> shapes = {new Triangle(1,1,1), new Triangle(2,2,2)};
    Shape * compound = new Compound(shapes);
    ASSERT_DOUBLE_EQ(9.0, compound->perimeter());
}