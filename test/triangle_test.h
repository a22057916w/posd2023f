#include "../src/triangle.h"
#include "../src/shape.h"
#include <array>
#include <algorithm>

TEST(TriangleSuite, Ping) {
    ASSERT_TRUE(true);
}

TEST(TriangleSuite, Perimeter_T345_Is_12) {
    Triangle t(3.0, 4.0, 5.0); // stack allocated
    ASSERT_DOUBLE_EQ(12.0, t.perimeter());
}

TEST(TriangleSuite, TriangleAsShape) {
    Shape * t = 
        new Triangle(3.0, 4.0, 5.0); // heap allocated - returning a pointer 
    ASSERT_DOUBLE_EQ(12.0, t->perimeter());
}

bool lessThanByPerimeter(Shape * a, Shape * b) {
    return a->perimeter() < b->perimeter();
}

TEST(TriangleSuite, SortTriangles) {
    std::array<Shape *, 3> shapes = {new Triangle(2,2,2), new Triangle(1,1,1), new Triangle(3,4,5)};
    std::sort(shapes.begin(), shapes.end(), lessThanByPerimeter);
    ASSERT_DOUBLE_EQ(3.0, shapes[0]->perimeter());
    ASSERT_DOUBLE_EQ(6.0, shapes[1]->perimeter());
    ASSERT_DOUBLE_EQ(12.0, shapes[2]->perimeter());
}