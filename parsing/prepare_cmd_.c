/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd_.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 04:41:42 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/07 04:46:44 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*lst_new_cmd(char **line, int in, int out)
{
	t_cmd	*new;
	int		i;

	i = 0;
	if (!line)
		return (NULL);
	new = g_malloc(sizeof(t_cmd), MALLOC);
	if (!new)
		return (NULL);
	new->cmds = line;
	new->redir_in = in;
	new->redir_out = out;
	new->next = NULL;
	return (new);
}

void	lst_add_back_cmd(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

	tmp = *head;
	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
