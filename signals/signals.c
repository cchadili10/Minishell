/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:46:20 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/19 19:38:23 by yessemna         ###   ########.fr       */
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
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_redisplay();
		ft_exit_status(128 + sig, SET);
	}
}

void	ft_signal(int check)
{
	if (check == 1)
	{
		signal(SIGINT, sigusr_handler);
		signal(SIGQUIT, sigusr_handler);
	}
	else if (check == 2)
		signal(SIGINT, SIG_IGN);
	else if (check == 3)
		signal(SIGINT, SIG_DFL);
}

void	ft_herdoc(int sig)
{
	(void)sig;
	rl_on_new_line();
	close(0);
}
