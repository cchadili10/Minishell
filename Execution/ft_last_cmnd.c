/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_cmnd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:34:48 by hchadili          #+#    #+#             */
/*   Updated: 2024/09/15 13:09:56 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_run_last_built(t_cmd *tmp, t_env **node_env,
			t_exp **export, t_exection_var *exp)
{
	dup2(exp->p[0], 0);
	if (tmp->redir_out == -1)
	{
		ft_exit_status(1, SET);
		return ;
	}
	if (tmp->redir_out != 1)
	{
		dup2(tmp->redir_out, 1);
		close(tmp->redir_out);
	}
	if (!exp->arr_join && ft_check_cmnd(tmp) == -1)
		ft_display_erorr(exp, tmp);
	ft_run_built_continue(tmp, node_env, export, exp);
}

void	ft_last_cmnd(t_cmd *tmp, t_env **node_env,
			t_exp **export, t_exection_var *exp)
{
	exp->arr_join = ft_get_path(exp->arr_phat, tmp->cmds[0], exp);
	exp->pids[exp->cont] = fork();
	if (exp->pids[exp->cont++] == 0)
	{
		if (ft_check_cmnd(tmp) != -1 || !exp->arr_join)
		{
			ft_run_last_built(tmp, node_env, export, exp);
			exit(ft_exit_status(0, GET));
		}
		if (tmp->redir_out == -1)
			exit(1);
		dup2(exp->p[0], STDIN_FILENO);
		if (tmp->redir_out != 1)
		{
			dup2(tmp->redir_out, STDOUT_FILENO);
			close(tmp->redir_out);
		}
		if (tmp->redir_in != 0)
			(1) && (dup2(tmp->redir_in, 0), close(tmp->redir_in));
		((1) && (close(exp->p[1]), close(exp->p[0])));
		execve(exp->arr_join, tmp->cmds, exp->env);
		exit(1);
	}
	ft_exit_status(0, SET);
}
