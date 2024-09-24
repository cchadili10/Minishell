/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:30:46 by hchadili          #+#    #+#             */
/*   Updated: 2024/09/24 04:35:50 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_exit(void)
{
	g_malloc_env(0, FREE);
	g_malloc(0, FREE);
	printf("exit\n");
	exit(ft_exit_status(0, GET));
}

int	ft_check_first(char *first_cmnd, t_exection_var *exp, int check)
{
	if (check)
	{
		if (!first_cmnd)
		{
			exp->flag = 16;
			return (1);
		}
		if (!(*first_cmnd))
		{
			exp->flag = 6;
			return (1);
		}
	}
	else
	{
		if (ft_strcmp(":", first_cmnd) == 0)
		{
			exp->flag = 17;
			return (1);
		}
	}
	return (0);
}
