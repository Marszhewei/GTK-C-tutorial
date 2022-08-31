CC := gcc
RM := rm -f
CFLAGS += `pkg-config --cflags gtk+-4.0` -Wall
LDFLAGS += `pkg-config --libs gtk+-4.0` -lm -Wall
OBJS = tfe.o tfetextview.o

all: tfe

tfe: ${OBJS}
	$(CC) -o tfe ${OBJS} ${LDFLAGS}

# tfe.o: tfetextview.h
# 	$(CC) -c tfe.c ${CFLAGS}

tfe.o: tfetextview.h
	$(CC) -c tfetextview.c ${CFLAGS}

# .Phony: clean

clean:
    $(RM) $(OBJS) 