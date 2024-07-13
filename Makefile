# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 23:22:21 by yessemna          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2024/07/13 05:53:14 by yessemna         ###   ########.fr        #
=======
#    Updated: 2024/07/12 22:44:51 by hchadili         ###   ########.fr        #
>>>>>>> b9c3b618bd4c986bbf0f8704eb270262af73f9cf
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc -g #-fsanitize=address 
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
		tools/dbl_join.c \
		tools/ft_strdup.c \
		tools/ft_strlen.c \
		tools/ft_strcmp.c \
		tools/ft_strchr.c \
		tools/ft_substr.c \
		tools/ft_strcpy.c \
		tools/lst_tools.c \
		tools/ft_lstsize.c \
		tools/error.c \
		tools/ft_malloc.c \
		tools/count_word.c \
		tools/ft_putendl_fd.c \
		tools/ft_lstclear.c \
		parsing/errors.c \
		parsing/tokenazing.c \
		parsing/finders.c \
<<<<<<< HEAD
		parsing/heredoc_expand.c \
=======
		Execution/execution.c \
>>>>>>> b9c3b618bd4c986bbf0f8704eb270262af73f9cf
		

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
