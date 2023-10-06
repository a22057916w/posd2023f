
all: bin/ut_all

bin/ut_all: test/ut_all.cpp test/ut_file.h
		g++ -std=c++11 test/ut_all.cpp -o bin/ut_all -lgtest -lpthread 

