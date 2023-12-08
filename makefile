.phony: clean stat

FLAGS = -std=c++11 -Wfatal-errors -Wall
OBJ = obj/shape_iterator.o obj/unit_of_work.o obj/drawing_mapper.o obj/painter_mapper.o
SRC = src/abstract_mapper.h src/parser.h src/builder.h src/scanner.h src/domain_object.h src/drawing.h src/painter.h src/iterator_factory.h src/shape_iterator_factory.h src/shape.h src/triangle.h src/visitor.h
TEST = test/ut.cpp test/db_test.h test/parser_test.h

all: dir u_test 

u_test: $(SRC) $(TEST) $(OBJ)
	g++ $(FLAGS) test/ut.cpp $(OBJ) -o bin/ut_all -lsqlite3 -lgtest -lpthread

obj/shape_iterator.o: src/shape_iterator.h src/shape_iterator.cpp
	g++ $(FLAGS) -c src/shape_iterator.cpp -o obj/shape_iterator.o

obj/unit_of_work.o: src/unit_of_work.h src/unit_of_work.cpp
	g++ $(FLAGS) -c src/unit_of_work.cpp -o obj/unit_of_work.o

obj/drawing_mapper.o: src/drawing_mapper.h src/drawing_mapper.cpp
	g++ $(FLAGS) -c src/drawing_mapper.cpp -o obj/drawing_mapper.o

obj/painter_mapper.o: src/painter_mapper.h src/painter_mapper.cpp
	g++ $(FLAGS) -c src/painter_mapper.cpp -o obj/painter_mapper.o

dir:
	mkdir -p bin
	mkdir -p obj
	mkdir -p resource

clean:
	rm -f bin/* obj/*.o resource/*.db

stat:
	wc -l src/* test/*.h test/*.cpp