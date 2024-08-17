/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:59:59 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/17 21:58:08 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_nodes(t_token **list)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = *list;
	while (tmp)
	{
		if (tmp->value == CMD && tmp->next && tmp->next->value == CMD)
			((1) && (tmp->key = ft_srtjoin(tmp->key, tmp->next->key),
					tmp->next = tmp->next->next));
		if (tmp->next && (tmp->value == DBL_Q || tmp->value == SNGL_Q
				|| tmp->value == VAR || tmp->value == DBL_VAR
				|| tmp->value == CMD) && (tmp->next->value == DBL_Q
				|| tmp->next->value == SNGL_Q
				|| tmp->next->value == VAR || tmp->next->value == DBL_VAR
				|| tmp->next->value == CMD))
		{
			tmp2 = tmp->next->next;
			tmp->key = ft_srtjoin(tmp->key, tmp->next->key);
			if (tmp->next->value == DBL_Q || tmp->next->value == SNGL_Q)
				tmp->value = tmp->next->value;
			tmp->next = tmp2;
		}
		else
			tmp = tmp->next;
	}
}

bool	ft_parse(char *line, t_token **list, t_env **envi, t_cmd **cmd)
{
	if (!processline(line, list))
		return (true);
	else if (!catch_errors(list))
		return (true);
	find_node(*envi, *list);
	join_nodes(list);
	if (!prepare_cmd(*list, cmd, *envi))
		return (true);
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

void	ft_loop_main(t_env **envi)
{
	t_token			*list;
	char			*line;
	t_cmd			*cmd;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	while (1)
	{
		((1) && (line = NULL, list = NULL, cmd = NULL));
		line = readline("minishell$ ");
		if (!line)
			(printf("exit\n"), exit(0));
		if (line && ft_strlen(line) != 0)
			add_history(line);
		if (ft_parse(line, &list, envi, &cmd)
			|| ft_execute(&list, &cmd, envi))
		{
			free((void *)line);
			continue ;
		}
		free(line);
		g_malloc(0, FREE);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	g_malloc_env(0, FREE);
}

int	main(int ac, char **av, char **env)
{
	t_env	*envi;

	(void)av;
	ft_signal();
	rl_catch_signals = 0;
	envi = NULL;
	if (ac > 1)
		print_error("no argument needed");
	initenv(env, &envi);
	ft_loop_main(&envi);
}
