/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:07:37 by yessemna          #+#    #+#             */
/*   Updated: 2024/09/24 00:41:40 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redout_hlper(t_token **tmp, t_main_prepare_cmd **t)
{
	if (!(*tmp)->key)
	{
		if (!(*t)->cmd_exist)
			(*tmp)->key = ft_strdup(":");
		ft_printf("Minishell: %s: ambiguous redirect\n", (*tmp)->copy_key);
		ft_exit_status(1, SET);
		(*t)->red_in = -1;
		return (1);
	}
	return (0);
}

int	redir_out(t_token **tmp, t_main_prepare_cmd *t)
{
	if ((t->red_out) != 1)
		close((t->red_out));
	*tmp = (*tmp)->next;
	if (*tmp && (*tmp)->value == SPC)
		*tmp = (*tmp)->next;
	if (redout_hlper(tmp, &t))
		return (1);
	(t->red_out) = ft_open(t->col, (*tmp)->key, O_WRONLY
			| O_CREAT | O_TRUNC, 0644);
	if ((t->red_out) < 0)
		return (2);
	if (t->cmd_exist)
	{
		*tmp = (*tmp)->next;
		return (1);
	}
	if (t->piped)
	{
		(*tmp)->key = ft_strdup(":");
		return (1);
	}
	*tmp = (*tmp)->next;
	return (1);
}
