/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:33:24 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/12 22:18:22 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset_env_exp(t_cmd *cmnd, t_exp **export, t_env **env, int check)
{
	int	x;

	x = 1;
	while (cmnd->cmds[x])
	{
		if (ft_check_key(cmnd->cmds[x]))
		{
			if (ft_find_key(export, cmnd->cmds[x]))
			{
				ft_remove_key_export(export, cmnd->cmds[x]);
				ft_remove_key_env(env, cmnd->cmds[x]);
			}
		}
		else
		{
			printf("unset: `%s': not a valid identifier\n", cmnd->cmds[x]);
			check = 1;
		}
		x++;
	}
	if (check)
		ft_exit_status(1, SET);
	else
		ft_exit_status(0, SET);
}

void	ft_unset(t_cmd *cmnd, t_exp **export, t_env **env)
{
	int	x;
	int	check;

	((1) && (x = 0, check = 0));
	while (cmnd->cmds[x])
		x++;
	if (x == 1)
	{
		ft_exit_status(0, SET);
		return ;
	}
	else
		ft_unset_env_exp(cmnd, export, env, check);
}
