CC	= g++-4.9
CFLAGS	= -Wall -g -std=c++11 `pkg-config libosrm --cflags` -I/usr/include/nodejs/src -I/usr/local/lib/node_modules/nan 
LDFLAGS	= `pkg-config libosrm --libs --static` -lrt
EXE = traveler
OBJ = osrmquery.o tsp.o
INC = 

all: $(EXE)

clean:
	rm -f *~ *.o core $(EXE)
	rm -rf *.dSYM

$(EXE): % : %.o $(OBJ)
	$(CC) $(CFLAGS) $@.o -o build/$@ $(OBJ) $(LDFLAGS)

%.o: %.cc $(INC)
	$(CC) $(CFLAGS) -c $<