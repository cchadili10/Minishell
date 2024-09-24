/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hrdc_apnd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:05:56 by yessemna          #+#    #+#             */
/*   Updated: 2024/09/24 00:42:21 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	hd_apnd_hlper(t_token **tmp, t_main_prepare_cmd **t)
{
	if ((*t)->pipe_hd)
	{
		(*tmp) = (*tmp)->next;
		return (1);
	}
	if ((*t)->cmd_exist)
	{
		(*tmp) = (*tmp)->next;
		return (1);
	}
	if ((*t)->piped)
	{
		(*tmp)->key = ft_strdup(":");
		return (1);
	}
	return (0);
}

int	redir_hd(t_token **tmp, t_main_prepare_cmd *t, t_env *envi)
{
	if ((t->red_in) != 0)
		close((t->red_in));
	(*tmp) = (*tmp)->next;
	if (*tmp && (*tmp)->value == SPC)
		(*tmp) = (*tmp)->next;
	ft_here_doc(*tmp, envi, &t->red_in, t->col);
	close(t->red_in);
	(t->red_in) = ft_open(t->col, "/tmp/dog", O_RDONLY, 0644);
	if ((t->red_in) < 0)
		return (0);
	unlink("/tmp/dog");
	if (hd_apnd_hlper(tmp, &t))
		return (1);
	*tmp = (*tmp)->next;
	return (1);
}

int	redir_apnd(t_token **tmp, t_main_prepare_cmd *t)
{
	(*tmp) = (*tmp)->next;
	if (*tmp && (*tmp)->value == SPC)
		(*tmp) = (*tmp)->next;
	if (!(*tmp)->key)
	{
		if (!t->cmd_exist)
			(*tmp)->key = ft_strdup(":");
		ft_printf("Minishell: %s: ambiguous redirect\n", (*tmp)->copy_key);
		ft_exit_status(1, SET);
		t->red_in = -1;
		return (1);
	}
	(t->red_out) = ft_open(t->col, (*tmp)->key, O_WRONLY
			| O_CREAT | O_APPEND, 0644);
	if ((t->red_out) < 0)
		return (3);
	if (hd_apnd_hlper(tmp, &t))
		return (1);
	*tmp = (*tmp)->next;
	return (1);
}
