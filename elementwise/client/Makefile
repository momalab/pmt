# directories
FULLDIR=$(abspath ..)
PMTDIR=$(abspath ${FULLDIR}/..)
E3ROOT=${PMTDIR}/e3
# E3ROOT=/workspace/e3work#remove
SRCDIR=${E3ROOT}/src
BLOOM=${PMTDIR}/bloom
COMMON=${PMTDIR}/common
DATA=${PMTDIR}/data
CLIENT=${FULLDIR}/client
SERVER=${FULLDIR}/server

# e3 config
SEAL=0
CGT_FILE=${FULLDIR}/cgt.tmp
E3_CPP=${SRCDIR}/cgtshared.cpp ${SRCDIR}/secint.cpp ${SRCDIR}/cgtkey.cpp
PUBLIC_KEY=SealBridge.eval.key*
E3NOABORT=1

# compiler, flags, incs, and libs
CC=g++
FLAGS=-O2 -std=c++17
BLOOM_CPP=${BLOOM}/filter.cpp
COMMON_CPP=${COMMON}/io.cpp ${COMMON}/text.cpp
INCS=-I${BLOOM} -I${COMMON} -I${SRCDIR} -I${E3ROOT}/3p/seal_unx/include
LIBS=${BLOOM_CPP} ${COMMON_CPP} ${E3_CPP} -L${E3ROOT}/3p/seal_unx/lib -lseal -pthread
DEFINES=-DE3KEY=1 -DE3NOABORT=${E3NOABORT}

LOGM=16
QUERY=query
QUERIES=${DATA}/queries.db
RESULT=result
SETUP=setup
RANDOM=random.tmp
ERANDOM=erandom.tmp
RESULTS=results.tmp
QUERY_HASHES=query.tmp

# g++ -I./ -I[user program directory] cgtshared.cpp secint.cpp cgtkey.cpp [user program directory]/*.cpp -DE3KEY=1 -o alice.exe

all: compile

%: %.cpp
	${CC} ${INCS} ${FLAGS} -o $@.exe $< ${LIBS} ${DEFINES}

cgt:
	rm -f *.key
	cp -f ${COMMON}/sz.hpp ${COMMON}/sz.tmp && \
	echo "${LOGM};" >> ${COMMON}/sz.tmp
	cd ${SRCDIR} && \
	$(MAKE) c && \
	$(MAKE) cgt.exe SEAL=${SEAL} && \
	./cgt.exe gen -c ${CGT_FILE} -d ${CLIENT} && \
	bash amalgam.sh && bash amalkey.sh && \
	cp *.key ${CLIENT} && \
	if [ -f SecureMod.const ] ; then cp *.const ${CLIENT}; fi

clean:
	rm -f *.o *.exe *.tmp

compile: ${SETUP} ${QUERY} ${RESULT}

decrypt:
	${SRCDIR}/cgt.exe dec -c ${CGT_FILE} -f ${FILE}

do_query: run_query send_query
do_result : run_result
do_setup: run_setup send_setup

run_query:
	./${QUERY}.exe ${QUERIES}

run_result:
	./${RESULT}.exe ${QUERIES}

run_setup:
	./${SETUP}.exe

send_query:
	cp ${QUERY_HASHES} ${SERVER}

send_setup:
	cp ${ERANDOM} ${SERVER}
	cp ${PUBLIC_KEY} ${SERVER} && \
	if [ -f SecureMod.const ] ; then cp *.const ${SERVER}; fi
