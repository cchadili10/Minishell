/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:00:17 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/27 02:13:40 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_look_for_key_env(t_env **tmp, char *key, int *check)
{
	while (*tmp)
	{
		if (ft_strcmp((*tmp)->key, key) == 0)
		{
			*check = 1;
			break ;
		}
		else if ((*tmp)->next)
		{
			if (ft_strcmp((*tmp)->next->key, key) == 0)
				break ;
		}
		*tmp = (*tmp)->next;
	}
}

void	ft_remove_key_env(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*for_free_env;
	int		check;

	((1) && (tmp = *env, check = 0));
	ft_look_for_key_env(&tmp, key, &check);
	if (check && tmp)
	{
		for_free_env = *env;
		*env = for_free_env->next;
		free(for_free_env);
	}
	else if (tmp && tmp->next->next)
	{
		for_free_env = tmp->next;
		tmp->next = tmp->next->next;
		// free(for_free_env);// <------ dbl free
	}
	else if (tmp && !tmp->next->next && tmp->next)
	{
		for_free_env = tmp->next;
		tmp->next = NULL;
		// free(for_free_env); //<------ dbl free
	}
}
