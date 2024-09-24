/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:59:59 by yessemna          #+#    #+#             */
/*   Updated: 2024/09/24 04:33:17 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parse(t_token **list, t_env **envi, t_cmd **cmd, t_fd_col *collector)
{
	char			*line;

	line = NULL;
	line = readline("minishell$ ");
	if (!line)
		free_garb_exite();
	if (line && ft_strlen(line) != 0)
		add_history(line);
	if (!processline(line, list))
		return (true);
	else if (!catch_errors(list))
	{
		free(line);
		return (true);
	}
	find_node(*envi, *list);
	join_nodes(list);
	if (pipe_syntax_error(list))
		return (free(line), true);
	if (!prepare_cmd(*list, cmd, *envi, collector))
		return (true);
	free(line);
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

void	ft_loop_main(t_env **envi, t_fd_col *collector)
{
	t_token			*list;
	t_cmd			*cmd;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	while (1)
	{
		(ft_signal(1), (1) && (list = NULL, cmd = NULL));
		if (ft_parse(&list, envi, &cmd, collector)
			|| ft_execute(&list, &cmd, envi))
		{
			continue ;
		}
		(unlink("/tmp/dog"));
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		g_malloc(0, FREE);
		close_all_fds(collector);
	}
	g_malloc_env(0, FREE);
}

int	main(int ac, char **av, char **env)
{
	t_env		*envi;
	t_fd_col	collector;

	(void)av;
	init_fd_collector(&collector);
	rl_catch_signals = 0;
	envi = NULL;
	if (ac > 1)
		print_error("no argument needed");
	initenv(env, &envi);
	ft_loop_main(&envi, &collector);
}
