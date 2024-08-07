/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 01:53:59 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/07 17:17:24 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_env **env, t_cmd *cmnds)
{
	t_env	*tmp;

	tmp = *env;
	(void)cmnds;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	ft_exit_status(0, SET);
}
