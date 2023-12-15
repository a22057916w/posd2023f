#include "../src/scanner.h"
#include "../src/parser.h"
#include "../src/builder.h"

TEST(ParserSuite, ScannerOnTriangle){
    Scanner * scanner = new Scanner();
    scanner->setInput("triangle 1.0 1.0 1.0");
    
    ASSERT_EQ("triangle", scanner->nextToken());
    ASSERT_EQ(1.0, scanner->nextDouble());
    ASSERT_EQ(1.0, scanner->nextDouble());
    ASSERT_EQ(1.0, scanner->nextDouble());
    ASSERT_TRUE(scanner->isDone());
}

TEST(ParserSuite, ParserOnTriangle){
    Scanner *scanner = new Scanner();
    Builder * builder = new Builder();
    Parser *parser = new Parser(scanner, builder);
    parser->setInput("triangle 1.0 1.0 1.0");
    parser->parse();
    std::list<Shape *> shapes = parser->getShapes();
    ASSERT_EQ(3.0, shapes.front()->perimeter());
}

TEST(ParserSuite, ParserOnCompoundOfTwoTriangles) {
    std::string input = "compound {\n  triangle 2.0 2.0 2.0\n  triangle 3.0 3.0 3.0\n}";
    Scanner *scanner = new Scanner();
    Builder * builder = new Builder();
    Parser *parser = new Parser(scanner, builder);
    parser->setInput(input);
    parser->parse();
    std::list<Shape *>shapes = parser->getShapes();
    ASSERT_EQ(15.0, shapes.front()->perimeter());
}

TEST(ParserSuite, ParserOnTestData) {
    std::string input = "compound {\n  triangle 1.0 1.0 1.0\n  compound {\n    triangle 2.0 2.0 2.0\n    triangle 3.0 3.0 3.0\n  }\n}\ntriangle 4.0 4.0 4.0";
    Scanner * scanner = new Scanner();
    Builder * builder = new Builder();
    Parser * parser = new Parser(scanner, builder);
    parser->setInput(input);
    parser->parse();
    std::list<Shape *> shapes = parser->getShapes();
    ASSERT_EQ(18.0, shapes.front()->perimeter());
    ASSERT_EQ(12.0, shapes.back()->perimeter());
}

TEST(ParserSuite, ParserWithBuilder) {
    std::string input = "compound {\n  triangle 1.0 1.0 1.0\n  compound {\n    triangle 2.0 2.0 2.0\n    triangle 3.0 3.0 3.0\n  }\n}\ntriangle 4.0 4.0 4.0";
    Scanner * scanner = new Scanner();
    Builder * builder = new Builder();
    Parser * parser = new Parser(scanner, builder);
    parser->setInput(input);
    parser->parse();
    std::list<Shape *> shapes = builder->getShapes();
    ASSERT_EQ(18.0, shapes.front()->perimeter());
    ASSERT_EQ(12.0, shapes.back()->perimeter());
}