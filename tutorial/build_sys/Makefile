CC := gcc
RM := rm -f
CFLAGS = `pkg-config --cflags gtk4`
LDFLAGS = `pkg-config --libs gtk4`

TARGET = tfe
OBJS = tfe.o tfetextview.o

all: ${TARGET}

${TARGET}: ${OBJS}
	$(CC) $^ -o $@ ${LDFLAGS}

tfe.o: tfe.c
	$(CC) -c $^ -o $@ ${CFLAGS}

tfetextview.o: tfetextview.c
	$(CC) -c $^ -o $@ ${CFLAGS}

.PHONY: clean

clean:
	$(RM) ${TARGET} ${OBJS} 