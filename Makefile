SRCS := $(shell find src -name "*.c")
OBJS := $(SRCS:.c=.o)
HDRS := $(shell find . -name "*.h")

TEST_SRCS := $(shell find test -name "*.c") $(shell find src -name "*.c" | grep -v "main.c")
TEST_OBJS := $(TEST_SRCS:.c=.o)

db: $(OBJS)
	gcc -o $@ $^

testdb: $(TEST_OBJS)
	gcc -g -o $@ $^

%.o: %.c $(HDRS)
	gcc -c -o $@ $<

.PHONY: clean

clean:
	rm -f db testdb $(OBJS) $(TEST_OBJS) *.db

.PHONY: test

test: testdb
	./testdb

.PHONY: run

run: db
	./db
