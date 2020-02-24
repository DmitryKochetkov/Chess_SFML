clean:
	rm -rf *.o test chess

chess:
	g++ main.cpp -c
	g++ main.o -o chess -lsfml-window -lsfml-graphics -lsfml-system