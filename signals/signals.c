/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:46:20 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/15 21:32:00 by hchadili         ###   ########.fr       */
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
		ft_exit_herdog(1, SET);
	}
}

void	ft_signal(void)
{
	signal(SIGINT, sigusr_handler);
	signal(SIGQUIT, sigusr_handler);
}

void	ft_herdoc(int sig)
{
	(void)sig;
	rl_on_new_line();
	close(0);
}
