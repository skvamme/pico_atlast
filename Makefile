
#	Unix makefile for ATLAST

VERSION = 1.2

COPTIONS = -g -Wall
CC = gcc

LIBRARIES = -lm

INCLUDE =

ATLCONFIG = -DMEMSTAT -DALIGNMENT -DEXPORT -DREADONLYSTRINGS

CFLAGS = $(COPTIONS) $(INCLUDE) $(ATLCONFIG)

ATLOBJ = atlast.o

APPS = atlast 

all:	$(APPS)

atlast: $(ATLOBJ)
	$(CC) $(CFLAGS) $(ATLOBJ) -o atlast $(LIBRARIES)

atlast.o:   atlast.c atldef.h
atldef.h:   atlast.h

clean:
	rm -f $(APPS)
	rm -f *.bak *.o *.dvi *.aux *.log
	rm -f core core.* cscope.out *.tar.gz
	rm -rf dist
	( cd tex ; make clean )
	
