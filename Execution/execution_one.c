/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:13:51 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/03 10:14:32 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_excute_one(t_cmd **cmnds, t_export **export, char **env, t_env **node_env)
{
	t_cmd *tmp = *cmnds;
	char **arr_phat = ft_split(ft_look_for_paht(node_env), ':');
	char *arr_join = ft_get_path(arr_phat, tmp->cmds[0]);

	if (ft_check_cmnd(tmp) != -1 || !arr_join)
	{
		int saved_stdout = dup(1);
		int saved_stdout_ = dup(0);
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
		else if (arr_join)
			ft_buitin_cmnd(tmp, node_env, export, ft_check_cmnd(tmp));
		else
		{
			if (ft_check_cmnd(tmp) != 0)
				ft_buitin_cmnd(tmp, node_env, export, ft_check_cmnd(tmp));
		}
		dup2(saved_stdout, 1);
		dup2(saved_stdout_, 0);
	}
	else
	{
		int id = fork();
		if (id == 0)
		{
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
			execve(arr_join, tmp->cmds, env);
			exit(1);
			ft_exit_status(0, SET);
		}
		wait(NULL);
		if (tmp->redir_out != 1)
			close(tmp->redir_out);
	}
}