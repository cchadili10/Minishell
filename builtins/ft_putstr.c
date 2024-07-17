/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 03:14:05 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/17 03:35:11 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_putchar_fd(char c, int fd)
{
	if (fd >= 0)
		write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	x;

	x = 0;
	if (!s)
		return ;
	if (fd >= 0)
	{
		while (s[x])
			ft_putchar_fd(s[x++], fd);
		ft_putchar_fd('\n', fd);
	}
}