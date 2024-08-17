/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:43:08 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/17 23:52:49 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_n(char *str)
{
	int	x;

	x = 0;
	if (!str[x])
		return (0);
	while (str[x])
	{
		if (str[x] != 'n')
			return (0);
		x++;
	}
	return (1);
}

int	ft_look_for_n(char *str)
{
	if (str[0] == '-')
		return (ft_check_n(str + 1));
	else
		return (0);
}

void	ft_write_echo_no_nl(t_cmd *tmp, int x, int i)
{
	int	holder;

	holder = x;
	while (x < i)
	{
		if (x == holder)
			write(1, tmp->cmds[x], ft_strlen(tmp->cmds[x]));
		else
		{
			write(1, " ", 1);
			write(1, tmp->cmds[x], ft_strlen(tmp->cmds[x]));
		}
		x++;
	}
}

void	ft_write_echo_nl(t_cmd *tmp, int x, int i)
{
	x = 1;
	while (x < i)
	{
		if (x == 1)
			printf("%s", tmp->cmds[x]);
		else
			printf(" %s", tmp->cmds[x]);
		x++;
	}
	printf("\n");
}

void	ft_echo(t_cmd *cmnd)
{
	int		i;
	int		x;
	int		y;
	int		check;
	t_cmd	*tmp;

	((1) && (x = 2, y = 0, i = 1, check = 0, tmp = cmnd));
	while (tmp->cmds[i])
		i++;
	if (i == 1)
		printf("\n");
	else
	{
		while (ft_look_for_n(tmp->cmds[++y]))
			check = 1;
		if (check)
			ft_write_echo_no_nl(tmp, y, i);
		else
			ft_write_echo_nl(tmp, x, i);
	}
	ft_exit_status(0, SET);
}
