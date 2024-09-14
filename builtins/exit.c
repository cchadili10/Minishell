/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:34:56 by hchadili          #+#    #+#             */
/*   Updated: 2024/09/14 20:00:54 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exite_and_free_garb(char *str, int nut_exite, int check)
{
	g_malloc_env(0, FREE);
	g_malloc(0, FREE);
	if (check)
	{
		printf("exit\n");
		ft_printf("Minishell: exit: %s: ", str);
		ft_printf("numeric argument required\n");
		exit(255);
	}
	exit((unsigned char)nut_exite);
}

int	ft_atoi_l(const char *str, int *check)
{
	int					x;
	int					sin;
	unsigned long long	res;

	x = 0;
	sin = 1;
	res = 0;
	while ((str[x] >= 9 && str[x] <= 13) || str[x] == 32)
		x++;
	if (str[x] == '-' || str[x] == '+' )
	{
		if (str[x] == '-')
			sin *= -1;
		x++;
	}
	while (str[x] >= '0' && str[x] <= '9')
	{
		res = res * 10 + str[x++] - 48;
		if (res > LONG_MAX && sin == 1)
			return (*check = 1);
		else if (res > LONG_MAX && sin == -1)
			return (*check = 1);
	}
	return (res * sin);
}

int	ft_check_exit_number(char *str)
{
	int	x;

	x = 0;
	if (!str[x])
		return (0);
	if ((str[x] == '-' || str[x] == '+') && str[x + 1])
		x++;
	while (str[x])
	{
		if (str[x] < '0' || str[x] > '9')
			return (0);
		x++;
	}
	return (1);
}

void	ft_exit_many_arg(t_cmd *cmnd)
{
	if (ft_check_exit_number(cmnd->cmds[1]))
	{
		printf("exit\n");
		ft_printf("Minishell: bash: exit: too many arguments\n");
		ft_exit_status(1, SET);
	}
	else
	{
		printf("exit\n");
		ft_printf("Minishell: exit: %s: ", cmnd->cmds[1]);
		ft_printf("numeric argument required\n");
		ft_exite_and_free_garb(cmnd->cmds[1], 255, 0);
	}
}

void	ft_exit(t_cmd *cmnd)
{
	int	x;
	int	check;

	x = 0;
	check = 0;
	while (cmnd->cmds[x])
		x++;
	if (x == 1)
		exit(ft_exit_status(0, GET));
	if (x == 2)
	{
		if (ft_check_exit_number(cmnd->cmds[1]))
			ft_exite_and_free_garb(cmnd->cmds[1],
				(unsigned char)ft_atoi_l(cmnd->cmds[1], &check), check);
		else
		{
			printf("exit\n");
			ft_printf("Minishell: exit: %s: ", cmnd->cmds[1]);
			ft_printf("numeric argument required\n");
			ft_exite_and_free_garb(cmnd->cmds[1], 255, 0);
		}
	}
	else
		ft_exit_many_arg(cmnd);
}
