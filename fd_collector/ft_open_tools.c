/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 08:29:31 by yessemna          #+#    #+#             */
/*   Updated: 2024/09/24 00:57:16 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_fd_collector(t_fd_col *collector)
{
	int	i;

	i = 0;
	while (i < MAX_FDS)
	{
		collector->fds[i] = -1;
		i++;
	}
	collector->count = 0;
}
