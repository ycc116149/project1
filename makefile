project1: keypad.o func.o
	g++ -o project1 keypad.o  func.o -lncurses

keypad.o: keypad.cpp
	g++ -c keypad.cpp -lncurses

func.o: func.cpp
	g++ -c func.cpp

clean:
	rm project1*.o
