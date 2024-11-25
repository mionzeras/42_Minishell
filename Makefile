# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/14 18:12:41 by gcampos-          #+#    #+#              #
#    Updated: 2024/11/25 20:02:23 by fgomes-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Setup
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I includes -I libft #-fsanitize=address
LIBFT_PATH = libft
LIBFT = -Llibft -lft
SRC =	src/builtin/cd00.c \
		src/builtin/cd01.c \
		src/builtin/echo.c \
		src/builtin/env.c \
		src/builtin/exit.c \
		src/builtin/export00.c \
		src/builtin/export01.c \
		src/builtin/export02.c \
		src/builtin/pwd.c \
		src/builtin/unset.c \
		src/clean/clean.c \
		src/error/error.c \
		src/initialize/init.c \
		src/loop/mini_loop.c \
		src/parser/new_split.c \
		src/parser/parseline.c \
		src/parser/parsing.c \
		src/parser/quotes.c \
		src/utils/utils.c \
		src/utils/utils2.c \
		src/main.c

# Regras
OBJ = $(SRC:.c=.o)
MAKE = make -sC
RM = rm -f

# Colors
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
RESET = \033[0m

# Regra genérica para compilar .c em .o
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Regra principal para compilar o programa final
all: $(NAME)

# Compilação do executável a partir dos objetos
$(NAME): $(OBJ)
	@echo "$(CYAN)Compiling libft...$(RESET)"
	@$(MAKE) $(LIBFT_PATH)
	@echo "$(MAGENTA)libft compiled!$(RESET)"
	@echo "$(CYAN)Compiling $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
	@echo "$(MAGENTA)$(NAME) compiled!$(RESET)"

# Limpeza dos arquivos .o e do executável
clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@$(MAKE) $(LIBFT_PATH) clean
	@$(RM) $(OBJ)

fclean: clean
	@echo "$(YELLOW)Cleaning executable...$(RESET)"
	@$(MAKE) $(LIBFT_PATH) fclean
	@$(RM) $(NAME)

re: fclean all

leak: all
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --suppressions=supp.supp ./$(NAME)

# Declaração de dependências adicionais
.PHONY: all clean fclean re
