/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 20:46:35 by yessemna          #+#    #+#             */
/*   Updated: 2024/09/24 00:43:51 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	h_h_hrdc(t_token **tmp2, t_main_prepare_cmd **t)
{
	while ((*tmp2) && (*tmp2)->next && (*tmp2)->next->next
		&& (*tmp2)->value == HEREDOC
		&& ((*tmp2)->next->value == CMD || ((*tmp2)->next->value == SPC
				&& (*tmp2)->next->next->value == CMD)))
	{
		(*tmp2) = (*tmp2)->next;
		if ((*tmp2)->value == SPC)
			(*tmp2) = (*tmp2)->next;
		if ((*tmp2)->value == CMD)
			(*tmp2) = (*tmp2)->next;
		if ((*tmp2) && (*tmp2)->value == SPC)
			(*tmp2) = (*tmp2)->next;
	}
	if ((*tmp2) && (*tmp2)->value == CMD)
		(*t)->pipe_hd = true;
}

void	h_h_in(t_token **tmp2, t_main_prepare_cmd **t)
{
	while ((*tmp2) && (*tmp2)->next && (*tmp2)->next->next
		&& (*tmp2)->value == IN
		&& ((*tmp2)->next->value == CMD || ((*tmp2)->next->value == SPC
				&& (*tmp2)->next->next->value == CMD)))
	{
		(*tmp2) = (*tmp2)->next;
		if ((*tmp2)->value == SPC)
			(*tmp2) = (*tmp2)->next;
		if ((*tmp2)->value == CMD)
			(*tmp2) = (*tmp2)->next;
		if ((*tmp2) && (*tmp2)->value == SPC)
			(*tmp2) = (*tmp2)->next;
	}
	if ((*tmp2) && (*tmp2)->value == CMD)
		(*t)->pipe_in = true;
}

void	handler_hlper(t_token **tmp, t_main_prepare_cmd **t)
{
	t_token	*tmp2;

	tmp2 = *tmp;
	if ((*tmp)->value == HEREDOC)
		h_h_hrdc(&tmp2, t);
	if ((*tmp)->value == IN)
		h_h_in(&tmp2, t);
}

void	p_denied(t_token **tmp)
{
	ft_printf("Minishell: %s: Permission denied\n", (*tmp)->copy_key);
	while ((*tmp) && (*tmp)->next && (*tmp)->next->value != PIPE)
		(*tmp) = (*tmp)->next;
	if ((*tmp) && (*tmp)->next && (*tmp)->next->value == SPC)
		(*tmp) = (*tmp)->next;
	(*tmp)->key = NULL;
}

int	handle_redir(t_token **tmp, t_main_prepare_cmd *t, t_env *envi)
{
	int	flag;

	flag = 0;
	if ((*tmp)->value == HEREDOC || (*tmp)->value == IN)
		handler_hlper(tmp, &t);
	if ((*tmp)->value == IN)
		flag = redir_in(tmp, t);
	else if ((*tmp)->value == HEREDOC)
		return (redir_hd(tmp, t, envi));
	else if ((*tmp)->value == APPEND)
		flag = redir_apnd(tmp, t);
	else if ((*tmp)->value == OUT)
		flag = redir_out(tmp, t);
	if (flag == 4)
		return (0);
	if (flag == 3)
		ft_printf("Minishell: %s: Permission denied\n", (*tmp)->copy_key);
	else if (flag == 2)
		p_denied(tmp);
	return (flag);
}
