CC	= g++-4.9
CFLAGS	= -Wall -g -std=c++14 -O
LDFLAGS	=
EXE = traveler
OBJ = tsp.o osrm.o
INC = 

all: $(EXE)

clean:
	rm -f *~ *.o core $(EXE)
	rm -rf *.dSYM

$(EXE): % : %.o $(OBJ)
	$(CC) $(CFLAGS) $@.o -o build/$@ $(OBJ) $(LDFLAGS)

%.o: %.cc $(INC)
	$(CC) $(CFLAGS) -c $<