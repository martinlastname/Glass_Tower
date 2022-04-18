main.o: 
	cc main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o Glass_Tower

Glass_Tower: main.o

run: Glass_Tower
	./Glass_Tower
