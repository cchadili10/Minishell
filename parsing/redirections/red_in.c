/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:59:59 by yessemna          #+#    #+#             */
/*   Updated: 2024/09/26 23:21:45 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redin_hlper(t_token **tmp, t_main_prepare_cmd **t)
{
	if (access((*tmp)->key, F_OK) == -1)
	{
		if ((*t)->flag == 0)
			ft_printf("Minishell: %s: No such file or directory\n",
				(*tmp)->copy_key);
		(*t)->flag = 1;
		(*tmp)->key = NULL;
		ft_exit_status(1, SET);
		(*t)->red_in = -1;
		if ((*t)->piped && !(*t)->cmd_exist)
			(*tmp)->key = ft_strdup("true");
		return (4);
	}
	return (0);
}

int	redir_in(t_token **tmp, t_main_prepare_cmd	*t)
{
	*tmp = (*tmp)->next;
	if (*tmp && (*tmp)->value == SPC)
		*tmp = (*tmp)->next;
	if (redin_hlper(tmp, &t) == 4)
		return (4);
	(t->red_in) = ft_open(t->col, (*tmp)->key, O_RDONLY, 0644);
	if ((t->red_in) < 0)
		return (3);
	if (t->pipe_in)
	{
		*tmp = (*tmp)->next;
		return (1);
	}
	if (t->piped && !t->cmd_exist)
	{
		(*tmp)->key = ft_strdup("true");
		return (1);
	}
	*tmp = (*tmp)->next;
	ft_exit_status(0, SET);
	return (1);
}
