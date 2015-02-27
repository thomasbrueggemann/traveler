PREFIX?=/usr/local
CC	= g++-4.9
CFLAGS	= -Wall -g -std=c++11 -I{PREFIX}/include/
LDFLAGS	= -L${PREFIX}/lib -pthread -lboost_thread -lboost_system -lOSRM
EXE = traveler
OBJ = tsp.o osrmquery.o
INC = 

all: $(EXE)

clean:
	rm -f *~ *.o core $(EXE)
	rm -rf *.dSYM

$(EXE): % : %.o $(OBJ)
	$(CC) -o build/$@ $@.o $(OBJ) $(LDFLAGS)

%.o: %.cc $(INC)
	$(CC) $(CFLAGS) -c $<