/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:35:30 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/07 04:10:21 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initenv(char **env, t_env **envi)
{
	char	*key;
	char	*value;
	int		index;
	int		i;

	index = 0;
	i = -1;
	while (env && env[++i])
	{
		index = find_char(env[i], '=');
		key = ft_substr_env(env[i], 0, index);
		value = ft_substr_env(env[i], index + 1, ft_strlen(env[i]) - index);
		if (ft_strcmp(key, "SHLVL") == 0)
			value = ft_itoa(ft_atoi(value) + 1);
		else if (ft_strcmp(key, "_") == 0)
			value = "/usr/bin/env";
		if (ft_strcmp(key, "OLDPWD") == 0)
			continue ;
		lst_add_back_env(envi, lst_new_env(key, value));
	}
}
