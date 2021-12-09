CC = gcc
FLAGS = -std=c99 -pedantic -g
FLAGS+= -Wall -Wno-unused-parameter -Wno-implicit-fallthrough -Wextra -Werror=vla -Werror
LINK = -lm
VALGRIND = --show-leak-kinds=all --track-origins=yes --leak-check=full
CMD = ./$(NAME)

BIND = bin
OBJD = obj
SRCD = src
SUBD = sub
TESTD = tests

INCL = -I$(SRCD)
INCL+= -I$(SUBD)/testoasterror/src

TESTS = $(TESTD)/main.c
TESTS+= $(SUBD)/testoasterror/src/testoasterror.c

SRCS = $(SRCD)/math32.c

SRCS_OBJS := $(patsubst %.c,$(OBJD)/%.o,$(SRCS))
TESTS_OBJS:= $(patsubst %.c,$(OBJD)/%.o,$(TESTS))

# aliases
.PHONY: tests
tests: $(BIND)/tests

# generic compiling command
$(OBJD)/%.o: %.c
	@echo "building object $@"
	@mkdir -p $(@D)
	@$(CC) $(INCL) $(FLAGS) -c -o $@ $<

# tests executable
$(BIND)/tests: $(SRCS_OBJS) $(TESTS_OBJS)
	@echo "compiling tests"
	@mkdir -p $(@D)
	@$(CC) -o $@ $^ $(LINK)

run:
	@cd $(BIND) && ./tests

leak: leakgrind
leakgrind: $(BIND)/tests
	@rm -f valgrind.log
	@cd $(BIND) && valgrind $(VALGRIND) 2> ../valgrind.log $(CMD)
	@less valgrind.log

clean:
	@echo "cleaning"
	@rm -rf $(BIND) $(OBJD) valgrind.log
