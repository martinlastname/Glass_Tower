FLAGS		= -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRCS		= main.c ECS.c

TARGET		= Glass_Tower

DEL			:= $(shell command -v trash 2> /dev/null)

$(TARGET): all

all:
	cc $(SRCS) $(FLAGS) -o $(TARGET)

clean:
ifndef DEL
	rm *.o $(TARGET)
else
	trash *.o $(TARGET)
endif

run: $(TARGET)
	./Glass_Tower
