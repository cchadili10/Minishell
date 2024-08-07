/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:09:41 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/07 04:10:48 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_arg(char **str)
{
	int	x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

void	ft_execution(t_cmd **cmnds, t_env **env)
{
	int				i;
	char			**arr_env;
	static t_export	*export = NULL;

	if (!cmnds || !*cmnds || !env || !*env)
		return ;
	i = 3;
	arr_env = ft_get_charenv(env);
	if (!export)
		ft_fill_export(&export, env);
	if (ft_count_cmnds(cmnds) == 1)
		ft_excute_one(cmnds, &export, arr_env, env);
	else
		ft_excute(cmnds, &export, env);
}
