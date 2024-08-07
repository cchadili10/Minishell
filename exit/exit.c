/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:05:28 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/07 04:08:07 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit_status(int value, int set)
{
	static int	exit_staus;

	if (set == SET)
		exit_staus = value;
	else if (set == GET)
	{
		return (exit_staus);
		ft_exit_status(127, SET);
	}
	return (0);
}
