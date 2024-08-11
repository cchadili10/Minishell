/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:46:20 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/11 17:03:09 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigusr_handler(int sig)
{
	(void)sig;
	if (sig == SIGQUIT)
	{
		ft_exit_status(128 + sig, SET);
		return ;
	}
	else
	{
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
		ft_exit_status(128 + sig, SET);
	}
}

void	ft_signal(void)
{
	signal(SIGINT, sigusr_handler);
	signal(SIGQUIT, sigusr_handler);
}
