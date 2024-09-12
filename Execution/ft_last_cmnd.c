/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_cmnd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:34:48 by hchadili          #+#    #+#             */
/*   Updated: 2024/09/12 16:30:33 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_run_last_built(t_cmd *tmp, t_env **node_env,
			t_exp **export, t_exection_var *exp)
{
	int	saved_stdout;
	int	saved_stdin;

	((1) && (saved_stdin = dup(0), saved_stdout = dup(1)));
	dup2(exp->p[0], 0);
	if (tmp->redir_out != 1)
	{
		dup2(tmp->redir_out, 1);
		close(tmp->redir_out);
	}
	if (!exp->arr_join && ft_check_cmnd(tmp) == -1)
		ft_display_erorr(exp, tmp);
	ft_run_built_continue(tmp, node_env, export, exp);
	((1) && (dup2(saved_stdout, 1), dup2(saved_stdin, 0)));
	((1) && (close(saved_stdout), close(saved_stdin)));
}

void	ft_last_cmnd(t_cmd *tmp, t_env **node_env,
			t_exp **export, t_exection_var *exp)
{
	ft_expand_exit_status(tmp->cmds);
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
			exit(0);
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
	waitpid(exp->pids[exp->cont - 1], &exp->status, 0);
	ft_exit_status(WEXITSTATUS(exp->status), SET);
}
