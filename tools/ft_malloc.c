/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 01:36:32 by yessemna          #+#    #+#             */
/*   Updated: 2024/09/25 18:46:43 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_exit(void *ptr, t_col **head)
{
	ft_printf("minishell : error malloc failed\n");
	free(ptr);
	clear_all(head);
	exit(1);
}

void	*g_malloc(size_t size, t_call call)
{
	static t_col	*head;
	t_col			*tmp;
	void			*ptr;

	if (call == MALLOC)
	{
		ptr = malloc(size);
		if (!ptr)
		{
			ft_printf("minishell : error malloc failed\n");
			clear_all(&head);
			exit(1);
		}
		tmp = new_node(ptr);
		if (!tmp)
			ft_free_exit(ptr, &head);
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
		{
			ft_printf("minishell : error malloc failed\n");
			clear_all(&head);
			exit(1);
		}
		tmp = new_node(ptr);
		if (!tmp)
			ft_free_exit(ptr, &head);
		add_back(&head, tmp);
		return (ptr);
	}
	else if (call == FREE)
		clear_all(&head);
	return (NULL);
}
