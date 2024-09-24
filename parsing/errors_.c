/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 04:33:30 by yessemna          #+#    #+#             */
/*   Updated: 2024/09/24 04:34:07 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    free_garb_exite(void)
{
	printf("exit\n");
	g_malloc_env(0, FREE);
	exit(ft_exit_status(0, GET));
}

bool	pipe_syntax_error(t_token **list)
{
	if ((*list)->value == PIPE
		&& ((*list)->next->value != PIPE || (*list)->next != NULL))
	{
		ft_printf("Minishell: syntax error near unexpected token `|'\n");
		ft_exit_status(258, SET);
		return (true);
	}
	return (false);
}
