/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_cmnd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:34:51 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/03 13:36:15 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_first_cmnd(t_cmd *tmp, t_env **node_env, t_export **export, int *p)
{
	char	*arr_join;
	int		saved_stdout;
	int		id;
	char **env = ft_get_charenv(node_env);
	char **arr_phat = ft_split(ft_look_for_paht(node_env), ':');

	arr_join = ft_get_path(arr_phat, tmp->cmds[0]);
	pipe(p);
	if (ft_check_cmnd(tmp) != -1 || !arr_join)
	{
		saved_stdout = dup(1);
		dup2(p[1], STDOUT_FILENO); // 3a9l gad hadi li ba9at lik ou mid cmnd ou last cmnd
		if (tmp->redir_out != 1)
		{
			dup2(tmp->redir_out, 1);
			close(tmp->redir_out);
		}
		if (!arr_join && ft_check_cmnd(tmp) == -1)
		{
			printf("Minishell: %s: command not found\n", tmp->cmds[0]);
			ft_exit_status(127, SET);
		}
		if (arr_join && ft_check_cmnd(tmp) < 5)
		{
			if (ft_check_cmnd(tmp) == 4 && ft_count_arg(tmp->cmds) == 1)
				ft_buitin_cmnd(tmp, node_env, export, ft_check_cmnd(tmp));
			else if (ft_check_cmnd(tmp) != 4)
				ft_buitin_cmnd(tmp, node_env, export, ft_check_cmnd(tmp));
		}
		else if (!arr_join && ft_check_cmnd(tmp) < 5)
		{
			if (ft_check_cmnd(tmp) != 0 && ft_check_cmnd(tmp) != 4)
				ft_buitin_cmnd(tmp, node_env, export, ft_check_cmnd(tmp));
			else if (ft_check_cmnd(tmp) == 4 && ft_count_arg(tmp->cmds) == 1 && ft_check_cmnd(tmp) != 0)
				ft_buitin_cmnd(tmp, node_env, export, ft_check_cmnd(tmp));
		}
		dup2(saved_stdout, 1);
	}
	else
	{
		id = fork();
		if (id == 0)
		{
			dup2(p[1], STDOUT_FILENO);
			if (tmp->redir_out != 1)
			{
				dup2(tmp->redir_out, 1);
				close(tmp->redir_out);
			}
			if (tmp->redir_in != 0)
			{
				dup2(tmp->redir_in, 0);
				close(tmp->redir_in);
			}
			close(p[0]);
			close(p[1]);
			execve(arr_join, tmp->cmds, env);
			exit(1);
		}
	}
	close(p[1]);
}