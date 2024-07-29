/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:34:56 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/29 11:11:39 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	ft_atoi_l(const char *str)
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
			return (-1);
		else if (res > LONG_MAX && sin == -1)
			return (0);
	}
	return (res * sin);
}

int	ft_check_exit_number(char *str)
{
	int x;

	x = 0;
	if(!str[x])
		return 0;
	if (str[x] == '-' && str[x+1])
		x++;
	while(str[x])
	{
		if(str[x] < '0' || str[x] > '9')
			return 0;
		x++;
	}
	return 1;
}

void	ft_exit(t_cmd *cmnd)
{
	int x = 0;
	while (cmnd->cmds[x])
		x++;
	if (x == 1)
		exit(0);
	if (x == 2)
	{
		if (ft_check_exit_number(cmnd->cmds[1]))
			exit((unsigned char)ft_atoi_l(cmnd->cmds[1]));
		else
		{
			printf("exit\nMinishell: exit: %s: numeric argument required\n", cmnd->cmds[1]);
			exit(255);
		}
	}
	else
	{
		if (ft_check_exit_number(cmnd->cmds[1]))
		{
			printf("exit\nMinishell: bash: exit: too many arguments\n");
			ft_exit_status(1, SET);
		}
		else
		{
			printf("exit\nMinishell: exit: %s: numeric argument required\n", cmnd->cmds[1]);
			exit(255);
		}
	}
}
