CFLAGS = -Wall -ansi -pedantic-errors -I include
OBJS =				\
       $(BUILDDIR)/main.o	\
       $(BUILDDIR)/lexer.o	\
       $(BUILDDIR)/parser.o	\
       $(BUILDDIR)/list.o
BUILDDIR = build
BIN = $(BUILDDIR)/bin/lcalc

all : $(BUILDDIR) $(BIN)

$(BIN) : $(OBJS)
	gcc $(CFLAGS) -o $@ $^

$(BUILDDIR)/%.o : src/%.c
	gcc -c $(CFLAGS) -o $@ $^

$(BUILDDIR) :
	mkdir $(BUILDDIR)
	mkdir $(BUILDDIR)/bin

clear :
	rm -r $(BUILDDIR)
