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
E3_CPP=${SRCDIR}/cgtshared.cpp ${SRCDIR}/secint.cpp
E3NOABORT=1

# compiler, flags, incs, and libs
CC=g++
FLAGS=-O2 -std=c++17
BLOOM_CPP=${BLOOM}/filter.cpp
COMMON_CPP=${COMMON}/io.cpp ${COMMON}/text.cpp
INCS=-I${BLOOM} -I${COMMON} -I${SRCDIR} -I${E3ROOT}/3p/seal_unx/include
LIBS=${BLOOM_CPP} ${COMMON_CPP} ${E3_CPP} -L${E3ROOT}/3p/seal_unx/lib -lseal -pthread
DEFINES=-DE3NOABORT=${E3NOABORT}

M=16384
LOGM=16
H=6
INSDEL=insdel
QUERY=query
SETUP=setup
SORT=sort
DATABASE=${DATA}/database.db
CONFIG=bloomfilter.cfg.tmp
RESULTS=result.tmp
INSERTIONS=${DATA}/insert.db
DELETIONS=${DATA}/remove.db

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

compile: ${INSDEL} ${QUERY} ${SETUP} ${SORT}

decrypt:
	${SRCDIR}/cgt.exe dec -c ${CGT_FILE} -f ${FILE}

do_insert: run_insert
do_query: run_query send_query
do_remove: run_remove
do_setup: run_setup send_setup
do_sort: run_sort

run_insert:
	./${INSDEL}.exe insert ${INSERTIONS}

run_query:
	./${QUERY}.exe

run_remove:
	./${INSDEL}.exe remove ${DELETIONS}

run_setup:
	./${SETUP}.exe ${DATABASE} ${M} ${H}

run_sort:
	./${SORT}.exe

send_query:
	cp ${RESULTS} ${CLIENT}

send_setup:
	cp ${CONFIG} ${CLIENT}
