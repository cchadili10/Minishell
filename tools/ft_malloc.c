/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 01:36:32 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/23 20:35:30 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*g_malloc(size_t size, t_call call)
{
	static t_col	*head;
	t_col			*tmp;
	void			*ptr;

	if (call == MALLOC)
	{
		ptr = malloc(size);
		if (!ptr)
			return (clear_all(&head), NULL);
		tmp = new_node(ptr);
		if (!tmp)
			return (clear_all(&head), free(ptr), NULL);
		add_back(&head, tmp);
		return (ptr);
	}
	else if (call == FREE)
		clear_all(&head);
	return (NULL);
}

void	*g_malloc_env(size_t size, t_call call)
{
	static t_col	*head;
	t_col			*tmp;
	void			*ptr;

	if (call == MALLOC)
	{
		ptr = malloc(size);
		if (!ptr)
			return (clear_all(&head), NULL);
		tmp = new_node(ptr);
		if (!tmp)
			return (clear_all(&head), free(ptr), NULL);
		add_back(&head, tmp);
		return (ptr);
	}
	else if (call == FREE)
		clear_all(&head);
	return (NULL);
}
