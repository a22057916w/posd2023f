.PHONY: clean dirs

UT_ALL = test/ut_all.cpp
TEST_HEADERS = test/ut_iterator.h test/ut_file.h test/ut_folder.h test/ut_node.h 

SRC_HEADERS = src/file.h src/folder.h src/node.h src/iterator.h src/null_iterator.h src/dfs_iterator.h

ITERATOR_OBJ = obj/iterator.o
ITERATOR_SRC = src/iterator.cpp src/iterator.h

all: dirs bin/ut_all

bin/ut_all: $(UT_ALL) $(TEST_HEADERS) $(SRC_HEADERS) $(ITERATOR_OBJ)
	g++  -std=c++11 -Wfatal-errors -Wall -o bin/ut_all $(UT_ALL) $(ITERATOR_OBJ) -lgtest -lpthread

$(ITERATOR_OBJ): $(ITERATOR_SRC)
	g++  -std=c++11 -Wfatal-errors -Wall -c $< -o $@

clean:
	rm -rf bin obj

dirs:
	mkdir -p bin obj
