EXECS=reduce
MPICC=mpicc

all: ${EXECS}

reduce: reduce.c
	${MPICC} -o reduce reduce.c

clean:
	rm -f ${EXECS}

deps:
	@pip install -r requirements.txt

python: deps
