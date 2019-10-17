CC       = gcc
FLAGS 	 = 
OBJ_FILE = s-tee.o
EXE_FILE = s-tee

${EXE_FILE}: ${OBJ_FILE}
	${CC} ${FLAGS}  -o ${EXE_FILE}  ${OBJ_FILE} -lpthread

s-tee.o: s-tee.c
	${CC} ${DFLAGS} ${IFLAGS} ${CFLAGS} -c s-tee.c

all: ${OBJ_FILE}
	${CC} ${FLAGS}  -o ${EXE_FILE}  ${OBJ_FILE} -lpthread

clean:
	rm -f ${OBJ_FILE} ${EXE_FILE}
