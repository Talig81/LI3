CC      = gcc
CFLAGS  = -Wall -std=c11 `pkg-config --cflags libxml-2.0 glib-2.0` -D_GNU_SOURCE -g
LIBS 	= `pkg-config --libs libxml-2.0 glib-2.0`
DATASETS = datasets/snapshot_dec16 datasets/snapshot_jan17 datasets/snapshot_fev17
EXE = final.exe

all: $(EXE)

$(EXE): avl.o linklist.o heap.o parser.o interface.o program.o
	$(CC) $(CFLAGS) avl.o linklist.o heap.o parser.o interface.o program.o -o final.exe $(LIBS)

test: avl.o linklist.o heap.o parser.o interface.o program.o
	$(CC) $(CFLAGS) avl.o linklist.o heap.o parser.o interface.o program.o -o final.exe $(LIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $(LIBS) $< -o $@

run: $(EXE)
	./$(EXE) $(DATASETS)

clean:
	rm -f *.o $(EXE)
