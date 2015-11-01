EXECS=broadcast
MPICC=mpicc

all: ${EXECS}

broadcast: broadcast.c
	${MPICC} -o broadcast broadcast.c

clean:
	rm -f ${EXECS}
