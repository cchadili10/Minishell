/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 21:18:04 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/30 01:19:08 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_display_erorr(t_exection_var *exp, t_cmd *tmp)
{
	if (exp->flag == 1)
	{
		ft_printf("Minishell: %s: is a directory\n", tmp->cmds[0]);
		ft_exit_status(126, SET);
		return ;
	}
	else if (exp->flag == 2 || tmp->redir_in == -1)
		ft_printf("Minishell: %s: No such file or directory\n", tmp->cmds[0]);
	else if (exp->flag == 3)
	{
		ft_printf("Minishell: %s: Permission denied\n", tmp->cmds[0]);
		ft_exit_status(126, SET);
		return ;
	}
	else if (exp->flag == 4)
	{
		ft_printf("Minishell: %s: Not a directory\n", tmp->cmds[0]);
		ft_exit_status(126, SET);
		return ;
	}
	else if (exp->flag == 0 || exp->flag == 0)
		ft_printf("Minishell: %s: command not found\n", tmp->cmds[0]);
	(tmp->cmds[0]) && (ft_exit_status(127, SET));
	(!tmp->cmds[0]) && (ft_exit_status(0, SET));
	exp->flag = 0;
}

char	*ft_check_cmd_erorrs(char *first_cmnd, t_exection_var *exp, int test)
{
	if (test == 1)
	{
		if (access(first_cmnd, F_OK) == 0)
		{
			if (access(first_cmnd, X_OK) == 0)
				return (first_cmnd);
			(first_cmnd[0] == '/') && (exp->flag = 6);
			(first_cmnd[0] != '/') && (exp->flag = 3);
		}
		else
			exp->flag = 2;
		return (NULL);
	}
	else if (test == 2)
	{
		exp->flag = 4;
		return (NULL);
	}
	else if (test == 3)
	{
		exp->flag = 1;
		return (NULL);
	}
	return (NULL);
}

char	*ft_loop_for_path(char **arr_phat,
		char *first_cmnd, t_exection_var *exp)
{
	char	*arr_join_one;
	char	*arr_join;
	int		x;

	x = -1;
	if (!arr_phat)
	{
		exp->flag = 2;
		return (NULL);
	}
	while (arr_phat[++x])
	{
		arr_join_one = ft_srtjoin(arr_phat[x], "/");
		arr_join = ft_srtjoin(arr_join_one, first_cmnd);
		if (access(arr_join, F_OK | X_OK) == 0)
			break ;
		else if (access(arr_join, F_OK | X_OK) == -1 && !arr_phat[x + 1])
			return (NULL);
	}
	return (arr_join);
}

void	ft_run_built_continue(t_cmd *tmp, t_env **node_env,
			t_exp **export, t_exection_var *exp)
{
	if (exp->arr_join)
		ft_buitin_cmnd(tmp, node_env, export, ft_check_cmnd(tmp));
	else if (!exp->arr_join)
	{
		if (ft_check_cmnd(tmp) != 0)
			ft_buitin_cmnd(tmp, node_env, export, ft_check_cmnd(tmp));
	}
}
