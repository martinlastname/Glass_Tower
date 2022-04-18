build:
	cc main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o Glass_Tower

run:
	./Glass_Tower
