/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:15:53 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/12 22:19:35 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sort_first_node(t_exp **tmp2)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	if (ft_strcmp((*tmp2)->key, (*tmp2)->next->key) > 0)
	{
		key = (*tmp2)->key;
		value = (*tmp2)->value;
		(*tmp2)->key = (*tmp2)->next->key;
		(*tmp2)->value = (*tmp2)->next->value;
		(*tmp2)->next->key = key;
		(*tmp2)->next->value = value;
	}
}

void	ft_sort_others_node(t_exp **tmp2)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	key = (*tmp2)->next->key;
	value = (*tmp2)->next->value;
	(*tmp2)->next->key = (*tmp2)->next->next->key;
	(*tmp2)->next->value = (*tmp2)->next->next->value;
	(*tmp2)->next->next->key = key;
	(*tmp2)->next->next->value = value;
}

void	ft_sort_export(t_exp **export)
{
	t_exp		*tmp;
	t_exp		*tmp2;
	int			x;

	tmp = *export;
	tmp2 = *export;
	while (tmp)
	{
		while (tmp2 && tmp2->next && tmp2->next->next)
		{
			if (x == 0)
				ft_sort_first_node(&tmp2);
			if (ft_strcmp(tmp2->next->key, tmp2->next->next->key) > 0)
				ft_sort_others_node(&tmp2);
			tmp2 = tmp2->next;
			x++;
		}
		((1) && (x = 0, tmp2 = *export, tmp = tmp->next));
	}
}
