/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 01:53:59 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/17 06:03:35 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void ft_env(char **env, t_cmd **cmnds)
{
	// t_cmd *tmp = *cmnds;
	(void)cmnds;
	int x;
	x = 0;
	while (env[x])
	{
		printf("%s\n",env[x]);
		x++;
	}
}