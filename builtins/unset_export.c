/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:00:12 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/27 02:13:53 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_look_for_key_export(t_exp **tmp, char *key, int *check)
{
	while (*tmp)
	{
		if (ft_strcmp((*tmp)->key, key) == 0)
		{
			*check = 1;
			break ;
		}
		else if (ft_strcmp((*tmp)->next->key, key) == 0)
			break ;
		*tmp = (*tmp)->next;
	}
}

void	ft_remove_key_export(t_exp **export, char *key)
{
	t_exp	*tmp;
	t_exp	*for_free_export;
	int		check;

	tmp = *export;
	check = 0;
	ft_look_for_key_export(&tmp, key, &check);
	if (check)
	{
		for_free_export = *export;
		*export = for_free_export->next;
		free(for_free_export);
	}
	else if (tmp->next->next)
	{
		for_free_export = tmp->next;
		tmp->next = tmp->next->next;
		// free(for_free_export); // <------ dbl free
	}
	else if (!tmp->next->next && tmp->next)
	{
		for_free_export = tmp->next;
		tmp->next = NULL;
		// free(for_free_export); //<------ dbl free
	}
}
