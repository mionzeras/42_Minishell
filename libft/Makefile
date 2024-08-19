# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 14:48:56 by gcampos-          #+#    #+#              #
#    Updated: 2024/08/17 16:59:03 by gcampos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

LIBFT1 = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
		ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
		ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c 

LIBFT2 = ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_itoa.c ft_strmapi.c \
		ft_striteri.c
	
LIBFT_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

FT_PRINTF = ft_printf.c ft_pf_functions.c ft_pf_hex.c ft_pf_pointer.c ft_unsigned.c

FT_GNL = get_next_line.c get_next_line_utils.c

SRC = ${LIBFT1} ${LIBFT2} ${LIBFT_BONUS} ${FT_PRINTF} ${FT_GNL}

OBJS = ${SRC:.c=.o}

CC = cc

# remove the files named in the variable RM from the directory and subdirectories if any. -f: ignore nonexistent files and arguments.
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

# create the library with the flags rcs
#(r: insert the files member into archive (with replacement)
#c: creates the archive
#s: sort archives, if you put that, you don't need ranlib)
AR = ar rcs

# %.o is the target and %.c is the prerequisite
# $@ is the target and $^ is the prerequisite, -c is to create the object files and -o is to name the object files
%.o:%.c
		@${CC} ${CFLAGS} -c -o $@ $^

# create the library with the flags rcs.
${NAME}: ${OBJS}
		@${AR} ${NAME} ${OBJS}

all:	${NAME}

# remove the object files from the directory and subdirectories if any.
clean:
		@${RM} ${OBJS}

# remove the object files and the library from the directory and subdirectories if any.
fclean: clean
		@${RM} ${NAME}

#recompile all files if any changes are made to the source files or header files in the project directory or any subdirectory.
re: fclean all

# make sure we can compile correctly, even when we have files with those names.
.PHONY: all clean fclean re