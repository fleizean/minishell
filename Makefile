NAME = minishell
CC = gcc
RM = rm -rf
SOURCE = $(shell find src -name "*.c") $(wildcard libft/*.c)
OBJECTS = $(SOURCE:.c=.o)

UNAME := $(shell uname -s)
ifeq ($(UNAME), Darwin)
READLINE_INC = -I /goinfre/homebrew/opt/readline/include
READLINE_LIB = -L /goinfre/homebrew/opt/readline/lib -lreadline
else
READLINE_INC =
READLINE_LIB = -lreadline
endif

FLAGS = -Wall -Werror -Wextra -g $(READLINE_INC)

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)
all: $(NAME)
$(NAME): $(OBJECTS) minishell.h
	$(CC) $(FLAGS) $(OBJECTS) $(READLINE_LIB) -o $(NAME)
clean:
	$(RM) $(OBJECTS)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re
