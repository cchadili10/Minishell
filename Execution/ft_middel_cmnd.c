/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_middel_cmnd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:34:54 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/06 18:30:25 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_run_mid_built_continue(t_cmd *tmp, t_env **node_env,
			t_export **export, t_exection_var *exp)
{
	if (exp->arr_join && ft_check_cmnd(tmp) < 4)
	{
		if (ft_check_cmnd(tmp) == 3 && ft_count_arg(tmp->cmds) == 1)
			ft_buitin_cmnd(tmp, node_env, export, ft_check_cmnd(tmp));
		else if (ft_check_cmnd(tmp) != 3)
			ft_buitin_cmnd(tmp, node_env, export, ft_check_cmnd(tmp));
	}
	else if (!exp->arr_join && ft_check_cmnd(tmp) < 4)
	{
		if (ft_check_cmnd(tmp) != 0 && ft_check_cmnd(tmp) != 3)
			ft_buitin_cmnd(tmp, node_env, export, ft_check_cmnd(tmp));
		else if (ft_check_cmnd(tmp) == 3
			&& ft_count_arg(tmp->cmds) == 1 && ft_check_cmnd(tmp) != 0)
			ft_buitin_cmnd(tmp, node_env, export, ft_check_cmnd(tmp));
	}
}

void	ft_run_mid_built(t_cmd *tmp, t_env **node_env,
			t_export **export, t_exection_var *exp)
{
	int	saved_stdout;
	int	saved_stdin;

	((1) && (saved_stdin = dup(0), saved_stdout = dup(1)));
	if (tmp->redir_out != 1)
	{
		dup2(tmp->redir_out, 1);
		close(tmp->redir_out);
	}
	if (!exp->arr_join && ft_check_cmnd(tmp) == -1)
	{
		printf("Minishell: %s: command not found\n", tmp->cmds[0]);
		ft_exit_status(127, SET);
	}
	dup2(exp->std_d, STDIN_FILENO);
	dup2(exp->p[1], STDOUT_FILENO);
	ft_run_mid_built_continue(tmp, node_env, export, exp);
	dup2(saved_stdout, 1);
	dup2(saved_stdin, 0);
}

void	ft_run_mid_cmd_using_fork(t_cmd *tmp, t_exection_var *exp)
{
	exp->id = fork();
	if (exp->id == 0)
	{
		dup2(exp->std_d, STDIN_FILENO);
		dup2(exp->p[1], STDOUT_FILENO);
		if (tmp->redir_out != 1)
		{
			dup2(tmp->redir_out, STDOUT_FILENO);
			close(tmp->redir_out);
		}
		if (tmp->redir_in != 0)
		{
			dup2(tmp->redir_in, 0);
			close(tmp->redir_in);
		}
		close(exp->std_d);
		close(exp->p[0]);
		close(exp->p[1]);
		execve(exp->arr_join, tmp->cmds, exp->env);
		exit(1);
	}
}

void	ft_mid_cmnd(t_cmd *tmp, t_env **node_env,
			t_export **export, t_exection_var *exp)
{
	exp->std_d = exp->p[0];
	exp->arr_join = ft_get_path(exp->arr_phat, tmp->cmds[0]);
	pipe(exp->p);
	if (ft_check_cmnd(tmp) != -1 || !exp->arr_join)
		ft_run_mid_built(tmp, node_env, export, exp);
	else
		ft_run_mid_cmd_using_fork(tmp, exp);
	close(exp->p[1]);
	close(exp->std_d);
}
