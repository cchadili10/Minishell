/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:38:09 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/26 02:16:15 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirection(t_type type)
{
	if (type == APPEND || type == HEREDOC || type == IN || type == OUT)
		return (1);
	return (0);
}

int	err(char *str, t_token *cur, int flag)
{
	if (str == NULL)
		ft_putendl_fd("syntax error", 2);
	else if (flag == 1)
		ft_printf("%s `%s'\n", str, cur->next->key);
	else
		ft_printf("minishell: %s\n", str);
	return (1);
}

int	redir_errors(t_token *cur)
{
	if(cur->next->value == PIPE)
		return (err("syntax error near unexpected token `|'", cur, 0), 0);
	if (cur && cur->next && cur->next->next
		&& (cur->next->value == PIPE && cur->next->next->value == PIPE))
		return (err("syntax error near unexpected token `||'", cur, 0), 0);
	if (cur->next == NULL
		|| (cur->next->value == SPC && cur->next->next == NULL)
		|| (!ft_strcmp(cur->key, ">") && cur->next->value == PIPE))
	{
		err("syntax error near unexpected token `newline'", cur, 0);
		return (0);
	}
	if (cur && cur->next && cur->next->next && ((cur->next->value == SPC
				&& (cur->next->next->value == PIPE))
			|| (cur->next->value == PIPE
				&& cur->next->next->value == PIPE)))
		return (err("syntax error near unexpected token `|'", cur, 0), 0);
	if (is_redirection(cur->next->value)
		|| (cur->next->value == SPC
			&& is_redirection(cur->next->next->value)))
		return (err("syntax error near unexpected token", cur, 1), 0);
	return (1);
}

int	check_is_valid(t_token *cur)
{
	if (is_redirection(cur->value))
	{
		if (!redir_errors(cur))
			return (0);
	}
	else if (cur->value == PIPE)
	{
		if (cur->next == NULL
			|| (cur->next->value == SPC && cur->next->next == NULL))
			return (err("syntax error near unexpected token `|'", cur, 0), 0);
		if ((cur->next->value == SPC
				&& is_redirection(cur->next->next->value)
				&& cur->next->next->next == NULL)
			|| (cur->next->value == PIPE && cur->next->next == NULL))
			return (err("syntax error near unexpected token `newline'"
					, cur, 0), 0);
		if (cur->next == NULL
			|| (cur->next->value == SPC && cur->next->next == NULL)
			|| (cur->next->value == SPC && cur->next->next->value == PIPE))
			return (err("syntax error near unexpected token `|'", cur, 0), 0);
	}
	return (1);
}

int	catch_errors(t_token **arg)
{
	t_token	*cur;

	cur = *arg;
	if (!cur || (cur->value == SPC && cur->next == NULL))
		return (0);
	while (cur)
	{
		if (!check_is_valid(cur))
		{
			ft_exit_status(258, SET);
			return (0);
		}
		cur = cur->next;
	}
	return (1);
}
