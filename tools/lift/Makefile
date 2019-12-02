all: remill-lift

SRC=Lift.cpp
OBJ=$(SRC:.cpp=.o)

LDFLAGS= -lgflags -lglog -lLLVM -lxed -lstdc++ -L../../remill -lremill -lremill_x86

%.o: %.cpp
	clang -c -I../../ -o $@ $<

remill-lift: ${OBJ}
	clang -o $@ $^ ${LDFLAGS}

.PHONY: all clean

clean:
	$(RM) -v ${OBJ} remill-lift
