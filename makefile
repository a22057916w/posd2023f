u_test: test/ut.cpp test/triangle_test.h src/triangle.h src/shape.h #u_test is the target, test/ut.cpp is the depended file
	g++ -std=c++11 test/ut.cpp -o bin/ut -lgtest -lpthread