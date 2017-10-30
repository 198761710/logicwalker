#ARCH:=arm-linux-
ARCH:=/usr/bin/
CC:=$(ARCH)g++
STRIP:=$(ARCH)strip
LEX:=flex
YACC:=bison
LEXIN:= logicwalker.l
YACCIN:= logicwalker.y
LEXOUT:= lexer.cpp
YACCOUT:= parser.cpp
LFLAGS:= -o $(LEXOUT) --header-file=lexer.h
YFLAGS:= -o $(YACCOUT) --defines=parser.h
CFLAGS:=  -g

all: parser 
	$(STRIP) $+
	@ls -lhcv $+

test:
	@echo "-----------------input logic script--------------------"
	@cat example.logic
	@echo "-----------------output as prifix----------------------"
	@./parser < example.logic
	@echo "-------------------------------------------------------"

lexer:$(LEXIN)
	@echo $(CC) $+ -o $@
	@$(CC) -o $@ -DTEST_LEXER $(CFLAGS) $(LEXOUT)

parser: *.cpp *.h
	@echo $(CC) $+ -o $@
	@$(CC) -o $@ -DTEST_PARSER $(CFLAGS) $+

lexer.cpp:$(LEXIN)
	@echo $(LEX) $+ -o $@
	@$(LEX) $(LFLAGS) $+

parser.cpp:$(YACCIN)
	@echo $(LEX) $+ -o $@
	@$(YACC) $(YFLAGS) $+

clean:
	@rm -v logicwalker lexer parser *.o -rf
