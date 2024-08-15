/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 21:18:04 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/15 21:45:34 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_display_erorr(t_exection_var *exp, t_cmd *tmp)
{
	if (exp->flag == 1)
		ft_printf("Minishell: %s: is a directory\n", tmp->cmds[0]);
	else if (exp->flag == 2)
		ft_printf("Minishell: %s: No such file or directory\n", tmp->cmds[0]);
	else if (exp->flag == 3)
		ft_printf("Minishell: %s: Permission denied\n", tmp->cmds[0]);
	else if (exp->flag == 4)
		ft_printf("Minishell: %s: Not a directory\n", tmp->cmds[0]);
	else
		ft_printf("Minishell: %s: command not found\n", tmp->cmds[0]);
	ft_exit_status(127, SET);
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
			else
				exp->flag = 3;
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

char	*ft_loop_for_path(char **arr_phat, char *first_cmnd)
{
	char	*arr_join_one;
	char	*arr_join;
	int		x;

	x = -1;
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
