FLAGS		= -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRCS		= main.c Config.c ECS.c Game.c Hash_Table.c Hazard.c Player.c

TARGET		= Glass_Tower
TEST_TARGET	= TEST_Glass_Tower

$(TARGET): all

all:
	cc $(SRCS) $(FLAGS) -o $(TARGET)

debug:
	cc -g $(SRCS) $(FLAGS) -o $(TEST_TARGET)

# Uses trash-cli instead of rm if available.
DEL			:= $(shell command -v trash 2> /dev/null)
clean:
ifndef DEL
	rm $(TARGET) $(TEST_TARGET)
else
	trash $(TARGET) $(TEST_TARGET)
endif

todo:
	grep TODO -n *.c

run: $(TARGET)
	./Glass_Tower
