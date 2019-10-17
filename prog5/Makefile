CC       = gcc
FLAGS 	 = 
OBJ_FILE = server.o
EXE_FILE = logger

${EXE_FILE}: ${OBJ_FILE}
	${CC} ${FLAGS}  -o ${EXE_FILE}  ${OBJ_FILE} ${TMLIB_NV} -lpthread

server.o: server.c
	${CC} ${DFLAGS} ${IFLAGS} ${CFLAGS} -c server.c

clean:
	rm -f ${OBJ_FILE} ${EXE_FILE}
