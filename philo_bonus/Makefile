#---------------------- Makefile for philosophers -------------------------# 
################################ Colors ####################################  

MAGENT 			= \033[0;35m
RED 			= \033[1;31m
GREEN 			= \033[1;32m
YELLOW 			= \033[0;33m
BLUE 			= \033[1;34m
RESET 			= \033[0m

################################# Project ###################################

NAME 			= philo_bonus
HEADER 			= ./include

################################# Sources ###################################

MAND_SRCS 		= main.c \
				check_args.c \
				init.c \
				time.c \
				minilib.c \
				semaphores.c \
				actions.c \
				actions_utils.c \
				# monitor.c \

SRC 			= $(addprefix ./src/, $(MAND_SRCS))

################################# Objects ###################################

OBJS 			= $(MAND_SRCS:.c=.o)
OBJS_DIR 		= ./objs

################################# Flags #####################################

CC 				= gcc
CFLAGS 			= -Wall -Wextra -Werror -g -pthread -I$(HEADER)

################################# Progress ###################################

TOTAL_FILES 	= $(words $(MAND_SRCS))
CURRENT_FILES 	= 0

define update_progress
	$(eval CURRENT_FILES=$(shell echo $$(($(CURRENT_FILES) + 1))))
	@echo -n "\r$(MAGENT)Progress: $(CURRENT_FILES)/$(TOTAL_FILES) [$$((($(CURRENT_FILES)*100)/$(TOTAL_FILES)))%]$(RESET)"
endef

################################# Rules #####################################

all: $(NAME)

$(NAME): $(OBJS:%=$(OBJS_DIR)/%)
	@$(CC) $(CFLAGS) $(OBJS:%=$(OBJS_DIR)/%) -o $(NAME)
	@echo ""
	@echo "$(GREEN)$(NAME) created$(RESET)"

$(OBJS_DIR)/%.o: src/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ 
	$(call update_progress)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)$(NAME) objects deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)$(NAME) deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re
