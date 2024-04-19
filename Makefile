# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 23:22:21 by yessemna          #+#    #+#              #
#    Updated: 2024/04/19 10:25:22 by yessemna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc #-g -fsanitize=address 
CFLAGS = -Wall -Wextra -Werror 
RDFLAGS =  -L $(shell brew --prefix readline)/lib -lreadline
SRC = minishell.c \
		tools/ft_split.c \
		tools/ft_bzero.c \
		tools/ft_calloc.c \
		tools/ft_memset.c \
		tools/ft_strlen.c \
		tools/ft_strchr.c \
		tools/ft_substr.c \
		tools/ft_strcpy.c \
		tools/lst_tools.c \
		

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(RDFLAGS)

all: $(NAME)

%.o : %.c minishell.h
	@$(CC) $(CFLAGS) -I $(shell brew --prefix readline)/include -c $< -o $@
	
clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all