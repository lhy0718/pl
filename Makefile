CC		= gcc
# if linux, LIBS = -lfl # if macOS, LIBS = -ll
LIBS	= -ll
LEX		= flex
YACC	= bison
TARGET	= project

all: $(TARGET)

project.tab.c project.tab.h:	project.y 
	$(YACC) project.y -dv

lex.yy.c:	project.lex project.tab.h
	$(LEX) project.lex

$(TARGET):	lex.yy.c project.tab.c project.tab.h symtab.c symtab.h functions.c functions.h
	$(CC) -o $(TARGET) lex.yy.c project.tab.c symtab.c functions.c $(LIBS)

clean:
	rm project *.tab.* lex.yy.c *.output
