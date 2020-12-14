E3ROOT=/workspace/e3work

CC=g++
FLAGS=-O2 -std=c++17
INCS=-I${E3ROOT}/3p/seal_unx/include
LIBS=-L${E3ROOT}/3p/seal_unx/lib -lseal -pthread

LOGN=13

all: compile run

%: %.cpp
	${CC} ${FLAGS} ${INCS} -o $@.exe $< ${LIBS}

clean:
	rm -f *.data *.exe

compile: modswitch

run:
	./modswitch.exe ${LOGN}
