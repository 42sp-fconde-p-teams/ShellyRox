# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csilva-s <csilva-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by csilva-s          #+#    #+#              #
#    Updated: 2026/02/18 12:13:17 by csilva-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I./includes -I./lib/libft
LIBS		= -L./lib/libft -lft -lreadline

# Directories
SRC_DIR		= src
OBJ_DIR		= obj
LIBFT_DIR	= lib/libft

# Source files
SRC_FILES	= main.c \
			  parsing/lexer.c \
			  parsing/parser.c \
			  parsing/expander.c \
			  execution/executor.c \
			  execution/redirections.c \
			  execution/pipes.c \
			  builtins/cd.c \
			  builtins/echo.c \
			  builtins/env.c \
			  builtins/exit.c \
			  builtins/export.c \
			  builtins/pwd.c \
			  builtins/unset.c \
			  utils/errors.c \
			  utils/environment.c \
			  utils/signals.c \
			  utils/cleanup.c

SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Colors
GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0m

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GREEN)Compiled: $<$(RESET)"

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✓ Shelly compiled successfully!$(RESET)"

unit-tests:
	@$(MAKE) -C ./tests

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C ./tests
	@echo "$(RED)Object files removed$(RESET)"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@rm -rf ./test/test_report.log
	@$(MAKE) fclean -C ./tests
	@echo "$(RED)Executable removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re
