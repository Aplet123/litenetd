IDIR = ./include
CC = gcc
CFLAGS = -I$(IDIR) -Wall -Werror

ODIR = ./obj
SDIR = ./src

LIBFILES = server util

DEPS = $(patsubst %,$(IDIR)/%.h,$(LIBFILES))

_OBJ = main.o $(patsubst %,%.o,$(LIBFILES))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

litenetd: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o 
