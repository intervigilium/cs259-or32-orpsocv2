# Makefile

CC=or32-elf-gcc
CFLAGS=-Wall -mnewlib -mboard=atlys
SOURCES=core_list_join.c core_matrix.c core_portme.c core_state.c core_util.c
LIBS=
OBJECTS=${SOURCES:.c=.o}
EXECUTABLE=coremark

all: ${SOURCES} ${EXECUTABLE}

${EXECUTABLE}: ${OBJECTS}
	${CC} ${CFLAGS} ${LIBS} core_main.c ${OBJECTS} -o $@

.c.o:
	${CC} ${CFLAGS} ${LIBS} -c $< -o $@


clean:
	rm *.o ${EXECUTABLE}
