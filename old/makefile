# Makefile For OpenGL Assignment 2
# CG200 Assignment
# Last Modified: 18/09/16
# Connor Beardsmore - 15504319

# MAKE VARIABLES
LATEX=*.aux,*.log,*.out,*.bbl,*.blg,*.bcf,*.toc,*.lot,*.lof,*.synctex.gz*,*.run.xml
EXEC=sample
OBJ=sample.o
FRAMEWORK=-framework OpenGL -framework GLUT
DEPRECATED=-Wno-deprecated-declarations

# RULES + DEPENDENCIES
$(EXEC) : $(OBJ)
	gcc $(OBJ) -o $(EXEC) $(FRAMEWORK)

sample.o : sample.c sample.h
	gcc -c sample.c $(DEPRECATED)

clean :
	rm -f -R $(EXEC) $(OBJ) *.gch
	rm -f -R documentation/{$(LATEX)}
