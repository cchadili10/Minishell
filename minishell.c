/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:59:59 by yessemna          #+#    #+#             */
/*   Updated: 2024/09/12 17:42:55 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print list as a table

void print_list(t_token *list)
{
	t_token *tmp = list;
	while (tmp)
	{
		printf(" (%s)  ->  ", tmp->key);
		if (tmp->value == PIPE)
			printf("PIPE\n");
		else if (tmp->value == SPC)
			printf("SPC\n");
		else if (tmp->value == IN)
			printf("IN\n");
		else if (tmp->value == HEREDOC)
			printf("HEREDOC\n");
		else if (tmp->value == OUT)
			printf("OUT\n");
		else if (tmp->value == APPEND)
			printf("APPEND\n");
		else if (tmp->value == SNGL_Q)
			printf("Sgl_q\n");
		else if (tmp->value == DBL_Q)
			printf("Dbl_q\n");
		else if (tmp->value == VAR)
			printf("VAR\n");	
		else if (tmp->value == CMD)
			printf("CMD\n");
		else if (tmp->value == DBL_VAR)
			printf("DBL_VAR\n");
		tmp = tmp->next;
	}
}




void print_cmd(t_cmd **cmd)
{
	t_cmd *tmp = *cmd;
	int i = 0;
	printf("\n-----------\n");
	while (tmp)
	{
		i = 0;
		while (tmp->cmds && tmp->cmds[i])
		{
			printf("cmd[%d] : %s\n", i, tmp->cmds[i]);
			i++;
		}
		printf("redir_in: %d\n", tmp->redir_in);
		printf("redir_out: %d\n", tmp->redir_out);
		tmp = tmp->next;
	}
	printf("\n-----------\n");
}

bool	ft_parse(char *line, t_token **list, t_env **envi, t_cmd **cmd)
{
	if (!processline(line, list))
		return (true);
	else if (!catch_errors(list))
		return (true);
	find_node(*envi, *list);
	join_nodes(list);
	if ((*list)->value == PIPE
		&& ((*list)->next->value != PIPE || (*list)->next != NULL))
	{
		ft_printf("Minishell: syntax error near unexpected token `|'\n");
		ft_exit_status(258, SET);
		return (true);
	}
	if (!prepare_cmd(*list, cmd, *envi))
		return (true);
	print_list(*list);
	// print_cmd(cmd);
	return (false);
}

bool	ft_execute(t_token **list, t_cmd **cmd, t_env **envi)
{
	(void)list;
	if (ft_exit_herdog(1, GET))
		return (ft_exit_herdog(0, SET), true);
	ft_execution(cmd, envi);
	return (false);
}

void	free_garb_exite(void)
{
	printf("exit\n");
	g_malloc_env(0, FREE);
	exit(ft_exit_status(0, GET));
}

void	ft_loop_main(t_env **envi)
{
	t_token			*list;
	char			*line;
	t_cmd			*cmd;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	while (1)
	{
		(ft_signal(1), (1) && (line = NULL, list = NULL, cmd = NULL));
		line = readline("minishell$ ");
		if (!line)
			free_garb_exite();
		if (line && ft_strlen(line) != 0)
			add_history(line);
		if (ft_parse(line, &list, envi, &cmd)
			|| ft_execute(&list, &cmd, envi))
		{
			free((void *)line);
			continue ;
		}
		(free(line), unlink("/tmp/dog"));
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		g_malloc(0, FREE);
	}
	g_malloc_env(0, FREE);
}

int	main(int ac, char **av, char **env)
{
	t_env	*envi;

	(void)av;
	rl_catch_signals = 0;
	envi = NULL;
	if (ac > 1)
		print_error("no argument needed");
	initenv(env, &envi);
	ft_loop_main(&envi);
}
