/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 01:53:59 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/19 18:32:47 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void ft_env(t_env **env, t_cmd *cmnds)
{
	t_env *tmp = *env;
	(void)cmnds;
	
	while (tmp)
	{
		printf("%s=%s\n",tmp->key, tmp->value);
		tmp = tmp->next;
	}
}