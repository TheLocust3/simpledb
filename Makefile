SRCS := $(shell find src -name "*.c")
OBJS := $(SRCS:.c=.o)
HDRS := $(shell find src -name "*.h")

db: $(OBJS)
	gcc -o $@ $^

%.o: %.c $(HDRS)
	gcc -c -o $@ $<

clean:
	rm -f db $(OBJS)

run: db
	./db
