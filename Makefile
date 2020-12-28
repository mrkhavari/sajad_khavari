CXX = g++
CXXFLAGS = -std=c++2a -Wall -I h -I /usr/local/include/gtest/ -c -O3
LXXFLAGS = -std=c++2a -Ih -pthread
OBJECTS =  ./obj/node.o ./obj/main.o 
GTEST = /usr/local/lib/libgtest.a
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS) $(GTEST)
./obj/node.o: ./cpp/node.cpp 
	$(CXX) $(CXXFLAGS) ./cpp/node.cpp -o ./obj/node.o
./obj/main.o: ./cpp/main.cpp
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
clean:
	rm -fv $(TARGET) $(OBJECTS)
