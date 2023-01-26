OBJECTS = ../src/bookshelf.cpp
ifndef GUI
OBJECTS += ./clientinterface.o
CLIOBJECTCOMP = g++ $(DEFINEFLAGS) $(FLAGS) -c ../src/clientinterface.cpp -o clientinterface.o
endif
ifndef NOACCOUNTS
OBJECTS += ./accountservice.o
FLAGS += -lssl -lcrypto
ACCOUNTOBJCOMP = g++ $(DEFINEFLAGS) $(FLAGS) -c ../src/accountservice.cpp -o accountservice.o
else
DEFINEFLAGS = -DNOACCOUNTS
endif
ifdef VERBOSE
FLAGS += -v
endif

all: compileobj compile clean run
norun: compileobj compile clean
unclean: compileobj compile run

compileobj:
	$(CLIOBJECTCOMP) 
	$(ACCOUNTOBJCOMP)
compile:
	g++ $(DEFINEFLAGS) $(FLAGS) $(OBJECTS) -o booklibrary.x86_64 -std=c++17 -pthread
run:
	./booklibrary.x86_64
clean:
	rm -f *.o