CC = gcc
CFLAGS = -I.
DEPS = include/ui_handle.h include/file_handle.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ERS_APP: src/main.o src/ui_handle.o src/file_handle.o
	$(CC) -o ERS_APP src/main.o src/ui_handle.o src/file_handle.o $(CFLAGS)