/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:59:59 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/19 19:22:30 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		(ft_signal(1), (1) && (line = NULL, list = NULL, cmd = NULL));
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
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	g_malloc(0, FREE);
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
	system("leaks minishell");
}
