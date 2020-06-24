# Exemple générique de Makefile
# Par : Prasanth et Andy
# Date : 30/05/2020

SHELL = /bin/sh
#définition des commandes utilisees
CC = gcc
ECHO = echo
RM = rm -rf
TAR = tar
MKDIR = mkdir
CHMOD = chmod
CP = rsync -R
#déclaration des options pour gcc
CFLAGS = 
CPPFLAGS = -I.
LDFLAGS = -L/usr/lib -lm
#définition des fichiers et dossiers
PROGNAME = tetris
PACKAGE=$(PROGNAME)
VERSION = 1.0.0
distdir = $(PACKAGE)-$(VERSION)
HEADERS = cercle.h triangle.h losange.h file.h screen.h main.h
SOURCES = cercle.c triangle.c losange.c screen.c main.c
OBJS = $(SOURCES:.c=.o)
DISTFILES = $(SOURCES) Makefile $(HEADERS)

all: $(PROGNAME)

$(PROGNAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(PROGNAME)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

dist: distdir
	$(CHMOD) -R a+r $(distdir)
	$(TAR) zcvf $(distdir).tgz $(distdir)
	$(RM) $(distdir)
distdir: $(DISTFILES)
	$(RM) $(distdir)
	$(MKDIR) $(distdir)
	$(CHMOD) 777 $(distdir)
	$(CP) $(DISTFILES) $(distdir)/
clean:
	$(RM) $(PROGNAME) $(OBJS) *~ $(distdir).tgz
