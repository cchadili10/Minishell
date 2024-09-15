/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:46:20 by hchadili          #+#    #+#             */
/*   Updated: 2024/09/15 12:34:27 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigusr_handler(int sig)
{
	(void)sig;
	if (sig == SIGQUIT)
		return ;
	else
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_redisplay();
		ft_exit_status(1, SET);
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
	ft_exit_status(1, SET);
	close(0);
}
