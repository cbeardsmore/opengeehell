# Makefile for OpenGL Assignment 2
# CG200 Assignment
# Last Modified: 07/10/16
# Connor Beardsmore - 15504319

# MAKE VARIABLES
LATEX=*.aux,*.log,*.out,*.bbl,*.blg,*.bcf,*.toc,*.lot,*.lof,*.synctex.gz*,*.run.xml
CC = g++
CFLAGS = -Wall
EXEC = opengeehell
DEPRECATED=-Wno-deprecated-declarations
SRC1 = main.cpp imageloader.cpp floor.cpp axis.cpp chain.cpp rocks.cpp
SRC2 = teapot.cpp flag.cpp bubbles.cpp anchor.cpp

# SET LIBS BASED ON OS
ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut
endif

all : $(EXEC)

$(EXEC) : $(SRC1) $(SRC2)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC1) $(SRC2) $(LIBS) $(DEPRECATED)

run:
	./$(EXEC)

clean :
	rm -f $(EXEC) $(LATEX) *.gch
	rm -f -R documentation/{$(LATEX)}
