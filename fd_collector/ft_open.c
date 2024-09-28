/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 08:37:49 by yessemna          #+#    #+#             */
/*   Updated: 2024/09/26 16:20:11 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open(t_fd_col *collector, const char *filename, int flags, mode_t mode)
{
	int	fd;

	if (collector->count >= OPEN_MAX)
	{
		ft_printf("Error: Maximum file descriptor limit reached.\n");
		return (false);
	}
	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		perror("Error opening file");
		return (-1);
	}
	collector->fds[collector->count++] = fd;
	return (fd);
}

void	close_all_fds(t_fd_col *collector)
{
	int	i;

	i = 0;
	while (i < collector->count)
	{
		if (collector->fds[i] != -1)
		{
			close(collector->fds[i]);
			collector->fds[i] = -1;
		}
		i++;
	}
	collector->count = 0;
}
