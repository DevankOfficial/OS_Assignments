one: one.o
	cc one.o -pthread -o one 

one.o: one.c
	cc -c one.c -o one.o

one.c:
	echo "int main() { return 0; }" > one.c

clean:
	rm -f one