/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:30:43 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/03 10:31:40 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_buitin_cmnd(t_cmd *cmnds, t_env **env, t_export **export, int place)
{
	if (place == 0)
		ft_env(env, cmnds);
	if (place == 1)
		ft_pwd(env);
	if (place == 2)
		ft_echo(cmnds);
	if (place == 3)
		ft_exit_status(0, GET);
	if (place == 4)
		ft_export(cmnds, env, export);
	if (place == 5)
		ft_cd(cmnds, env, export);
	if (place == 6)
		ft_unset(cmnds, export, env);
	if (place == 7)
		ft_exit(cmnds);
}

int	ft_check_cmnd(t_cmd *cmnd)
{
	static char *builts[] = {"env", "pwd", "echo", "$?", "export" ,"cd", "unset", "exit", NULL};
	int x = 0;
	t_cmd *tmp;

	tmp = cmnd;
	while (builts[x])
	{
		if (strcmp(builts[x], tmp->cmds[0]) == 0)
			break ;
		x++;
	}
	if (x >= 8)
		return (-1);
	return (x);
}