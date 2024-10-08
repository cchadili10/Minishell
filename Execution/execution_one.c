/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:13:51 by hchadili          #+#    #+#             */
/*   Updated: 2024/09/18 22:36:44 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_excute_one_builtin_comd(t_cmd *tmp, t_env **node_env,
		t_exp **export, t_exection_var *exp)
{
	int	saved_stdout;
	int	saved_stdin;

	if (tmp->redir_out == -1 || tmp->redir_in == -1)
	{
		ft_exit_status(1, SET);
		return ;
	}
	((1) && (saved_stdin = dup(0), saved_stdout = dup(1)));
	if (tmp->redir_out != 1)
		((1) && (dup2(tmp->redir_out, 1), close(tmp->redir_out)));
	if (!exp->arr_join && ft_check_cmnd(tmp) == -1)
		ft_display_erorr(exp, tmp);
	else if (exp->arr_join)
		ft_buitin_cmnd(tmp, node_env, export, ft_check_cmnd(tmp));
	else
	{
		if (ft_check_cmnd(tmp) != 0)
			ft_buitin_cmnd(tmp, node_env, export, ft_check_cmnd(tmp));
		else if (ft_check_cmnd(tmp) == 0)
			ft_printf("Minishell: %s: No such file or directory\n",
				tmp->cmds[0]);
	}
	((1) && (dup2(saved_stdout, 1), dup2(saved_stdin, 0)));
	((1) && (close(saved_stdout), close(saved_stdin)));
}

void	ft_excute_one_cmd_using_fork(t_cmd *tmp,
			t_exection_var *exp, char **env)
{
	int	status[2];

	ft_signal(2);
	exp->id = fork();
	if (exp->id == 0)
	{
		ft_signal(3);
		if (tmp->redir_out == -1 || tmp->redir_in == -1)
			exit(1);
		if (tmp->redir_out != 1)
		{
			dup2(tmp->redir_out, 1);
			close(tmp->redir_out);
		}
		if (tmp->redir_in != 0)
			(1) && (dup2(tmp->redir_in, 0), close(tmp->redir_in));
		execve(exp->arr_join, tmp->cmds, env);
		exit(1);
	}
	waitpid(exp->id, status, 0);
	status[1] = WEXITSTATUS(status[0]);
	if (WIFSIGNALED(status[0]))
		status[1] = 128 + WTERMSIG(status[0]);
	ft_exit_status(status[1], SET);
}

void	ft_excute_one(t_cmd **cmnds, t_exp **export,
			char **env, t_env **node_env)
{
	t_cmd			*tmp;
	t_exection_var	exp;

	ft_set_zero(&exp);
	tmp = *cmnds;
	exp.arr_phat = ft_split(ft_look_for_paht(node_env), ':', 9);
	exp.arr_join = ft_get_path(exp.arr_phat, tmp->cmds[0], &exp);
	if (ft_check_cmnd(tmp) != -1 || !exp.arr_join)
		ft_excute_one_builtin_comd(tmp, node_env, export, &exp);
	else
		ft_excute_one_cmd_using_fork(tmp, &exp, env);
}
