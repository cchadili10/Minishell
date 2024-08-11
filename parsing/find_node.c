/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finde_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:39:25 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/11 21:39:56 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_node(t_env *envi, t_token *list)
{
	t_token	*tmp;
	int		found;

	tmp = list;
	found = 0;
	if (tmp && tmp->value != HEREDOC)
	{
		while (tmp)
		{
			found = 0;
			if (tmp->value == VAR || tmp->value == DBL_Q)
				handle_expand(envi, &tmp, found);
			tmp = tmp->next;
		}
	}
}
