objects = Fifo_P1 Fifo_P2 Shared_P1 Shared_P2 Unix_P1 Unix_P2
all: $(objects)

$(objects): %: %.c
	$(CC) $(CFLAGS) -o $@ $< -pthread -lm -lrt -lpthread

clean:
	rm -f Unix_P1 Unix_P2 Fifo_P1 Fifo_P2 Shared_P1 Shared_P2