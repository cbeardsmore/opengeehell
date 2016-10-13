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
SRC = main.cpp imageloader.cpp floor.cpp axis.cpp anchor.cpp rocks.cpp

# SET LIBS BASED ON OS
ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut
endif

all : $(EXEC)

$(EXEC) : $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC) $(LIBS) $(DEPRECATED)

run:
	./$(EXEC)

clean :
	rm -f $(EXEC) $(LATEX) *.gch
	rm -f -R documentation/{$(LATEX)}
