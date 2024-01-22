#---------------------- Makefile for philosophers -------------------------# 
################################ Colors ####################################  

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m

################################# Project ###################################

NAME = philo
HEADER = ./include

################################# Sources ###################################

MAND_SRCS = main.c \
		check_args.c \
		init.c \
		time.c \
		minilib.c \
		threads.c \
		actions.c 

SRC = $(addprefix ./src/, $(MAND_SRCS))

################################# Objects ###################################

OBJS = $(MAND_SRCS:.c=.o)
OBJS_DIR = ./objs

################################# Flags #####################################

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -pthread -I$(HEADER)

################################# Rules #####################################

all: $(NAME)

$(NAME): $(OBJS:%=$(OBJS_DIR)/%)
	@$(CC) $(CFLAGS) $(OBJS:%=$(OBJS_DIR)/%) -o $(NAME)
	@echo "$(GREEN)$(NAME) created$(RESET)"

$(OBJS_DIR)/%.o: src/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)$(NAME) objects deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)$(NAME) deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re
