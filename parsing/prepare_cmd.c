/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 04:35:26 by yessemna          #+#    #+#             */
/*   Updated: 2024/09/26 16:09:33 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	short_hand(t_main_prepare_cmd *t, t_cmd **cmd)
{
	if (t->cmd_strs)
		lst_add_back_cmd(cmd, lst_new_cmd(t->cmd_strs, t->red_in, t->red_out));
	else
		close(t->red_in);
}

void	ft_check_for_pipe(t_token *tmp, t_main_prepare_cmd *t)
{
	t_token	*tmp2;

	tmp2 = tmp;
	while (tmp2)
	{
		if (tmp2->value == PIPE)
			t->piped = true;
		tmp2 = tmp2->next;
	}
}

void	main_prepare_cmd(t_token **tmp, t_cmd **cmd
	, t_env *envi, t_main_prepare_cmd *t)
{
	(1) && (t->pipe_hd = false, t->red_in = 0, t->red_out = 1);
	while (*tmp && (*tmp)->value != PIPE)
	{
		if ((!(*tmp)->next && (*tmp)->value == SPC))
		{
			*tmp = (*tmp)->next;
			continue ;
		}
		if ((*tmp && (*tmp)->next && (*tmp)->value == SPC))
			*tmp = (*tmp)->next;
		if ((*tmp && (*tmp)->next && (*tmp)->next->next && (*tmp)->value == CMD)
			&& (is_redir((*tmp)->next->value) || ((*tmp)->next->value == SPC
					&& is_redir((*tmp)->next->next->value))))
		{
			t->cmd_exist = true;
		}
		if ((*tmp && (*tmp)->value == PIPE))
			continue ;
		else if ((*tmp)->value != PIPE && handle_redir(tmp, t, envi))
			continue ;
		(split_in_cmd(&t->cmd_strs, tmp), *tmp = (*tmp)->next);
	}
	short_hand(t, cmd);
	t->cmd_strs = NULL;
}

void	init_t_main(t_main_prepare_cmd *t, t_fd_col *collector)
{
	t->red_in = 0;
	t->red_out = 1;
	t->flag = 0;
	t->cmd_strs = NULL;
	t->pipe_in = false;
	t->cmd_exist = false;
	t->piped = false;
	t->pipe_hd = false;
	t->col = collector;
	t->std = dup(0);
}

int	prepare_cmd(t_token *list, t_cmd **cmd, t_env *envi, t_fd_col *collector)
{
	t_token				*tmp;
	t_main_prepare_cmd	t;

	tmp = list;
	init_t_main(&t, collector);
	ft_check_for_pipe(tmp, &t);
	(signal(SIGINT, ft_herdoc), rl_catch_signals = 1);
	while (tmp)
	{
		if (tmp && tmp->value == SPC)
			tmp = tmp->next;
		main_prepare_cmd(&tmp, cmd, envi, &t);
		if (tmp)
			tmp = tmp->next;
	}
	if (!ttyname(0))
	{
		ft_exit_herdog(1, SET);
		close_all_fds(t.col);
	}
	(dup2(t.std, 0), close(t.std), rl_catch_signals = 0);
	ft_signal(1);
	t.flag = 0;
	return (1);
}
