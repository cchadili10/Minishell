# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 23:22:21 by yessemna          #+#    #+#              #
#    Updated: 2024/08/06 17:35:50 by hchadili         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror 
RDFLAGS = -lreadline

READLINEDIR = $(shell brew --prefix readline)

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
		tools/get_next_line.c \
		tools/ft_atoi.c \
		tools/ft_itoa.c \
		parsing/errors.c \
		parsing/tokenazing.c \
		parsing/finders.c \
		parsing/heredoc_expand.c \
		parsing/heredoc.c \
		parsing/process_line.c \
		parsing/process_line_.c \
		init/init_env.c \
		Execution/call_builtins.c \
		Execution/execution.c \
		Execution/execution_func.c \
		Execution/execution_multi.c \
		Execution/execution_one.c \
		Execution/sort_export.c \
		Execution/ft_first_cmnd.c \
		Execution/ft_middel_cmnd.c \
		Execution/ft_last_cmnd.c \
		builtins/env.c \
		builtins/ft_cd.c \
		builtins/ft_cd_env.c \
		builtins/ft_cd_export.c \
		builtins/echo.c \
		builtins/ft_pwd.c \
		builtins/export.c \
		builtins/export_extand.c \
		builtins/export_extand_a.c \
		builtins/export_node.c \
		builtins/unset.c \
		builtins/unset_env.c \
		builtins/unset_export.c \
		builtins/exit.c \
		signals/signals.c \
		exit/exit.c \
		printf/ft_putnbr.c \
		printf/ft_putchar.c \
		printf/ft_putstr.c \
		printf/ft_printf.c \
		printf/ft_hexa.c 
	
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) -L$(READLINEDIR)/lib -lreadline

all: $(NAME)

%.o : %.c minishell.h
	@$(CC) $(CFLAGS) -c -I$(READLINEDIR)/include  $< -o $@
	
clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
re: fclean all
# -I$(READLINEDIR)/include 
# -L$(READLINEDIR)/lib