PREFIX?=/usr/local
CC	= g++-4.9
CFLAGS	= -Wall -g -std=c++14 -I{PREFIX}/include/
LDFLAGS	= -L${PREFIX}/lib -lOSRM -L/usr/lib -lboost_date_time -lboost_filesystem -lboost_iostreams -lboost_program_options -lboost_regex -lboost_system -lboost_thread -lboost_unit_test_framework -lpthread
EXE = traveler
OBJ = tsp.o osrmquery.o
INC = 

all: $(EXE)

clean:
	rm -f *~ *.o core $(EXE)
	rm -rf *.dSYM

$(EXE): % : %.o $(OBJ)
	$(CC) $(CFLAGS) $@.o -o build/$@ $(OBJ) $(LDFLAGS)

%.o: %.cc $(INC)
	$(CC) $(CFLAGS) -c $<