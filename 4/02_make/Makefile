SRC :=	main.c elefant.c giraffe.c zoo.c

OBJ := ${SRC:%.c=%.o}

DEPDIR := .deps

DEPS := $(wildcard $(OBJS:%=%.d))

CC = gcc

CFLGS = -Wall -Werror -Wextra

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

HEADER = elefant.h giraffe.h zoo.h

NAME = main

COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) -c

TEST = test.sh

$(DEPDIR):
		@mkdir -p $(DEPDIR)

%.o : %.c $(DEPDIR)/$(DEPS) | $(DEPDIR)
		$(COMPILE.c) $<

all : main
	
main: $(DEPDIR) $(OBJ) 
	@echo "compiling ..."
	$(CC) $(OBJ) -o $(NAME)

clean:
	@echo "cleaning all objects"
	@rm -fr $(OBJ)
	@rm -f $(NAME)

fclean: clean
	@echo "cleaning every thing ..."
	@rm -fr $(DEPDIR)

re: fclean all

test: $(TEST)
	@echo "testing ..."
	@bash $(TEST)

.PHONY: all clean fclean bonus so re test

-include $(DEPDIR)/*.d