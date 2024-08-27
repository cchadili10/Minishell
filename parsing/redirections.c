/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 20:46:35 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/27 17:46:14 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_in(t_token **tmp, t_main_prepare_cmd	*t)
{
	*tmp = (*tmp)->next;
	if (*tmp && (*tmp)->value == SPC)
		*tmp = (*tmp)->next;
	if (access((*tmp)->key, F_OK) == -1)
	{
		t->red_in = -1;
		return (1);
	}
	(t->red_in) = open((*tmp)->key, O_RDONLY);
	if ((t->red_in) < 0)
		return (3);
	if ((*tmp)->next && (*tmp)->next->next && ((*tmp)->next->value == PIPE
			|| ((*tmp)->next->value == SPC
				&& (*tmp)->next->next->value == PIPE)))
		return (1);
	if (t->piped)
		return (1);
	*tmp = (*tmp)->next;
	return (1);
}

int	redir_hd(t_token **tmp, t_main_prepare_cmd *t, t_env *envi)
{
	if ((t->red_in) != 0)
		close((t->red_in));
	(*tmp) = (*tmp)->next;
	if (*tmp && (*tmp)->value == SPC)
		(*tmp) = (*tmp)->next;
	ft_here_doc(*tmp, envi, &t->red_in);
	close(t->red_in);
	(t->red_in) = open("/tmp/dog", O_RDONLY);
	if ((t->red_in) < 0)
		return (0);
	printf("KEY: %s\n", (*tmp)->key);
	if (((*tmp)->next && (*tmp)->next->next && ((*tmp)->next->value == PIPE || ((*tmp)->next->value == SPC && (*tmp)->next->next->value == PIPE))) || !(*tmp)->next || !(*tmp)->next->next)
	{
		(*tmp)->key = "/tmp/dog";
		return (1);
	}
	*tmp = (*tmp)->next;
	return (1);
}

int	redir_apnd(t_token **tmp, t_main_prepare_cmd *t)
{
	(*tmp) = (*tmp)->next;
	if (*tmp && (*tmp)->value == SPC)
		(*tmp) = (*tmp)->next;
	(t->red_out) = open((*tmp)->key, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if ((t->red_out) < 0)
		return (3);
	if (t->piped)
		return (1);
	*tmp = (*tmp)->next;
	return (1);
}

int	redir_out(t_token **tmp, t_main_prepare_cmd *t)
{
	if ((t->red_out) != 1)
		close((t->red_out));
	*tmp = (*tmp)->next;
	if (*tmp && (*tmp)->value == SPC)
		*tmp = (*tmp)->next;
	if (!(*tmp)->key)
	{
		printf("bash: %s: ambiguous redirect\n", (*tmp)->copy_key);
		ft_exit_status(1, SET);
		ft_exit_herdog(1, SET);
		return (0);
	}
	(t->red_out) = open((*tmp)->key, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((t->red_out) < 0)
		return (2);
	if (t->piped)
		return (1);
	*tmp = (*tmp)->next;
	return (1);
}

int	handle_redir(t_token **tmp, t_main_prepare_cmd *t, t_env *envi)
{
	int	flag;

	flag = 0;;
	if ((*tmp)->value == IN)
		flag = redir_in(tmp, t);
	else if ((*tmp)->value == HEREDOC)
		return (redir_hd(tmp, t, envi));
	else if ((*tmp)->value == APPEND)
		flag = redir_apnd(tmp, t);
	else if ((*tmp)->value == OUT)
		flag = redir_out(tmp, t);
	if (flag == 3)
		ft_printf("Minishell: %s: Permission denied\n", (*tmp)->copy_key);
	else if (flag == 2)
	{
		ft_printf("Minishell: %s: Permission denied\n", (*tmp)->copy_key);
		while ((*tmp) && (*tmp)->next && (*tmp)->next->value != PIPE)
			(*tmp) = (*tmp)->next;
		if ((*tmp) && (*tmp)->next && (*tmp)->next->value == SPC)
			(*tmp) = (*tmp)->next;
		(*tmp)->key = NULL;
	}
	return (flag);
}
