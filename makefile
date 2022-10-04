CC=g++
IDIR=./include
SRCDIR=./src
_SRC=messaging.cpp blum.cpp
ODIR=./obj
_OBJ=messaging.o blum.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))
_DEPS=messaging.h blum.h server.h client.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

CFLAGS=-I $(IDIR)
LIBS=-lntl -lgmp

$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


server:  $(OBJ) $(ODIR)/server.o
	$(CC) -o server $^ $(CFLAGS) $(LIBS)

client:  $(OBJ) $(ODIR)/client.o
	$(CC) -o client $^ $(CFLAGS) $(LIBS)
