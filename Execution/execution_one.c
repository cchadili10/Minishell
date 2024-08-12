/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:13:51 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/12 22:18:22 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_excute_one_builtin_comd(t_cmd *tmp, t_env **node_env,
		t_exp **export, t_exection_var *exp)
{
	int	saved_stdout;
	int	saved_stdin;

	((1) && (saved_stdin = dup(0), saved_stdout = dup(1)));
	if (tmp->redir_out != 1)
		((1) && (dup2(tmp->redir_out, 1), close(tmp->redir_out)));
	if (!exp->arr_join && ft_check_cmnd(tmp) == -1)
	{
		if (exp->flag == 1)
			printf("Minishell: %s: is a directory\n", tmp->cmds[0]);
		else if (exp->flag == 2)
			printf("Minishell: %s: No such file or directory\n", tmp->cmds[0]);
		else
			printf("Minishell: %s: command not found\n", tmp->cmds[0]);
		ft_exit_status(127, SET);
		exp->flag = 0;
	}
	else if (exp->arr_join)
		ft_buitin_cmnd(tmp, node_env, export, ft_check_cmnd(tmp));
	else
	{
		if (ft_check_cmnd(tmp) != 0)
			ft_buitin_cmnd(tmp, node_env, export, ft_check_cmnd(tmp));
	}
	((1) && (dup2(saved_stdout, 1), dup2(saved_stdin, 0)));
}

void	ft_excute_one_cmd_using_fork(t_cmd *tmp,
			t_exection_var *exp, char **env)
{
	exp->id = fork();
	if (exp->id == 0)
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
		execve(exp->arr_join, tmp->cmds, env);
		exit(1);
		ft_exit_status(0, SET);
	}
	wait(NULL);
	if (tmp->redir_out != 1)
		close(tmp->redir_out);
}

void	ft_excute_one(t_cmd **cmnds, t_exp **export,
			char **env, t_env **node_env)
{
	t_cmd			*tmp;
	t_exection_var	exp;

	ft_set_zero(&exp);
	tmp = *cmnds;
	exp.arr_phat = ft_split(ft_look_for_paht(node_env), ':');
	exp.arr_join = ft_get_path(exp.arr_phat, tmp->cmds[0], &exp);
	if (ft_check_cmnd(tmp) != -1 || !exp.arr_join)
		ft_excute_one_builtin_comd(tmp, node_env, export, &exp);
	else
		ft_excute_one_cmd_using_fork(tmp, &exp, env);
}
