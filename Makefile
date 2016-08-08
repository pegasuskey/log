CFLAGS=-g -Wall -I./incl/
LFLAGS=-L ./lib/

FZSOCI=./fzsoci
OCIINS=./fzsins

OBJS=fzs_oci.o
I_OBJS=oci_insert.o

all:${FZSOCI} ${OCIINS}

${FZSOCI}:${OBJS}
	${CC} ${LFLAGS} ${OBJS} -lclntsh -o $@
	chmod 755 $@

${OCIINS}:${I_OBJS}
	${CC} ${LFLAGS} ${I_OBJS} -lclntsh -o $@
	chmod 755 $@
clean:
	rm -rf *.o fzsoci fzsins
