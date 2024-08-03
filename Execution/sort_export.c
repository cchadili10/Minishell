/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:15:53 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/03 11:05:16 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sort_export(t_export **export)
{
	t_export *tmp = *export;
	t_export *tmp2 = *export;
	char *key = NULL;
	char *value = NULL;
	int x = 0;
	while (tmp)
	{
		while (tmp2 && tmp2->next && tmp2->next->next)
		{
			if(x == 0)
			{
				if (ft_strcmp(tmp2->key, tmp2->next->key) > 0)
				{
					key = tmp2->key;
					value = tmp2->value;
					
					tmp2->key =  tmp2->next->key;
					tmp2->value =  tmp2->next->value;
					
					tmp2->next->key = key;
					tmp2->next->value = value;
				}
			}
			if (ft_strcmp(tmp2->next->key, tmp2->next->next->key) > 0)
			{
				key = tmp2->next->key;
				value = tmp2->next->value;
				
				tmp2->next->key =  tmp2->next->next->key;
				tmp2->next->value =  tmp2->next->next->value;
				
				tmp2->next->next->key = key;
				tmp2->next->next->value = value;
			}
			tmp2 = tmp2->next;
			x++;
		}
		x = 0;
		tmp = tmp->next;
		tmp2 = *export;
	}
	
}
