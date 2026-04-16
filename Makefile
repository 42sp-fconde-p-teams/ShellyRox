# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by csilva-s          #+#    #+#              #
#    Updated: 2026/04/16 01:38:53 by csilva-s         ###   ########.fr        #
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
			  parsing/parser.c \
			  parsing/expander/expander.c \
			  parsing/expander/remove_quotes.c \
			  parsing/expander/variable_expansion.c \
			  parsing/expander/tilde_expansion.c \
			  parsing/expander/token_insertion.c \
			  parsing/fsm/get_token_len.c \
			  parsing/fsm/clear_token_list.c \
			  parsing/fsm/set_tokens.c \
			  execution/executor.c \
			  execution/execute_builtin.c \
			  execution/redirections.c \
			  execution/heredoc.c	\
			  execution/pipes.c \
			  builtins/cd.c \
			  builtins/echo.c \
			  builtins/env.c \
			  builtins/exit.c \
			  builtins/export.c \
			  builtins/pwd.c \
			  builtins/unset.c \
			  utils/errors.c \
			  utils/get_env_value.c \
			  utils/env_set.c \
			  utils/env_init.c \
			  utils/env_array.c \
			  utils/signals.c \
			  utils/cleanup.c \
			  free/free-parser.c \
			  free/free-env.c


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

sanitize: CFLAGS += -fsanitize=address
sanitize: re
	@echo "$(GREEN)✓ Shelly compiled with AddressSanitizer!$(RESET)"

tester: CFLAGS += -DTESTER
tester: re
	@echo "$(GREEN)✓ Shelly compiled for tester mode!$(RESET)"

re: fclean all

.PHONY: all clean fclean re sanitize tester
