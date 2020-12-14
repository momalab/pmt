CLIENT=client
SERVER=server
DATA=../data
TOOLS=../tools
SEAL=0
QUERYSIZE=100
LOGDB=10
DBSIZE=$(shell echo "$$(( 1 << ${LOGDB} ))" )
PROB=0.001
H=6
N=14
P=65537
LOGP=$(shell python3 ${TOOLS}/log2.py ${P} floor )
M=$(shell python3 ${TOOLS}/m.py ${DBSIZE} ${PROB} ${H} ${N} ${P} )
LOGM=$(shell python3 ${TOOLS}/log2.py ${M} ceil )
# LOGM=14
# M=$(shell echo "$$(( 1 << ${LOGM} ))" )

all: print_params cgt compile run

cgt: cgt_python
	$(MAKE) cmd DIR=${CLIENT} CMD="cgt SEAL=${SEAL}" LOGM=${LOGM}

cgt_python:
	python3 ${TOOLS}/cgt.py ${N} ${P} ${LOGM}

clean: clean_client clean_server

clean_client:
	$(MAKE) cmd DIR=${CLIENT} CMD=clean

clean_server:
	$(MAKE) cmd DIR=${SERVER} CMD=clean

cmd:
	cd ${DIR} && $(MAKE) ${CMD}

compile: compile_client compile_server prepare_database

compile_client:
	$(MAKE) cmd DIR=${CLIENT} CMD=compile

compile_server:
	$(MAKE) cmd DIR=${SERVER} CMD=compile

insert:
	$(MAKE) cmd DIR=${SERVER} CMD=do_insert LOGP=${LOGP}

insert_remove:
	$(MAKE) insert LOGP=${LOGP} && \
	$(MAKE) query && \
	$(MAKE) remove LOGP=${LOGP} && \
	$(MAKE) query

prepare_database:
	cd ${DATA} && \
	python3 database.py ${DBSIZE} && \
	python3 query.py ${QUERYSIZE}

print_params:
	@echo "Using SEAL=${SEAL} QUERYSIZE=${QUERYSIZE} DBSIZE=${DBSIZE} LOGDB=${LOGDB} PROB=${PROB} H=${H} N=${N} P=${P} LOGP=${LOGP} M=${M} LOGM=${LOGM}"

query: query_client query_server result_client

query_client:
	$(MAKE) cmd DIR=${CLIENT} CMD=do_query

query_server:
	$(MAKE) cmd DIR=${SERVER} CMD=do_query

remove:
	$(MAKE) cmd DIR=${SERVER} CMD=do_remove LOGP=${LOGP}

result_client:
	$(MAKE) cmd DIR=${CLIENT} CMD=do_result LOGP=${LOGP}

run: setup query insert_remove

setup: setup_server setup_client sort_server

setup_client:
	$(MAKE) cmd DIR=${CLIENT} CMD=do_setup LOGP=${LOGP}

setup_server:
	$(MAKE) cmd DIR=${SERVER} CMD=do_setup M=${M} H=${H} LOGP=${LOGP}

sort_server:
	$(MAKE) cmd DIR=${SERVER} CMD=do_sort LOGP=${LOGP}
