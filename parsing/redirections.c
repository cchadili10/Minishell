/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 20:46:35 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/18 22:27:50 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_in(t_token **tmp, int *red_in)
{
	*tmp = (*tmp)->next;
	if (*tmp && (*tmp)->value == SPC)
		*tmp = (*tmp)->next;
	(*red_in) = open((*tmp)->key, O_RDONLY);
	if ((*red_in) < 0)
		return (0);
	if ((*tmp)->next && (*tmp)->next->next && ((*tmp)->next->value == PIPE
			|| ((*tmp)->next->value == SPC
				&& (*tmp)->next->next->value == PIPE)))
		return (1);
	*tmp = (*tmp)->next;
	return (1);
}

int	redir_hd(t_token **tmp, int *red_in, t_env *envi)
{
	if ((*red_in) != 0)
		close((*red_in));
	(*tmp) = (*tmp)->next;
	if (*tmp && (*tmp)->value == SPC)
		(*tmp) = (*tmp)->next;
	ft_here_doc(*tmp, envi, red_in);
	close(*red_in);
	(*red_in) = open("/tmp/dog", O_RDONLY);
	if ((*red_in) < 0)
		return (0);
	if ((*tmp)->next && (*tmp)->next->next && ((*tmp)->next->value == PIPE
			|| ((*tmp)->next->value == SPC
				&& (*tmp)->next->next->value == PIPE)))
	{
		(*tmp)->key = "/tmp/dog";
		return (1);
	}
	*tmp = (*tmp)->next;
	return (1);
}

int	redir_apnd(t_token **tmp, int *red_out)
{
	(*tmp) = (*tmp)->next;
	if (*tmp && (*tmp)->value == SPC)
		(*tmp) = (*tmp)->next;
	(*red_out) = open((*tmp)->key, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if ((*red_out) < 0)
		return (0);
	*tmp = (*tmp)->next;
	return (1);
}

int	redir_out(t_token **tmp, int *red_out)
{
	if ((*red_out) != 1)
		close((*red_out));
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
	(*red_out) = open((*tmp)->key, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*red_out) < 0)
		return (2);
	*tmp = (*tmp)->next;
	return (1);
}

int	handle_redir(t_token **tmp, int *red_in, int *red_out, t_env *envi)
{
	int	flag;

	if ((*tmp)->value == IN)
		return (redir_in(tmp, red_in));
	else if ((*tmp)->value == HEREDOC)
		return (redir_hd(tmp, red_in, envi));
	else if ((*tmp)->value == APPEND)
		return (redir_apnd(tmp, red_out));
	else if ((*tmp)->value == OUT)
	{
		flag = redir_out(tmp, red_out);
		if (flag == 2)
		{
			ft_printf("Minishell: %s: Permission denied\n", (*tmp)->copy_key);
			while ((*tmp) && (*tmp)->next && (*tmp)->next->value != PIPE)
				(*tmp) = (*tmp)->next;
			if ((*tmp) && (*tmp)->next && (*tmp)->next->value == SPC)
				(*tmp) = (*tmp)->next;
			(*tmp)->key = NULL;
			return (0);
		}
		return (flag);
	}
	return (0);
}
