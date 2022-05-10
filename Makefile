RESULT = lib/
BIN = bin/
TARGET = parser
SRC = src/
TEST = test/

all: clean bin $(TARGET)

$(TARGET):  $(BIN)Mark.o $(BIN)Direct.o $(BIN)Edge.o $(BIN)Vertex.o $(BIN)LGraph.o  $(BIN)Scanner.o  $(BIN)Dependencies.o $(BIN)Parser.o 
	g++ -std=c++11 $(BIN)Mark.o $(BIN)Direct.o $(BIN)Edge.o $(BIN)Vertex.o $(BIN)LGraph.o $(BIN)Scanner.o $(BIN)Dependencies.o $(BIN)Parser.o main.cpp -o  $(TARGET)

$(BIN)Mark.o:
	g++ -fPIC -c -std=c++11 -o $(BIN)Mark.o $(SRC)Mark.cpp
$(BIN)Direct.o:
	g++ -fPIC -c -std=c++11 -o $(BIN)Direct.o $(SRC)Direct.cpp
$(BIN)Edge.o:
	g++ -fPIC -c -std=c++11 -o $(BIN)Edge.o $(SRC)Edge.cpp
$(BIN)Vertex.o:
	g++ -fPIC -c -std=c++11 -o $(BIN)Vertex.o $(SRC)Vertex.cpp
$(BIN)LGraph.o:
	g++ -fPIC -c -std=c++11 -o $(BIN)LGraph.o $(SRC)LGraph.cpp
$(BIN)Dependencies.o: 
	g++ -fPIC -c -std=c++11 -o $(BIN)Dependencies.o $(SRC)Dependencies.cpp
$(BIN)Scanner.o:
	g++ -fPIC -c -std=c++11 -o $(BIN)Scanner.o $(SRC)Scanner.cpp
$(BIN)Parser.o: 
	g++ -fPIC -c -std=c++11 -o $(BIN)Parser.o $(SRC)Parser.cpp

bin:
	mkdir bin

clean:
	rm -rf bin
	rm -f $(TARGET)