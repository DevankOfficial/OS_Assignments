objects = One_a One_b Async_One_a Async_One_b
all: $(objects)

$(objects): %: %.c
	$(CC) $(CFLAGS) -o $@ $< -pthread 

clean:
	rm -f One_a One_b Async_One_a Async_One_b