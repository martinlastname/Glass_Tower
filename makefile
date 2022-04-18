FLAGS		= -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRCS		= main.c ECS.c

TARGET		= Glass_Tower

$(TARGET): all

all:
	cc $(SRCS) $(FLAGS) -o $(TARGET)

# Uses trash-cli instead of rm if available.
DEL			:= $(shell command -v trash 2> /dev/null)
clean:
ifndef DEL
	rm *.o $(TARGET)
else
	trash *.o $(TARGET)
endif

run: $(TARGET)
	./Glass_Tower
