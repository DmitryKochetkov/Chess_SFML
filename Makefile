clean:
	rm -rf *.o handler_test chess

chess:
	g++ main.cpp -c
	g++ main.o -o chess -lsfml-window -lsfml-graphics -lsfml-system

handler_test:
	g++ handler_test.cpp -c
	g++ handler_test.o -o handler_test -lsfml-window -lsfml-graphics -lsfml-system