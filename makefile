.PHONY: clean dirs

UT_ALL = test/ut_all.cpp
TEST_HEADERS = test/json_test.h test/ut_visitor.h test/ut_iterator.h test/ut_scanner.h test/ut_parser.h

SRC_HEADERS = src/json_object.h src/value.h src/string_value.h src/json_iterator.h src/visitor.h src/beautify_visitor.h src/json_parser.h src/json_scanner.h src/json_builder.h

all: dirs bin/ut_all

bin/ut_all: $(UT_ALL) $(TEST_HEADERS) $(SRC_HEADERS)
	g++ -std=c++11 -Wfatal-errors -Wall -o bin/ut_all $(UT_ALL) -lgtest -lpthread

clean:
	rm -rf bin obj

dirs:
	mkdir -p bin obj
