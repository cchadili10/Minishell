/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:05:28 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/17 23:25:39 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit_status(int value, int set)
{
	static int	exit_staus;

	if (set == SET)
		exit_staus = value;
	else if (set == GET)
		return (exit_staus);
	return (0);
}

int	ft_exit_herdog(int check, int set)
{
	static int	res;

	if (set == SET)
		res = check;
	else if (set == GET)
		return (res);
	return (0);
}
