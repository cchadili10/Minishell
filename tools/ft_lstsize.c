/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:28:20 by yessemna          #+#    #+#             */
/*   Updated: 2024/07/03 19:10:20 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize(t_env *lst)
{
	int		count;
	t_env	*t;

	t = lst;
	count = 0;

	while (t != NULL)
	{
		count++;
		t = t -> next;
	}
	return (count);
}
