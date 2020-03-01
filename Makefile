handler_test:
	g++ handler_test.cpp -c
	g++ handler_test.o -o handler_test -lsfml-window -lsfml-graphics -lsfml-system

chess:
	g++ main.cpp -c
	g++ main.o -o chess -lsfml-window -lsfml-graphics -lsfml-system

clean:
	rm -rf *.o handler_test chess