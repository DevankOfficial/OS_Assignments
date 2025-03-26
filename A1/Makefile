TARGET=a.out
SOURCE=one_1.c
DEPEND=one_1.o

all: $(TARGET)

a.out: $(DEPEND)
	gcc $(DEPEND) -o $(TARGET)

$(DEPEND):
	gcc -c $(SOURCE)

clean:
	rm -rf $(TARGET) *.O
