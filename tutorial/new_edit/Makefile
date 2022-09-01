# build edit

CC := gcc
RM := rm -f
CFLAGS = `pkg-config --cflags gtk4`
LDFLAGS = `pkg-config --libs gtk4`

TARGET = tfe
OBJS = tfeapplication.o tfenotebook.o tfetextview.o

all : ${TARGET}

${TARGET} : ${OBJS}
	$(CC) $^ -o $@ ${LDFLAGS}

tfeapplication.o : tfeapplication.c
	$(CC) -c $^ -o $@ ${CFLAGS}

tfenotebook.o : tfenotebook.c
	$(CC) -c $^ -o $@ ${CFLAGS}

tfetextview.o : ./tfetextview/tfetextview.c
	$(CC) -c $^ -o $@ ${CFLAGS}

.PHONY : clean

ckean:
	$(RM) ${TARGET} ${OBJS}