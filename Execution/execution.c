/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:09:41 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/03 13:23:07 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_arg(char **str)
{
	int x = 0;
	while (str[x])
		x++;
	return x;
}

void	ft_execution(t_cmd **cmnds, t_env **env)
{
	if (!cmnds || !*cmnds || !env || !*env)
		return ;
	int count_cmnd;
	char **arr_env = NULL;
	static t_export *export = NULL;
	count_cmnd = 0;
	arr_env = ft_get_charenv(env);
	if (!export)
		ft_fill_export(&export, env);
	if (ft_count_cmnds(cmnds) == 1)
		ft_excute_one(cmnds, &export, arr_env, env);
	else
		ft_excute(cmnds, &export, env);
	for (int i = 3; i < OPEN_MAX; i++)
	{
		close(i);
	}
	// write(0,"0 shj\n",7);
	// write(1,"1 shj\n",7);
	// write(2,"2 shj\n",7);
}