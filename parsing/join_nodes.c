/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:22:57 by yessemna          #+#    #+#             */
/*   Updated: 2024/09/16 23:31:31 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_nodes_helper(t_token **tmp)
{
	if ((*tmp)->value == CMD && (*tmp)->next && (*tmp)->next->value == CMD)
	{
		((1) && ((*tmp)->key = ft_srtjoin((*tmp)->key, (*tmp)->next->key),
				(*tmp)->next = (*tmp)->next->next));
		(*tmp)->value = DBL_Q;
	}
}

void	join_nodes(t_token **list)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = *list;
	while (tmp)
	{
		join_nodes_helper(&tmp);
		if (tmp->next && (tmp->value == DBL_Q || tmp->value == SNGL_Q
				|| tmp->value == VAR || tmp->value == DBL_VAR
				|| tmp->value == CMD) && (tmp->next->value == DBL_Q
				|| tmp->next->value == SNGL_Q
				|| tmp->next->value == VAR || tmp->next->value == DBL_VAR
				|| tmp->next->value == CMD))
		{
			tmp2 = tmp->next->next;
			tmp->key = ft_srtjoin(tmp->key, tmp->next->key);
			if (tmp->next->value == DBL_Q || tmp->next->value == SNGL_Q)
				tmp->value = tmp->next->value;
			tmp->next = tmp2;
		}
		else
			tmp = tmp->next;
	}
}

void	token_exit_status(char **line, t_token **list, int *i)
{
	if (*line[*i] == '$' && *line[(*i) + 1] == '?')
	{
		lst_add_back(list, lst_new("$?", DBL_Q));
		(*i) += 2;
	}
}
