/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:05:28 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/28 17:48:21 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_exit_status(int value, int set)
{
	static int exit_staus;
	if(set ==  SET)
		exit_staus = value;
	else if (set == GET)
	{
		printf("Minishell: %d: command not found\n", exit_staus);
		ft_exit_status(127, SET);
	}
}