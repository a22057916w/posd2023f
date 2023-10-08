
all: bin/ut_all

file.o: src/file.h src/file.cpp
	g++ -std=c++11 -c src/file.cpp -o obj/file.o

folder.o: src/folder.h src/folder.cpp
	g++ -std=c++11 -c src/folder.cpp -o obj/folder.o

iterator.o: src/iterator.h src/iterator.cpp src/dfs_iterator.h
	g++ -std=c++11 -c src/iterator.cpp -o obj/iterator.o

bin/ut_all: test/ut_all.cpp test/ut_file.h test/ut_folder.h test/ut_iterator.h iterator.o file.o folder.o
	g++ -std=c++11 test/ut_all.cpp obj/iterator.o obj/file.o obj/folder.o -o bin/ut_all -lgtest -lpthread 

