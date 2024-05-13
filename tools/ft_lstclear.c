/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:04:40 by yessemna          #+#    #+#             */
/*   Updated: 2024/05/12 17:47:00 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del(void *content)
{
	free(content);
}

void	ft_lstdelone(t_env *lst)
{
	if (!lst)
		return ;
	del(lst->key);
	lst->value = 0;
	// printf("\n>>>>>>>>><<<<<<<<<<<<<<<\n");
	free(lst);
}

void ft_lstclear(t_env **lst)
{
	t_env *tmp;
	t_env *cur;

	if (!lst || !*lst)
		return ;
	cur = *lst;
	while (cur)
	{
		tmp = cur->next;
		ft_lstdelone(cur);
		cur = tmp;
	}
	*lst = NULL;
}