/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:40:16 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/12 22:18:22 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_second_arg(char *str)
{
	int	x;

	x = 0;
	if (!str[x])
		return (0);
	while (str[x])
	{
		if (str[x] != '.')
			return (0);
		x++;
	}
	return (1);
}

void	ft_cd(t_cmd *cmnd, t_env **env, t_exp **export)
{
	int	x;

	x = 0;
	while (cmnd->cmds[x])
		x++;
	if (x == 1)
	{
		if (ft_go_to_home_export(export))
			ft_go_to_home_env(env);
	}
	else
	{
		if (ft_set_path_for_export(export, cmnd, x))
		{
			ft_set_path_for_env(env);
			ft_exit_status(0, SET);
		}
	}
}
