/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:43:08 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/19 23:46:39 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_look_for_n(char *str)
{
	int x = 0;
	while (str[x])
	{
		if(str[0] != '-')
			break ;
		x++;
	}
	
	
}

void ft_echo(t_cmd *cmnd)
{
	int	i = 0;
	t_cmd *tmp = cmnd; 
	
	while (tmp->cmds[i])
		i++;
	if (i == 1)
		printf("\n");
	else
	{
		if (ft_look_for_n(tmp->cmds[1]))
	}
	
}