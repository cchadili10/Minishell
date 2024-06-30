# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 23:22:21 by yessemna          #+#    #+#              #
#    Updated: 2024/06/30 22:15:36 by yessemna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc #-g -fsanitize=address 
CFLAGS = -Wall -Wextra -Werror 
RDFLAGS = -lreadline
SRC = minishell.c \
		find_node.c \
		tools/ft_split.c \
		tools/ft_srtjoin.c \
		tools/ft_strjoin.c \
		tools/ft_bzero.c \
		tools/ft_calloc.c \
		tools/ft_memset.c \
		tools/ft_strlen.c \
		tools/ft_strchr.c \
		tools/ft_substr.c \
		tools/ft_strcpy.c \
		tools/lst_tools.c \
		tools/ft_lstsize.c \
		tools/error.c \
		tools/count_word.c \
		tools/ft_putendl_fd.c \
		tools/ft_lstclear.c \
		parsing/errors.c \
		parsing/tokenazing.c \
		parsing/finders.c \
		

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(RDFLAGS)

all: $(NAME)

%.o : %.c minishell.h
	@$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all